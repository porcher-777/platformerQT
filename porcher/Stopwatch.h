#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QElapsedTimer>
#include <QGraphicsItem>
#include <QTimer>

class Stopwatch: public QElapsedTimer, public QGraphicsTextItem{

public:
    //////////////////////// Constructor / Destructor /////////////////////

    Stopwatch(QString display);
    virtual ~Stopwatch();

    ////////////////////// Methods ////////////////////////////////////////

    void stopwatchManagement();     //transition from ms to s - s to min

    //////////////////////// Getters ////////////////////////////////

    int getTotaltime() const;

private slots:

    void slot_displayStopwatch();    //display stopwatch on the scene

private:

    int seconds;
    int minutes;

    int totaltime;

    QTimer* timer;       //Creating a timer of his own so the display is done every second

    QString display;

};

#endif // STOPWATCH_H
