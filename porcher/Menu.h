#ifndef MENU_H
#define MENU_H

#include <QPushButton>
#include <QPixmap>
#include <QPalette>
#include <QLabel>
#include <QWidget>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QObject>
#include <QGraphicsScene>
#include <QPainter>
#include <QApplication>
#include <QTimer>
#include <QSound>

class Menu : public QWidget{

    Q_OBJECT

public:

    //////////////////////// Constructor / Destructor /////////////////////

    Menu(QWidget* parent = nullptr);
    virtual ~Menu();

    //////////////////////// Getters ////////////////////////////////

    QPushButton *getStart() const;
    QPushButton *getExit() const;
    QPushButton *getControls() const;
    QSound *getMusic() const;

    //////////////////////// Setters ////////////////////////////////

    void setHlayout(QHBoxLayout *newHlayout);

private slots:

    void slot_updateLayout();

private :

    QPushButton* start;
    QPushButton* exit;
    QPushButton* controls;

    QHBoxLayout* hlayout;

    QTimer* timer;
    QSound* music;

};

#endif // MENU_H
