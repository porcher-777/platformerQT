#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy : public QWidget, public QGraphicsPixmapItem{
    Q_OBJECT
public:

    //////////////////////// Constructor / Destructor /////////////////////

    Enemy(QPoint posmin, QPoint posmax, QWidget* parent = nullptr);
    virtual ~Enemy();

    ////////////////////// Methods ////////////////////////////////////////

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void move();
    void attack();

    void setIscollidingright(bool newIscollidingright);

    void setIscollidingleft(bool newIscollidingleft);

public slots:

    void slot_updateSprite();

private slots:

    void slot_nextFrame();

private:

    bool iswalkingright;
    bool iswalkingleft;
    bool isattackingright;
    bool isattackingleft;
    bool iscollidingright;
    bool iscollidingleft;

    QPoint posmin;
    QPoint posmax;

    QTimer* timer;      // Timer for turning images into QPixmap
    QPixmap* sprite;   // In this QPixmap object will be placed sprite
    int currentframe;   // Coordinates X, which starts the next frame of the sprite

    std::pair<int, int> sc;   //stands for sprite choice

};

#endif // ENEMY_H
