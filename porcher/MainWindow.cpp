    #include "MainWindow.h"

//////////////////////// Constructor / Destructor /////////////////////

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    this->setWindowTitle("Heaven's Door");

    this->setStyleSheet("background-image: url(:/assets/background/BG_menu.png); background-repeat: no-repeat; background-position: center;");

    this->menu = new Menu;
    this->mainView = new MyView;
    this->mainView->setWindowTitle("Heaven's Door");

    this->setCentralWidget(this->menu);

    connect(this->menu->getStart(), &QPushButton::clicked, this, &MainWindow::slot_start);
    connect(this->menu->getControls(), &QPushButton::clicked, this, &MainWindow::slot_showControls);
    connect(this->menu->getExit(), &QPushButton::clicked, this, &MainWindow::slot_exit);

}

MainWindow::~MainWindow(){}

/////////////////////// Redefined methods ////////////////////////////

//Return to menu by pressing P

void MainWindow::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Escape){
        slot_displayPrincipalMenu();
    }
}

////////////////////// Methods ////////////////////////////////////////

//Read the informations from the scores text file

QStringList MainWindow::readScores(QString filename){
    QFile file(filename);
    QStringList listgot;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        QMessageBox::information(0, "error", file.errorString());
    QTextStream in(&file);
    QString got;
    while(!in.atEnd()){
        got = in.readLine();
        listgot.append(got.split(QLatin1Char(';')));
    }
    file.close();
    return listgot;
}

//Write new best score if there is one, else rewrite it as it was

void MainWindow::writeScores(QString filename, QStringList bestscore){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::information(0, "error", file.errorString());
    file.seek(0);
    QTextStream out(&file);

    if(this->mainScene->getScore() < bestscore[1].toInt())
        out << this->mainScene->getPlayerdialog()->getPlayername() << ";" << QString::number(this->mainScene->getScore()) << "\n";
    else
        out << bestscore[0] << ";" << bestscore[1];
}

/////////////////////// Slots /////////////////////////////////

//Shut the application

void MainWindow::slot_exit(){
    QApplication::quit();
}

//Start a run

void MainWindow::slot_start(){

    this->menu->getMusic()->stop();

    this->mainScene = new MyScene;
    this->mainView = new MyView;
    this->mainView->setScene(this->mainScene);

    this->mainView->setWindowTitle("Heaven's Door");

    this->setCentralWidget(mainView);
    this->menu->hide();

    connect(this->mainScene, &MyScene::ending, this, &MainWindow::slot_displayEnding);
    connect(this->mainScene, &MyScene::returnToMenu, this, &MainWindow::slot_displayPrincipalMenu);
}

//Show the controls through the menu

void MainWindow::slot_showControls(){
    this->setCentralWidget(menu);
    this->setStyleSheet("background-image: url(:/assets/background/menu_controls.png); background-repeat: no-repeat; background-position: center;");
    this->menu->hide();
}

//Return to the menu called in the constructor - put the run to an end

void MainWindow::slot_displayPrincipalMenu(){
    this->menu = new Menu;
    this->setCentralWidget(this->menu);

    this->setStyleSheet("background-image: url(:/assets/background/BG_menu.png); background-repeat: no-repeat; background-position: center;");

    connect(this->menu->getStart(), &QPushButton::clicked, this, &MainWindow::slot_start);
    connect(this->menu->getControls(), &QPushButton::clicked, this, &MainWindow::slot_showControls);
    connect(this->menu->getExit(), &QPushButton::clicked, this, &MainWindow::slot_exit);
}

//Display bestscore and ending background depending on the way the game ended

void MainWindow::slot_displayEnding(){
    this->menu = new Menu;

    QStringList bestscore = this->readScores("scores.txt");

    if(this->mainScene->getEnded() == 1){
        this->setStyleSheet("background-image: url(:/assets/background/BG_good_ending.png); background-repeat: no-repeat; background-position: center;");
        this->writeScores("scores.txt", bestscore);
        bestscore = this->readScores("scores.txt");
    }
    if(this->mainScene->getEnded() == 2){
        this->setStyleSheet("background-image: url(:/assets/background/BG_bad_ending.png); background-repeat: no-repeat; background-position: center;");
    }

    QString finalscore = bestscore[0] + " :\t\t " + bestscore[1] + " seconds" ;
    QLabel* score = new QLabel(finalscore);
    score->setStyleSheet("font: 35px; margin-top:200px");
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(score);
    layout->setAlignment(Qt::AlignCenter);
    this->menu->setHlayout(layout);
    this->setCentralWidget(this->menu);
}
