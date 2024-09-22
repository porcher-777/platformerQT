#include "MyScene.h"
#include "MyView.h"

//////////////////////// Constructor / Destructor /////////////////////

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent){

    this->ended = 0;
    this->score = 0;

    this->playerdialog = new Playerdialog;
    this->platform = new std::map<QPoint, QPixmap>;
    this->souls = new std::map<QPoint, Soul*>;
    this->listsouls = new std::list<QGraphicsPixmapItem*>;
    this->enemies = new std::list<Enemy*>;
    this->background.load(":/assets/background/BG.png");
    this->setSceneRect(0, 0, background.width(), background.height());

    QGraphicsPixmapItem* element;
    Soul* soul;
    generateMap();

    //Insert platforms in the scene

    for(auto it = this->platform->begin(); it != this->platform->end(); ++it){
        element = new QGraphicsPixmapItem(it->second);
        element->setPos(it->first);
        this->addItem(element);
    }

    //Insert souls in the scene

    for(auto it = this->souls->begin(); it != this->souls->end(); ++it){
        soul = it->second;
        this->addItem(soul);
        soul->setPos(it->first);
        this->listsouls->push_back(soul);   //List of souls which is used to hide them if the player "collects" them
    }

    this->stopwatch = new Stopwatch("00 : 00");
    this->player = new Player;
    this->door = new Door;

    this->addItem(this->door);
    this->addItem(this->player);
    this->addItem(this->stopwatch);

    createEnnemies();

    this->timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &MyScene::slot_update);
    connect(this->player, &Player::finishLineReached, this->door, &Door::slot_nextFrame);
    this->timer->start(30); //refresh every 30 ms

    this->playerdialog->exec();

    this->music = new QSound(":/music/Heavens_door.wav");
    this->music->setLoops(QSound::Infinite);
    this->music->play();
}

MyScene::~MyScene(){}

/////////////////////// Redefined methods ////////////////////////////

void MyScene::drawBackground(QPainter* painter, const QRectF &rect){
    Q_UNUSED(rect);
    painter->drawPixmap(QPointF(0,0), this->background, sceneRect());
}

void MyScene::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Q)
        this->player->activateRunLeft();

    if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
        this->player->activateRunRight();

    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Z || event->key() == Qt::Key_Space)
        this->player->activateJump();

    if(event->key() == Qt::Key_R)
        this->player->respawn();

    if(event->key() == Qt::Key_Escape){
        this->music->stop();
        emit returnToMenu();
    }
}

void MyScene::keyReleaseEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Left || event->key() == Qt::Key_Q)
        this->player->deactivateRunLeft();

    if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D)
        this->player->deactivateRunRight();

    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Z || event->key() == Qt::Key_Space)
        this->player->deactivateJump();

}

bool operator<(const QPoint& p1, const QPoint& p2){
    return p1.x() < p2.x() || (p1.x() == p2.x() && p1.y() < p2.y());
}

///////////////////////////// Methods ////////////////////////////////////

//Insert positions and pixmap of every platform in a map
//Insert positions and pointer on soul type in another map

void MyScene::generateMap(){
    int wpos = 0;
    QPixmap pimage; //pixmap of platforms
    QPixmap plimage;
    std::vector<QString> grounds = {":/assets/obstacle/plat1.png", ":/assets/obstacle/plat2.png", ":/assets/obstacle/plat3.png"}; //compile ground plaforms in a vector
    std::vector<int> pchoice = {1, 2, 0, 1, 1, 2, 2, 1, 2, 0}; // order in which platforms appear
    std::vector<int> plchoice = {2, 2, 0, 1, 1, 2, 2, 0, 0, 2}; // order in which platforms appear

    for(int i = 0; i < 10; i++){
        Soul* soul = new Soul;
        if(i == 3){
            wpos += 110;
            pimage = QPixmap(":/assets/obstacle/plat5.png");

            this->platform->insert(std::pair<QPoint,QPixmap>(QPoint(wpos, YLEVEL - (i * 75 + pimage.height())), pimage));
            this->platform->insert(std::pair<QPoint,QPixmap>(QPoint(wpos + i * 110, YLEVEL - (i * 45 + pimage.height())), pimage));

            this->souls->insert(std::pair<QPoint,Soul*>(QPoint(wpos + 30, YLEVEL - (i * 75 + pimage.height()) - 70), soul));
        }
        if(i == 4){
            wpos += 130;
            pimage = QPixmap(":/assets/obstacle/plat5.png");
            this->platform->insert(std::pair<QPoint,QPixmap>(QPoint(wpos, YLEVEL - (i * 85 + pimage.height())), pimage));
            this->platform->insert(std::pair<QPoint,QPixmap>(QPoint(wpos + i * 45 , YLEVEL - (i * 45 + pimage.height())), pimage));

            this->souls->insert(std::pair<QPoint,Soul*>(QPoint((wpos + i * 45) + 30, YLEVEL - (i * 45 + pimage.height()) - 70), soul));
            this->souls->insert(std::pair<QPoint,Soul*>(QPoint(wpos + 30, YLEVEL - (i * 75 + pimage.height()) - 70), soul));
        }
        if(i == 6){
            wpos += 30;
            pimage = QPixmap(":/assets/obstacle/plat5.png");
            this->platform->insert(std::pair<QPoint,QPixmap>(QPoint(wpos, YLEVEL - (i * 35 + pimage.height())), pimage));

            this->souls->insert(std::pair<QPoint,Soul*>(QPoint(wpos + 20, YLEVEL - (i * 35 + pimage.height()) - 70), soul));
        }
        else{
            plimage = QPixmap(grounds[plchoice[i]]);
            this->platform->insert(std::pair<QPoint,QPixmap>(QPoint(wpos, YLOWERLEVEL - plimage.height()), plimage));
            pimage = QPixmap(grounds[pchoice[i]]);
            this->platform->insert(std::pair<QPoint,QPixmap>(QPoint(wpos, YLEVEL - pimage.height()), pimage));
            if(i%2 == 0)
                this->souls->insert(std::pair<QPoint,Soul*>(QPoint(wpos + 40, YLEVEL - pimage.height() - 70), soul));
            if(i%2 == 1)
                this->souls->insert(std::pair<QPoint,Soul*>(QPoint(wpos + 60, YLOWERLEVEL - plimage.height() - 70), soul));

        }
        wpos += pimage.width() - 10;
    }
}

//Create enemies, place them and put them in a map

void MyScene::createEnnemies(){
    Enemy* enemy1 = new Enemy(QPoint(285, 715), QPoint(402, 715));       // y = platform height - enemy height - 1  -- 402 == platform xpos - enemy max width
    this->addItem(enemy1);
    this->enemies->push_back(enemy1);

    Enemy* enemy2 = new Enemy(QPoint(841, 770), QPoint(1024, 770));       //same
    this->addItem(enemy2);
    this->enemies->push_back(enemy2);

    Enemy* enemy3 = new Enemy(QPoint(1256, 770), QPoint(1429, 770));       //same
    this->addItem(enemy3);
    this->enemies->push_back(enemy3);

    Enemy* enemy4 = new Enemy(QPoint(508, 1155), QPoint(625, 1155));       //same
    this->addItem(enemy4);
    this->enemies->push_back(enemy4);

    Enemy* enemy5 = new Enemy(QPoint(1541, 1215), QPoint(1658, 1215));       //same
    this->addItem(enemy5);
    this->enemies->push_back(enemy5);
}

void MyScene::finishLine(){
    //Player arrives to the finish line -> displays menu and scores

    if(this->door->QGraphicsItem::x() <= this->player->QGraphicsItem::x()
       && this->door->QGraphicsItem::y() + this->door->boundingRect().height() >= this->player->QGraphicsItem::y()
       && this->door->QGraphicsItem::y() <= this->player->QGraphicsItem::y()){     //collideWithItem not working, don't know why
        emit this->player->finishLineReached();
        if(this->player->getSouls() >= 10)   //player got all the souls or more (only hiding them)
            this->ended = 1;
        if(this->player->getSouls() < 10)                               //player did get to the finish line but is lacking the 6 souls
            this->ended = 2;

        this->score = this->stopwatch->getTotaltime();
        emit ending();
        this->player->setPos(0, 0);         //Go back to zero soul to prevent the signal from emiting next timeout
        this->ended = 0;
        this->music->stop();
    }

    if(this->player->getLifepoint() <= 0){
        this->ended = 2;     //player lifepoint = 0
        emit ending();
        this->player->setLifepoint(1);      //Go back to zero soul to prevent the signal from emiting next timeout
        this->ended = 0;
        this->music->stop();
    }

    if(this->player->QGraphicsItem::y() >= 1500){
        this->ended = 2;     //player lifepoint = 0
        emit ending();
        this->player->setPos(0, 0);         //Go back to zero soul to prevent the signal from emiting next timeout
        this->ended = 0;
        this->music->stop();
    }
}

void MyScene::hidingSoul(){
    //Hiding the souls once the player collected them

    for(auto it = this->listsouls->begin(); it != this->listsouls->end();){
        //bidouilling collisions cause collideWithItem also not working
        if(this->player->QGraphicsItem::x() >= (*it)->x() - 5 && this->player->QGraphicsItem::x() <= (*it)->x() + 5 && this->player->QGraphicsItem::y() + this->player->boundingRect().height() + 5 >= (*it)->y() && this->player->QGraphicsItem::y() <= (*it)->y()){
            (*it)->hide();
            it = this->listsouls->erase(it);
            this->player->setSouls(this->player->getSouls() + 1);
        }
        else
            ++it;
    }
}

void MyScene::enemyCollisions(){

    //Collisions also not working with enemies (probably cause of inheritance ?) sooooooo declaring collisions with enemies - losing lifepoints if side collisions

    for(auto it = this->enemies->begin(); it != this->enemies->end(); ++it){

        //Colliding from the west
        if(this->player->QGraphicsItem::x() + this->player->boundingRect().width() + 1 >= (*it)->QGraphicsItem::x()
           && this->player->QGraphicsItem::x() + this->player->boundingRect().width() + 1 <= (*it)->QGraphicsItem::x() + 10
           && this->player->QGraphicsItem::y() + this->player->boundingRect().height() >= (*it)->QGraphicsItem::y()
           && this->player->QGraphicsItem::y() + this->player->boundingRect().height() <= (*it)->QGraphicsItem::y() + (*it)->boundingRect().height() + 10){

            (*it)->setIscollidingleft(1);
            this->player->setX((*it)->QGraphicsItem::x() - this->player->boundingRect().width() - 1);
            (*it)->attack();
            this->player->setLifepoint(this->player->getLifepoint() - 1);
        }

        //Colliding from the east

        if(this->player->QGraphicsItem::x() - 1 <= (*it)->QGraphicsItem::x() + (*it)->boundingRect().width()
           && this->player->QGraphicsItem::x() - 1 >= (*it)->QGraphicsItem::x() + (*it)->boundingRect().width() - 10
           && this->player->QGraphicsItem::y() + this->player->boundingRect().height() >= (*it)->QGraphicsItem::y()
           && this->player->QGraphicsItem::y() + this->player->boundingRect().height() <= (*it)->QGraphicsItem::y() + (*it)->boundingRect().height() + 10){

            (*it)->setIscollidingright(1);
            this->player->setX((*it)->QGraphicsItem::x() + (*it)->boundingRect().width() + 1);
            (*it)->attack();
            this->player->setLifepoint(this->player->getLifepoint() - 1);
        }

        //Colliding from the south

        if(this->player->QGraphicsItem::y() + this->player->boundingRect().height() + 1 >= (*it)->QGraphicsItem::y()
           && this->player->QGraphicsItem::x() >= (*it)->QGraphicsItem::x()
           && this->player->QGraphicsItem::x() <= (*it)->QGraphicsItem::x() + (*it)->boundingRect().width()
           && this->player->QGraphicsItem::y() + this->player->boundingRect().height() <= (*it)->QGraphicsItem::y() + (*it)->boundingRect().height() + 10){      //collideWithItem not working, don't know why

            this->player->setY((*it)->QGraphicsItem::y() - this->player->boundingRect().height());
            this->player->setIsmidair(0);
            this->player->setIsjumping(0);
        }

    }
}


//////////////////////////// Slots ////////////////////////////////////////

//Update positions and "states" of every items in the scene every 30ms

void MyScene::slot_update(){

    //Updating View position

    QList<QGraphicsView*> views = this->views();
    if(views.size() == 1){
        views[0]->centerOn(this->player);
    }

    //Updating stopwatch position to fit in the view

    if(this->player->QGraphicsItem::x() < 1900)
        this->stopwatch->setPos(this->player->QGraphicsItem::x() + 450, this->player->QGraphicsItem::y() - 450);
    else
        this->stopwatch->setX(2350);

    //Updating movements states

    if(this->player->getIsrunningright())
        this->player->runRight();

    if(this->player->getIsrunningleft())
        this->player->runLeft();

    if(this->player->getIsjumping())
        this->player->jump();

    if(!this->player->getIsjumping() && this->player->getIsmidair())
        this->player->fall();

    this->finishLine();
    this->hidingSoul();
    this->enemyCollisions();


    this->player->collidingManagement();
    this->player->slot_updateSprite();

    this->stopwatch->stopwatchManagement();

}

//////////////////////////// Getters ////////////////////////////////////////

int MyScene::getEnded() const{
    return ended;
}

int MyScene::getScore() const{
    return score;
}

Playerdialog *MyScene::getPlayerdialog() const{
    return playerdialog;
}




