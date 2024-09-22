
#include "Enemy.h"

//////////////////////// Constructor / Destructor /////////////////////

Enemy::Enemy(QPoint posmin, QPoint posmax, QWidget* parent) : QWidget(parent), QGraphicsPixmapItem(){
    this->sprite = new QPixmap(":/assets/ennemy/minotaur_wr.png");
    this->sc = std::pair<int, int>(94, 70);     //dimensions of the image according to spritesheet
    this->currentframe = 0;

    this->posmin = posmin;
    this->posmax = posmax;

    this->setPos(this->posmin);

    this->iswalkingright = 1;
    this->iswalkingleft = 0;
    this->isattackingright = 0;
    this->isattackingleft = 0;
    this->iscollidingright = 0;
    this->iscollidingleft = 0;

    this->timer = new QTimer();   // Create a timer for sprite animation
    connect(this->timer, &QTimer::timeout, this, &Enemy::slot_nextFrame);
    this->timer->start(100);
}

Enemy::~Enemy(){}

////////////////////// Methods ////////////////////////////////////////

//Redefines boundingRect depending on the sprite and "paint" it on the scene

QRectF Enemy::boundingRect() const{
    return QRectF(0, 0, this->sc.first, this->sc.second);
}

void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0, 0, *sprite, currentframe, 0, this->sc.first, this->sc.second);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//Defines the movement pattern

void Enemy::move(){
    if(this->iswalkingright)
        this->setX(QGraphicsItem::x() + 3);
    if(this->iswalkingleft)
        this->setX(QGraphicsItem::x() - 3);

    if(this->QGraphicsItem::pos().toPoint().x() >= this->posmax.x()){
        this->iswalkingleft = 1;
        this->iswalkingright = 0;
    }
    if(this->QGraphicsItem::pos().toPoint().x() <= this->posmin.x()){
        this->iswalkingleft = 0;
        this->iswalkingright = 1;
    }
}

//Defines the attack pattern and the damages inflicted

void Enemy::attack(){
    if(this->iscollidingright){
        this->isattackingright = 1;
        this->iscollidingright = 0;
        return;
    }
    if(this->iscollidingleft){
        this->isattackingleft = 1;
        this->iscollidingleft = 0;
        return;
    }
}

/////////////////////// Setters /////////////////////////////////

void Enemy::setIscollidingleft(bool newIscollidingleft){
    iscollidingleft = newIscollidingleft;
}

void Enemy::setIscollidingright(bool newIscollidingright){
    iscollidingright = newIscollidingright;
}

/////////////////////// Slots /////////////////////////////////

//Animation of the sprite

void Enemy::slot_nextFrame(){

    this->currentframe += this->sc.first;

    if((this->isattackingright && this->currentframe >= 560) || (this->isattackingleft && this->currentframe >= 560)){
        currentframe = 0;
        this->isattackingright = 0;
        this->isattackingleft = 0;
    }
    if((this->iswalkingright && this->currentframe >= 470) || (this->iswalkingleft && this->currentframe >= 470)){
        currentframe = 0;
    }

    this->QGraphicsItem::update(boundingRect());
    slot_updateSprite();
    move();
}

//Change enemy's sprite depending on its state

void Enemy::slot_updateSprite(){
    if(this->iswalkingright){
        this->sc = std::pair<int, int>(94, 70);
        this->sprite->load(":/assets/ennemy/minotaur_wr.png");
    }
    if(this->iswalkingleft){
        this->sc = std::pair<int, int>(94, 70);
        this->sprite->load(":/assets/ennemy/minotaur_wl.png");
    }
    if(this->isattackingright){
        this->sc = std::pair<int, int>(112, 70);
        this->sprite->load(":/assets/ennemy/minotaur_ar.png");
    }
    if(this->isattackingleft){
        this->sc = std::pair<int, int>(112, 70);
        this->sprite->load(":/assets/ennemy/minotaur_al.png");
    }
}






