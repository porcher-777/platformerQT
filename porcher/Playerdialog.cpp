#include "Playerdialog.h"

//////////////////////// Constructor / Destructor /////////////////////

Playerdialog::Playerdialog(){
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    this->setWindowTitle("Player Name");
    this->setMaximumWidth(300);
    this->setMaximumHeight(168);

    QLabel* playernamelabel = new QLabel("Player Name : ");
    QPushButton* validate = new QPushButton("OK");

    this->playernameedit = new QLineEdit("AnonymousPlayer");

    QHBoxLayout* labeledit = new QHBoxLayout;
    labeledit->addWidget(playernamelabel);
    labeledit->addWidget(this->playernameedit);

    QVBoxLayout* all = new QVBoxLayout;
    all->addLayout(labeledit);
    all->addWidget(validate);

    this->setLayout(all);

    connect(validate, &QPushButton::clicked, this, Playerdialog::slot_validated);
}

Playerdialog::~Playerdialog(){}

/////////////////////// Getters /////////////////////////////////

QString Playerdialog::getPlayername() const{
    return playername;
}

/////////////////////// Slots /////////////////////////////////

void Playerdialog::slot_validated(){
    this->playername = this->playernameedit->text();
    this->playernameedit->clear();
    if(!this->playername.isEmpty())
        this->accept();
}



