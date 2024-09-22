#ifndef SOUL_H
#define SOUL_H

#include "Player.h"

class Soul: public QWidget, public QGraphicsPixmapItem{

    Q_OBJECT

public:
    //////////////////////// Constructor / Destructor /////////////////////

    Soul(QWidget* parent = nullptr);
    virtual ~Soul();

    ////////////////////// Methods ////////////////////////////////////////

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private slots:

    void slot_nextFrame();

private:

    QTimer* timer;      // Timer for turning images into QPixmap
    QPixmap* sprite;   // In this QPixmap object will be placed sprite
    int currentframe;

};

#endif // SOUL_H
