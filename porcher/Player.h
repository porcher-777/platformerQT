#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QPainter>
#include <QPoint>
#include <QRectF>
#include <QRandomGenerator>
#include <QPainter>
#include <QRectF>

#define JUMPSPEED -6.4
#define GRAVITYSPEED 0.3


class Player : public QWidget, public QGraphicsPixmapItem{
    Q_OBJECT
public:

    //////////////////////// Constructor / Destructor /////////////////////

    Player(QWidget* parent = nullptr);
    virtual ~Player();

    ////////////////////// Methods ////////////////////////////////////////

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void activateRunRight();
    void activateRunLeft();
    void activateJump();

    void deactivateRunRight();
    void deactivateRunLeft();
    void deactivateJump();

    void runRight();
    void runLeft();
    void jump();
    void fall();
    void respawn();

    void initPlayer();
    void collidingManagement();

    //////////////////////// Getters ////////////////////////////////

    bool getIsrunningleft() const;
    bool getIsrunningright() const;
    bool getIsjumping() const;
    bool getIsmidair() const;
    int getSouls() const;
    int getLifepoint() const;

    /////////////////////// Setters /////////////////////////////////

    void setIsjumping(bool newIsjumping);
    void setIsmidair(bool newIsmidair);
    void setSouls(int newSouls);
    void setLifepoint(int newLifepoint);

public slots:

    void slot_updateSprite();

private slots:

    void slot_nextFrame();

signals:

    void finishLineReached();

private:

    bool isrunningleft;
    bool isrunningright;
    bool isjumping;
    bool ismidair;
    bool isstill;
    bool colliding;

    bool collidingLeft;
    bool collidingRight;
    bool collidingBottom;

    float horizontalspeed;
    float verticalspeed;

    int souls;
    int lifepoint;

    QTimer* timer;      // Timer for turning images into QPixmap
    QPixmap* sprite;   // In this QPixmap object will be placed sprite
    int currentframe;   // Coordinates X, which starts the next frame of the sprite

    std::pair<int, int> sc;   //stands for sprite choice
};

#endif // PLAYER_H
