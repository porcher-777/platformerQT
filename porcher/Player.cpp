#include "Player.h"

//////////////////////// Constructor / Destructor /////////////////////

Player::Player(QWidget* parent) : QWidget(parent), QGraphicsPixmapItem(){
    this->sprite = new QPixmap(":/assets/character/animsheet_rest.png");
    this->sc = std::pair<int, int>(91, 88);     //dimensions of the image according to spritesheet
    this->currentframe = 0;
    this->souls = 0;
    this->lifepoint = 120;

    this->initPlayer();

    this->timer = new QTimer();   // Create a timer for sprite animation
    connect(this->timer, &QTimer::timeout, this, &Player::slot_nextFrame);
    this->timer->start(200);
}

Player::~Player(){}

////////////////////// Methods ////////////////////////////////////////

//Redefines boundingRect depending on the sprite and "paint" it on the scene

QRectF Player::boundingRect() const{
    return QRectF(0, 0, this->sc.first, this->sc.second);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(0, 0, *sprite, currentframe, 0, this->sc.first, this->sc.second);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

//Initialises all the "states" of the player

void Player::initPlayer(){
    this->isrunningleft = 0;
    this->isrunningright = 0;
    this->isjumping = 0;
    this->ismidair = 1;
    this->isstill = 1;
    this->colliding = 0;

    this->collidingLeft = 0;
    this->collidingRight = 0;
    this->collidingBottom = 0;

    this->horizontalspeed = 1;
    this->verticalspeed = JUMPSPEED;

    this->setPos(50, 700);
}

//Set of 6 functions describing the state of the player

void Player::activateRunRight(){
    this->isrunningright = 1;
    this->isstill = 0;
}
void Player::activateRunLeft(){
    this->isrunningleft = 1;
    this->isstill = 0;
}
void Player::activateJump(){
    this->isjumping = 1;
    this->ismidair = 1;
    this->isstill = 0;
}

void Player::deactivateRunLeft(){
    this->isrunningleft = 0;
    this->isstill = 1;
    this->currentframe = 0;
}
void Player::deactivateRunRight(){
    this->isrunningright = 0;
    this->isstill = 1;
    this->currentframe = 0;
}
void Player::deactivateJump(){
    this->isjumping = 0;
    this->currentframe = 0;
}

//Defines the movement pattern

void Player::runRight(){
    this->setX(QGraphicsItem::x() + 5);
    if(QGraphicsItem::pos().rx() > 2500)        //background width = 2500
        this->setX(QGraphicsItem::x() - 5);
}

void Player::runLeft(){
    this->setX(QGraphicsItem::x() - 5);
    if(QGraphicsItem::x() < 0)
        this->setX(QGraphicsItem::x() + 5);
}

void Player::jump(){
    ////////////////// Code from documentation given in the specification /////////////////
    this->setPos(QGraphicsItem::pos().rx() += this->horizontalspeed, QGraphicsItem::pos().ry() += this->verticalspeed);
    fall();
}

//Makes the player experience gravity

void Player::fall(){
    this->setPos(QGraphicsItem::pos().rx() += this->horizontalspeed, QGraphicsItem::pos().ry() += this->verticalspeed);
    this->verticalspeed += GRAVITYSPEED;
}

//Makes the player go back to initial position

void Player::respawn(){
    initPlayer();
}

//Manages collisions between the player and platforms

void Player::collidingManagement(){
    QList<QGraphicsItem*> collidinglist = this->collidingItems(Qt::IntersectsItemBoundingRect);

    collidingBottom = 0;
    collidingRight = 0;
    collidingLeft = 0;

    ismidair = 1;       //fall if no collision
    isjumping = 0;

    if(!collidinglist.isEmpty()){

        //iterating in reverse so that the last element encountered takes priority

        for(auto it = collidinglist.crbegin(); it != collidinglist.crend(); ++it){

            //Detect from where the collision is coming

            //collides with the south but doesn't overlap when colliding with another platform (hence the +20)
            if(this->QGraphicsItem::pos().ry() + this->boundingRect().height() + 1 >= (*it)->QGraphicsItem::pos().ry() && this->QGraphicsItem::pos().ry() + this->boundingRect().height() + 1 <= (*it)->QGraphicsItem::pos().ry() + 20)
                collidingBottom = 1;

            //collides with the east but doesn't overlap when colliding with another platform (hence the +10)
            if(this->QGraphicsItem::pos().rx() + this->boundingRect().width() + 1 >= (*it)->QGraphicsItem::pos().rx() && this->QGraphicsItem::pos().rx() + this->boundingRect().width() + 1 <= (*it)->QGraphicsItem::pos().rx() + 10)
                collidingRight = 1;

            //collides with the west but doesn't overlap when colliding with another platform (hence the -10)
            if(this->QGraphicsItem::pos().rx() - 1 <= (*it)->QGraphicsItem::pos().rx() + (*it)->boundingRect().width() && this->QGraphicsItem::pos().rx() - 1 >= (*it)->QGraphicsItem::pos().rx() + (*it)->boundingRect().width() - 10)
                collidingLeft = 1;


            //Updating position and state depending on where collisions come from

            //colliding south-east or south-west
            if((this->collidingBottom && this->collidingRight) || (this->collidingBottom && this->collidingLeft)){
                this->collidingBottom = 0;      //Prevent Ypos to adapt to the wrong platform

                ismidair = 1;
                isjumping = 0;
            }

            //colliding on both sides means you are between 2 platforms and doesn't have a choice but to fall
            if(this->collidingLeft && this->collidingRight){
                ismidair = 1;
                isjumping = 0;
            }

            //colliding west
            if(this->collidingLeft){
                this->setX((*it)->pos().rx() + (*it)->boundingRect().width() + 1);
                this->horizontalspeed = 0;
            }
            //colliding east
            if(this->collidingRight){
                this->setX((*it)->pos().rx() - this->boundingRect().width() - 1);
                this->horizontalspeed = 0;
            }
            //colliding south
            if(this->collidingBottom){
                this->setY((*it)->pos().ry() - this->boundingRect().height() + 1);
                this->verticalspeed = 0;
                this->ismidair = 0;
            }
            //be able to jump without being stuck on the ground
            if(!this->collidingBottom && !isjumping){
                ismidair = 1;
                this->horizontalspeed = 0;
                this->verticalspeed = 0;
            }

            else{
                this->horizontalspeed = 1;
                this->verticalspeed = JUMPSPEED;
            }

        }
    }
}

//////////////////////// Getters ////////////////////////////////

bool Player::getIsrunningleft() const{
    return this->isrunningleft;
}

bool Player::getIsrunningright() const{
    return this->isrunningright;
}

bool Player::getIsjumping() const{
    return this->isjumping;
}

bool Player::getIsmidair() const{
    return this->ismidair;
}

int Player::getSouls() const{
    return souls;
}

int Player::getLifepoint() const{
    return lifepoint;
}

/////////////////////// Setters /////////////////////////////////

void Player::setIsjumping(bool newIsjumping){
    this->isjumping = newIsjumping;
}

void Player::setIsmidair(bool newIsmidair){
    this->ismidair = newIsmidair;
}

void Player::setLifepoint(int newLifepoint){
    lifepoint = newLifepoint;
}

void Player::setSouls(int newSouls){
    souls = newSouls;
}

/////////////////////// Slots /////////////////////////////////

//Animation of the sprite

void Player::slot_nextFrame(){
    this->currentframe += this->sc.first;
    if(this->lifepoint <= 0 && this->currentframe >= 248)
            this->currentframe += this->sc.first;

    if((this->isrunningright && this->currentframe >= 240) || (this->isrunningleft && this->currentframe >= 232) || (this->isjumping && this->ismidair && this->currentframe >= 248) || (!this->isjumping && this->ismidair && this->currentframe >= 66) || (this->isstill && this->currentframe >= 110))
        currentframe = 0;

    this->QGraphicsItem::update(boundingRect());
}

//Change player's sprite depending on its state

void Player::slot_updateSprite(){
    if(this->lifepoint <= 0){
        this->sc = std::pair<int, int>(62, 88);
        this->sprite->load(":/assets/character/animsheet_death.png");
    }
    else if(this->lifepoint > 0 && this->isrunningright){
        this->sc = std::pair<int, int>(60, 88);
        this->sprite->load(":/assets/character/animsheet_runr.png");
    }
    else if(this->lifepoint > 0 && this->isrunningleft){
        this->sc = std::pair<int, int>(58, 88);
        this->sprite->load(":/assets/character/animsheet_runl.png");
    }
    else if(this->lifepoint > 0 && this->isjumping && this->ismidair){
        this->sc = std::pair<int, int>(62, 98);
        this->sprite->load(":/assets/character/animsheet_jump.png");
    }
    else if(this->lifepoint > 0 && !this->isjumping && this->ismidair){
        this->sc = std::pair<int, int>(66, 88);
        this->sprite->load(":/assets/character/animsheet_fall.png");
    }
    else{
        this->sc = std::pair<int, int>(55, 88);
        this->sprite->load(":/assets/character/animsheet_rest.png");
    }
}






