#include "Soul.h"

//////////////////////// Constructor / Destructor /////////////////////

Soul::Soul(QWidget* parent) : QWidget(parent), QGraphicsPixmapItem(){
    this->sprite = new QPixmap(":/assets/soul/souls.png");
    this->currentframe = 0;


    timer = new QTimer();   // Create a timer for sprite animation
    connect(timer, &QTimer::timeout, this, &Soul::slot_nextFrame);
    timer->start(200);
}

Soul::~Soul(){}

////////////////////// Methods ////////////////////////////////////////

//Redefines boundingRect depending on the sprite and "paint" it on the scene

QRectF Soul::boundingRect() const{
    return QRectF(0, 0, 37, 60);
}

void Soul::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0, 0, *sprite, currentframe, 0, 37, 60);
    //painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

/////////////////////// Slots /////////////////////////////////

void Soul::slot_nextFrame(){
    this->currentframe += 37;
    if(this->currentframe >= 148)
        currentframe = 0;

    this->QGraphicsItem::update(boundingRect());
}
