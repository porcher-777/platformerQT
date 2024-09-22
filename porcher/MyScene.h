#ifndef MYSCENE_H
#define MYSCENE_H

#include <vector>
#include <QSound>
#include <QSoundEffect>

#include "Player.h"
#include "Stopwatch.h"
#include "Soul.h"
#include "Door.h"
#include "Enemy.h"
#include "Playerdialog.h"

#define YLEVEL 900
#define YLOWERLEVEL 1400

class MyScene : public QGraphicsScene{
    Q_OBJECT
public:
    //////////////////////// Constructor / Destructor /////////////////////

    MyScene(QObject* parent = nullptr);
    virtual ~MyScene();

    /////////////////////// Redefined methods ////////////////////////////

    void drawBackground(QPainter *painter, const QRectF &rect); //From the QGraphicsScene Class
    void keyPressEvent(QKeyEvent *event);   //From the QWidget Class
    void keyReleaseEvent(QKeyEvent *event);

    ////////////////////// Methods ////////////////////////////////////////

    void createEnnemies();
    void generateMap();
    void enemyCollisions();
    void finishLine();
    void hidingSoul();

    //////////////////////// Getters ////////////////////////////////

    int getEnded() const;
    int getScore() const;

    Playerdialog *getPlayerdialog() const;

public slots:

    void slot_update();

signals:

    void ending();
    void returnToMenu();

private:
    std::map<QPoint, QPixmap>* platform;
    std::map<QPoint, Soul*>* souls;
    std::list<QGraphicsPixmapItem*>* listsouls;
    std::list<Enemy*>* enemies;

    QPixmap background;

    QTimer* timer;
    QSound* music;

    int ended;      //0 = not ended - 1 = ended with 10 souls / win - 2 = ended with less than 10 souls or lifepoint = 0 / loss
    int score;

    Player* player;
    Door* door;
    Stopwatch* stopwatch;
    Playerdialog* playerdialog;
};

#endif // MYSCENE_H
