#include "MyView.h"

//////////////////////// Constructor / Destructor /////////////////////

MyView::MyView(){

    //Deactivate scrollbars

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

MyView::~MyView(){}
