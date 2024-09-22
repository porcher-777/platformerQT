#ifndef MYVIEW_H
#define MYVIEW_H

#include <QResizeEvent>
#include <QGraphicsView>

class MyView : public QGraphicsView{
    Q_OBJECT

public:
    //////////////////////// Constructor / Destructor /////////////////////

    MyView();
    virtual ~MyView();

protected:
    virtual void resizeEvent(QResizeEvent* event){      //Redefining from the QWidget class
        Q_UNUSED(event);
        this->fitInView(QRectF(0, 0, 1200, 1200));
    }
};

#endif // MYVIEW_H
