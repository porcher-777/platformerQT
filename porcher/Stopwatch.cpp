#include "Stopwatch.h"

//////////////////////// Constructor / Destructor /////////////////////

Stopwatch::Stopwatch(QString display) : QElapsedTimer(), QGraphicsTextItem(){
    this->setPos(0, 0);
    this->seconds = 0;
    this->minutes = 0;
    this->totaltime = 0;
    this->start();
    this->display = display;
    this->setScale(4);    //Increase item size
    //this->setFont("Gagalin");

    this->timer = new QTimer();
    connect(this->timer, &QTimer::timeout, this, &Stopwatch::slot_displayStopwatch);
    this->timer->start(999);
}

Stopwatch::~Stopwatch(){}

////////////////////// Methods ////////////////////////////////////////

//Transform the elapsed time into a readable format

void Stopwatch::stopwatchManagement(){
    this->seconds = this->elapsed() / 1000; //ms to s
    this->minutes = this->elapsed() / 60000; //ms to min - no need to detail hours and so on
}

//////////////////////// Getters ////////////////////////////////

int Stopwatch::getTotaltime() const{
    return totaltime;
}

//////////////////////// Slots ////////////////////////////////

//Display the elapsed time on the top-right corner of the scene

void Stopwatch::slot_displayStopwatch(){
    if(this->minutes < 10 && (this->seconds % 60) < 10)
        this->display = "0" + QString::number(this->minutes) + " : " + "0" + QString::number(this->seconds % 60);
    else if(this->minutes < 10)
       this->display = "0" + QString::number(this->minutes) + " : " + QString::number(this->seconds % 60);
    else if((this->seconds % 60) < 10)
        this->display = QString::number(this->minutes) + " : " + "0" + QString::number(this->seconds % 60);
    else
        this->display = QString::number(this->minutes) + " : " + QString::number(this->seconds % 60);

    this->setPlainText(this->display);
    this->totaltime = this->elapsed() / 1000; //ms to s
}
