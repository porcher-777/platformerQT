#include "Door.h"

//////////////////////// Constructor / Destructor /////////////////////

Door::Door(QWidget* parent) : QWidget(parent), QGraphicsPixmapItem(){
    this->sprite = new QPixmap(":/assets/door/doors.png");
    this->state = 0;
    this->setPos(2400, 580);
}

Door::~Door(){}

////////////////////// Methods ////////////////////////////////////////

//Redefines boundingRect depending on the sprite and "paint" it on the scene

QRectF Door::boundingRect() const{
    return QRectF(0, 0, 160, 150);       //spritesheet 640 x 150 - 4 sprites
}

void Door::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0, 0, *sprite, state, 0, 160, 150);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

/////////////////////// Slots /////////////////////////////////

void Door::slot_nextFrame(){
    if(this->state == 480){     //Stop at last sprite
        return;
    }
    this->state += 160;
}

