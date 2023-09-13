#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QColorDialog>
#include <cmath>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    connect(ui->bar1,SIGNAL(valueChanged(int)),this,SLOT(on_CMYKScrollBarChanged(int)));
    connect(ui->bar2,SIGNAL(valueChanged(int)),this,SLOT(on_CMYKScrollBarChanged(int)));
    connect(ui->bar3,SIGNAL(valueChanged(int)),this,SLOT(on_CMYKScrollBarChanged(int)));
    connect(ui->bar4,SIGNAL(valueChanged(int)),this,SLOT(on_CMYKScrollBarChanged(int)));

    connect(ui->bar5, SIGNAL(valueChanged(int)),this, SLOT(on_RGBScrollBarChanged(int)));
    connect(ui->bar6, SIGNAL(valueChanged(int)),this, SLOT(on_RGBScrollBarChanged(int)));
    connect(ui->bar7, SIGNAL(valueChanged(int)),this, SLOT(on_RGBScrollBarChanged(int)));

    connect(ui->bar9,SIGNAL(valueChanged(int)),this,SLOT(on_XYZScrollBarChanged(int)));
    connect(ui->bar10,SIGNAL(valueChanged(int)),this,SLOT(on_XYZScrollBarChanged(int)));
    connect(ui->bar11,SIGNAL(valueChanged(int)),this,SLOT(on_XYZScrollBarChanged(int)));

    /* connect(ui->bar13,SIGNAL(valueChanged(int)),this,SLOT(on_LABScrollBarChanged(int)));
        connect(ui->bar14,SIGNAL(valueChanged(int)),this,SLOT(on_LABScrollBarChanged(int)));
        connect(ui->bar15,SIGNAL(valueChanged(int)),this,SLOT(on_LABScrollBarChanged(int)));*/


    connect(ui->l1,SIGNAL(textChanged(QString)),this,SLOT(LineEditCMYKChanged(QString)));
    connect(ui->l2,SIGNAL(textChanged(QString)),this,SLOT(LineEditCMYKChanged(QString)));
    connect(ui->l3,SIGNAL(textChanged(QString)),this,SLOT(LineEditCMYKChanged(QString)));
    connect(ui->l4,SIGNAL(textChanged(QString)),this,SLOT(LineEditCMYKChanged(QString)));

    connect(ui->l5,SIGNAL(textChanged(QString)),this,SLOT(LineEditRGBChanged(QString)));
    connect(ui->l6,SIGNAL(textChanged(QString)),this,SLOT(LineEditRGBChanged(QString)));
    connect(ui->l7,SIGNAL(textChanged(QString)),this,SLOT(LineEditRGBChanged(QString)));

    connect(ui->l9,SIGNAL(textChanged(QString)),this,SLOT(LineEditXYZChanged(QString)));
    connect(ui->l10,SIGNAL(textChanged(QString)),this,SLOT(LineEditXYZChanged(QString)));
    connect(ui->l11,SIGNAL(textChanged(QString)),this,SLOT(LineEditXYZChanged(QString)));

    /*connect(ui->l13,SIGNAL(textChanged(QString)),this,SLOT(LineEditLABChanged(QString)));
        connect(ui->l14,SIGNAL(textChanged(QString)),this,SLOT(LineEditLABChanged(QString)));
        connect(ui->l15,SIGNAL(textChanged(QString)),this,SLOT(LineEditLABChanged(QString)));*/



    updateColorDisplay();
    updateCMYKSlidersAndLabels();
    solutionXYZSlidersAndLabels();
    decisionXYZSlidersAndLabels();

    ui->comboBox->addItem("Cmyk-rgb-xyz");
    ui->comboBox->addItem("rgb-lab-cmyk");

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onComboBoxIndexChanged);

    ui->comboBox->setCurrentIndex(0);


    currentColor = QColor(0, 0, 0);


}

void MainWindow::onComboBoxIndexChanged(int index) {
    switch (index) {
    case 0:

        break;
    }
}

void MainWindow::setValue(QScrollBar *item, int value)
{
    item->blockSignals(true);
    item->setValue(value);
    item->blockSignals(false);
}


void MainWindow::on_RGBScrollBarChanged(int) {

    int r = ui->bar5->value();
    int g = ui->bar6->value();
    int b = ui->bar7->value();

    currentColor.setRgb(r, g, b);

    updateColorDisplay();
    updateCMYKSlidersAndLabels();
    solutionXYZSlidersAndLabels();
    decisionXYZSlidersAndLabels();
}
void MainWindow::updateColorDisplay() {
    QPalette palette = ui->label->palette();
    palette.setColor(QPalette::Window, currentColor);
    ui->label->setPalette(palette);
    ui->label->setAutoFillBackground(true);
    ui->label->update();
    ui->l5->setText(QString::number(currentColor.red()));
    ui->l6->setText(QString::number(currentColor.green()));
    ui->l7->setText(QString::number(currentColor.blue()));

}
void MainWindow::updateRGBScrollBarFromColor(const QColor &color) // для кнопки
{

    int r = color.red();
    int g = color.green();
    int b = color.blue();

    setValue(ui->bar5,r);
    setValue(ui->bar6,g);
    setValue(ui->bar7,b);
    ui->l5->setText(QString::number(r));
    ui->l6->setText(QString::number(g));
    ui->l7->setText(QString::number(b));

    updateCMYKSlidersAndLabels();
    solutionXYZSlidersAndLabels();
    decisionXYZSlidersAndLabels();

}

void MainWindow::LineEditRGBChanged(QString str)
{
    bool ok = true;
    QLineEdit* parent = dynamic_cast<QLineEdit*>(sender());
    uint N = str.toUInt(&ok);
    if (ok and N <= 255){
        if (parent->objectName() == "l5"){
            setValue(ui->bar5,N);
            //ui->bar5->setValue(N);
            r = N;
        }
        if (parent->objectName() == "l6"){
            setValue(ui->bar6,N);
            g = N;
        }
        if (parent->objectName() == "l7"){
            setValue(ui->bar7,N);
            ui->bar7->setValue(N);
            b = N;
        }
    } else{
        ui->l5->setText(QString::number(r));
        ui->l6->setText(QString::number(g));
        ui->l7->setText(QString::number(b));
    }
}







// CMYK
// CMYK
// CMYK







void MainWindow::updateCMYKSlidersAndLabels() {
    int r = ui->bar5->value();
    int g = ui->bar6->value();
    int b = ui->bar7->value();

    double k = std::min({1.0 - r / 255.0, 1.0 - g / 255.0, 1.0 - b / 255.0});

    double c = (1.0 - r / 255.0 - k) / (1.0 - k);
    double m = (1.0 - g / 255.0 - k) / (1.0 - k);
    double y = (1.0 - b / 255.0 - k) / (1.0 - k);

    int cInt = qRound(c * 100.0);
    int mInt = qRound(m * 100.0);
    int yInt = qRound(y * 100.0);
    int kInt = qRound(k * 100.0);

    if (kInt == 100){cInt = 100; mInt=100; yInt=100;}

    // Устанавливаем значения ползунков CMYK
    setValue(ui->bar1,cInt);
    setValue(ui->bar2,mInt);
    setValue(ui->bar3,yInt);
    setValue(ui->bar4,kInt);
    //    ui->bar1->setValue(cInt);
    //    ui->bar2->setValue(mInt);
    //    ui->bar3->setValue(yInt);
    //    ui->bar4->setValue(kInt);

    ui->l1->setText(QString::number(cInt));
    ui->l2->setText(QString::number(mInt));
    ui->l3->setText(QString::number(yInt));
    ui->l4->setText(QString::number(kInt));
}

void MainWindow::on_CMYKScrollBarChanged(int) {
    double c = ui->bar1->value();
    double m = ui->bar2->value();
    double y = ui->bar3->value();
    double k = ui->bar4->value();

    ui->bar1->setValue(c);
    ui->bar2->setValue(m);
    ui->bar3->setValue(y);
    ui->bar4->setValue(k);
    ui->l1->setText(QString::number(c));
    ui->l2->setText(QString::number(m));
    ui->l3->setText(QString::number(y));
    ui->l4->setText(QString::number(k));


    int r = static_cast<int>(255 * (1 - c/100) * (1 - k/100));
    int g = static_cast<int>(255 * (1 - m/100) * (1 - k/100));
    int b = static_cast<int>(255 * (1 - y/100) * (1 - k/100));


    setValue(ui->bar5,r);
    setValue(ui->bar6,g);
    setValue(ui->bar7,b);
    //    ui->bar5->setValue(r);
    //    ui->bar6->setValue(g);
    //    ui->bar7->setValue(b);

    currentColor.setRgb(r, g, b);

    updateColorDisplay();
    solutionXYZSlidersAndLabels();
    decisionXYZSlidersAndLabels();
}

void MainWindow::LineEditCMYKChanged(QString str)
{
    bool ok = true;
    QLineEdit* parent = dynamic_cast<QLineEdit*>(sender());
    uint N = str.toUInt(&ok);
    if (ok and N <= 100){
        if (parent->objectName() == "l1"){
            setValue(ui->bar1,N);
            //ui->bar5->setValue(N);
            c = N;
        }
        if (parent->objectName() == "l2"){
            setValue(ui->bar2,N);
            m = N;
        }
        if (parent->objectName() == "l3"){
            setValue(ui->bar3,N);
            //ui->bar3->setValue(N);
            y = N;
        }
        if (parent->objectName() == "l4"){
            setValue(ui->bar4,N);
            //ui->bar4->setValue(N);
            k = N;
        }
    } else{
        ui->l1->setText(QString::number(c));
        ui->l2->setText(QString::number(m));
        ui->l3->setText(QString::number(y));
        ui->l4->setText(QString::number(k));
    }
}






// XYZ
// XYZ
// XYZ






void MainWindow::solutionXYZSlidersAndLabels(){
    double r = ui->bar5->value();
    double g = ui->bar6->value();
    double b = ui->bar7->value();
    double rn;
    double gn;
    double bn;

    if( r/255 >= 0.04045)
    {
        rn = pow((((r / 255)+ 0.055)/ 1.055),2.4);
        rn *= 100;
    }
    else
    {
        rn = (r / 255)/12.92;
        rn *= 100;
    }

    if( g/255 >= 0.04045)
    {
        gn = pow((((g / 255)+ 0.055)/ 1.055),2.4);
        gn *= 100;
    }
    else
    {
        gn = (g / 255)/12.92;
        gn *= 100;
    }

    if( b/255 >= 0.04045)
    {
        bn = pow((((b / 255)+ 0.055)/ 1.055),2.4);
        bn *= 100;
    }
    else
    {
        bn = (b / 255)/12.92;
        bn *= 100;
    }

    X = 0.412453 * rn + 0.357580 * gn + 0.180423 * bn;

    Y = 0.212671 * rn + 0.715160 * gn + 0.072169 * bn;
    Z = 0.019334 * rn + 0.119193 * gn + 0.950227 * bn;

}

void MainWindow::decisionXYZSlidersAndLabels(){
    X = qRound(X);
    Y = qRound(Y);
    Z = qRound(Z);


    setValue(ui->bar9,X);
    setValue(ui->bar10,Y);
    setValue(ui->bar11,Z);
    //    ui->bar9->setValue(xInt);
    //    ui->bar10->setValue(yInt);
    //    ui->bar11->setValue(zInt);

    ui->l9->setText(QString::number(X));
    ui->l10->setText(QString::number(Y));
    ui->l11->setText(QString::number(Z));

}

void MainWindow::on_XYZScrollBarChanged(int) {


    double x = ui->bar9->value();
    double y = ui->bar10->value() ;
    double z = ui->bar11->value() ;

    setValue(ui->bar9,x);
    setValue(ui->bar10,y);
    setValue(ui->bar11,z);

    //    ui->bar9->setValue(x);
    //    ui->bar10->setValue(y);
    //    ui->bar11->setValue(z);
    ui->l9->setText(QString::number(x));
    ui->l10->setText(QString::number(y));
    ui->l11->setText(QString::number(z));


    x /= 100.0;
    y /= 100.0;
    z /= 100.0;

    double r = 3.2406 * x - 1.5372 * y - 0.4986 * z;
    double g = -0.9689 * x + 1.8758 * y + 0.0415 * z;
    double b = 0.0557 * x - 0.2040 * y + 1.0570 * z;

    if (r >= 0.0031308) {
        r = pow(r, 1/2.4) * 1.055 - 0.055;
    } else {
        r *= 12.92;
    }

    if (g >= 0.0031308) {
        g = pow(g, 1/2.4) * 1.055 - 0.055;
    } else {
        g *= 12.92;
    }

    if (b >= 0.0031308) {
        b = pow(b, 1/2.4) * 1.055 - 0.055;
    } else {
        b *= 12.92;
    }

    r*=255;
    g*=255;
    b*=255;

    if(r<0){
        r = 0;

    }else if(r>255){
        r = 255;

    }
    if(g<0){
        g = 0;

    }else if(g>255){
        g = 255;

    }
    if(b<0){
        b = 0;

    }else if(b>255){
        b = 255;

    }

    int R = (int)r;
    int G = (int)g;
    int B = (int)b;

    setValue(ui->bar5,R);
    setValue(ui->bar6,G);
    setValue(ui->bar7,B);

    //    ui->bar5->setValue(R);
    //    ui->bar6->setValue(G);
    //    ui->bar7->setValue(B);

    currentColor.setRgb(R, G, B);

    updateColorDisplay();
    updateCMYKSlidersAndLabels();



}

void MainWindow::LineEditXYZChanged(QString str)
{
    bool ok = true;
    QLineEdit* parent = dynamic_cast<QLineEdit*>(sender());
    uint N = str.toUInt(&ok);

    if(ok and N <= 109){
        if (parent->objectName() == "l11"){
            setValue(ui->bar11,N);
            //ui->bar3->setValue(N);
            Z = N;
        }


        if (parent->objectName() == "l10"){
            setValue(ui->bar10,N);
            //ui->bar5->setValue(N);
            Y = N;
        }


        if (parent->objectName() == "l9"){
            setValue(ui->bar9,N);
            X = N;
        }
    }

    else{
        ui->l9->setText(QString::number(X));
        ui->l10->setText(QString::number(Y));
        ui->l11->setText(QString::number(Z));
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QColor selectedColor = QColorDialog::getColor(currentColor, this, "Выберите цвет");

    if (selectedColor.isValid()) {
        currentColor = selectedColor;
        updateColorDisplay();
        updateCMYKSlidersAndLabels();
        solutionXYZSlidersAndLabels();
        decisionXYZSlidersAndLabels();
        updateRGBScrollBarFromColor(currentColor);
    }
}








/// LAB
/// LAB
/// LAB
/// LAB
/// LAB






/*
void MainWindow::solutionLABSlidersAndLabels() {

    solutionXYZSlidersAndLabels();

    if((X / 95.047) >= 0.008856){
        L = cbrt((X / 95.047));
    }
    else
        L = 7.787 * X + 16/116;

    if((Y / 100) >= 0.008856){
        A = cbrt((X / 95.047));
    }
    else
        A = 7.787 * X + 16/116;

    if((Z / 108.883) >= 0.008856){
        B = cbrt((X / 95.047));
    }
    else
        B = 7.787 * X + 16/116;


    A = 500 * (L - A);
    B = 200 * (L - B);
    L = 116 * L - 16;

}



void MainWindow::on_LABScrollBarChanged(int) {


    L = ui->bar13->value();
    A = ui->bar14->value() ;
    B = ui->bar15->value() ;

    setValue(ui->bar13,L);
    setValue(ui->bar14,A);
    setValue(ui->bar15,B);

    //    ui->bar9->setValue(x);
    //    ui->bar10->setValue(y);
    //    ui->bar11->setValue(z);
    ui->l13->setText(QString::number(L));
    ui->l14->setText(QString::number(A));
    ui->l15->setText(QString::number(B));

    if(pow(L + 16, 3)>=0.008856){
        Y = pow(L + 16, 3) / 116 * 95.047;
    }
    else Y = ((L + 16)- 16/116) * 7.787;

    if(pow(A/ 500 + (L+16)/116,3)>=0.008856){
        X = pow(A/ 500 + (L+16)/116,3);
    }
    else X = (A/ 500 + (L+16)/116 - 16/116) / 7.787;

    if(pow((L+16)/116-B/200,3)>=0.008856){
        Z = pow((L+16)/116-B/200,3);
    }
    Z = ((L+16)/116-B/200 - 16/116)/7.787;


     X = (int)X;
     Y = (int)Y;
     Z = (int)Z;

    setValue(ui->bar5,X);
    setValue(ui->bar6,Y);
    setValue(ui->bar7,Z);

 // add
    // add



}

void MainWindow::LineEditLABChanged(QString str)
{
    bool ok = true;
    QLineEdit* parent = dynamic_cast<QLineEdit*>(sender());
    uint N = str.toUInt(&ok);

    if(ok and N <= 128){
        if (parent->objectName() == "l13"){
            setValue(ui->bar13,N);
            //ui->bar3->setValue(N);
            B = N;
        }


        if (parent->objectName() == "l14"){
            setValue(ui->bar14,N);
            //ui->bar5->setValue(N);
            A = N;
        }


        if (parent->objectName() == "l15"){
            setValue(ui->bar15,N);
            L = N;
        }
    }

    else{
        ui->l13->setText(QString::number(L));
        ui->l14->setText(QString::number(A));
        ui->l15->setText(QString::number(B));
    }
}*/
































