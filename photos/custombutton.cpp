#include "custombutton.h"

CustomButton::CustomButton(QWidget * parent = 0): QPushButton(parent)
{
}
CustomButton::CustomButton()
{

}

CustomButton::CustomButton(QString a, QWidget * parent = 0): QPushButton(parent)
{    
    orginalPicture.load(a);
    isGray = false;

    this->setFlat(true);
    this->setAutoFillBackground(true);
}

CustomButton::~CustomButton()
{

}

