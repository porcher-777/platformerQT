#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>


#include "MyScene.h"
#include "Menu.h"
#include "MyView.h"

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    //////////////////////// Constructor / Destructor /////////////////////

    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

    /////////////////////// Redefined methods ////////////////////////////

    void keyPressEvent(QKeyEvent *event);

    ////////////////////// Methods ////////////////////////////////////////

    QStringList readScores(QString);
    void writeScores(QString, QStringList);

public slots:

    void slot_exit();
    void slot_start();
    void slot_showControls(); 
    void slot_displayEnding();
    void slot_displayPrincipalMenu();

private:

    MyScene* mainScene;
    QGraphicsView* mainView;
    Menu* menu;

};
#endif // MAINWINDOW_H
