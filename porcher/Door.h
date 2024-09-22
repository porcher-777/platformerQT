#ifndef DOOR_H
#define DOOR_H

#include "Player.h"

class Door : public QWidget, public QGraphicsPixmapItem{
    Q_OBJECT
public:

    //////////////////////// Constructor / Destructor /////////////////////

    Door(QWidget* parent = nullptr);
    virtual ~Door();

    ////////////////////// Methods ////////////////////////////////////////

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:

    void slot_nextFrame();

private:

    QTimer* timer;      // Timer for turning images into QPixmap
    QPixmap* sprite;   // In this QPixmap object will be placed sprite
    int state;

};

#endif // DOOR_H
