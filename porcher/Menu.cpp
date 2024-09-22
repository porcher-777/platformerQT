#include "Menu.h"

//////////////////////// Constructor / Destructor /////////////////////

Menu::Menu(QWidget* parent) : QWidget(parent){
    this->start = new QPushButton;
    this->exit = new QPushButton;
    this->controls = new QPushButton;

    //Tried with QIcon didn't find any way to make it work

    this->start->setStyleSheet("border-image:url(:/assets/menu/play_button.png); height: 60px; border-radius: 5px; padding-top: 50%; margin-top: 20%");
    this->exit->setStyleSheet("border-image:url(:/assets/menu/exit_button.png); height: 60px; border-radius: 5px; padding-top: 50%; margin-top: 20%");
    this->controls->setStyleSheet("border-image:url(:/assets/menu/controls_button.png); height: 60px; border-radius: 5px; padding-top: 50%; margin-top: 20%");

    //Layout with 3 buttons of the main menu

    this->hlayout = new QHBoxLayout();
    hlayout->addWidget(this->start);
    hlayout->addWidget(this->controls);
    hlayout->addWidget(this->exit);

    this->timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, &Menu::slot_updateLayout);
    this->timer->start(30); //refresh every 30 ms

    this->music = new QSound(":/music/Heavens_door_menu.wav");
    this->music->setLoops(QSound::Infinite);
    this->music->play();
}

Menu::~Menu(){}

//////////////////////// Getters ////////////////////////////////

QPushButton *Menu::getStart() const{
    return start;
}
QPushButton *Menu::getExit() const{
    return exit;
}
QPushButton *Menu::getControls() const{
    return controls;
}
QSound *Menu::getMusic() const{
    return music;
}
//////////////////////// Setters ////////////////////////////////

void Menu::setHlayout(QHBoxLayout *newHlayout){
    hlayout = newHlayout;
}

/////////////////////// Slots /////////////////////////////////

void Menu::slot_updateLayout(){
    this->setLayout(hlayout);
}







