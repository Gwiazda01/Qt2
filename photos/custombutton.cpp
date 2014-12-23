#include "custombutton.h"

CustomButton::CustomButton(QWidget * parent = 0): QPushButton(parent)
{
}
CustomButton::CustomButton()
{

}

CustomButton::CustomButton(QString a, QWidget * parent = 0): QPushButton(parent)
{    
    originalPicture.load(a);
    filePath = a;
    originalFilePath = a;
    isGray = false;

    this->setFlat(true);
    this->setAutoFillBackground(true);
}
CustomButton::~CustomButton()
{

}

