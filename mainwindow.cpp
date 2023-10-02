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
    widgets["CMYK"] = ui->CMYK_widget;
    widgets["RGB"] = ui->RGB_widget;
    widgets["XYZ"] = ui->XYZ_widget;
    widgets["LAB"] = ui->LAB_widget;
    widgets["HSV"] = ui->HSV_widget;
    widgets["HSL"] = ui->HSL_widget;
    ui->XYZ_widget->hide();
    ui->HSV_widget->hide();
    ui->HSL_widget->hide();


    //    auto LAB_geometry = ui->LAB_widget->geometry();
    //    ui->LAB_widget->setGeometry(ui->RGB_widget->geometry());
    //    ui->RGB_widget->setGeometry();

    geometry_array[0] = ui->RGB_widget->geometry();
    geometry_array[1] = ui->LAB_widget->geometry();
    geometry_array[2] = ui->CMYK_widget->geometry();

    //    ui->CMYK_widget->hide();
    //    ui->RGB_widget->hide();
    //    ui->XYZ_widget->hide();
    //   ui->LAB_widget->hide();

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

    connect(ui->bar13,SIGNAL(valueChanged(int)),this,SLOT(on_LABScrollBarChanged(int)));
    connect(ui->bar14,SIGNAL(valueChanged(int)),this,SLOT(on_LABScrollBarChanged(int)));
    connect(ui->bar15,SIGNAL(valueChanged(int)),this,SLOT(on_LABScrollBarChanged(int)));

    connect(ui->bar17,SIGNAL(valueChanged(int)),this,SLOT(on_HSVScrollBarChanged(int)));
    connect(ui->bar18,SIGNAL(valueChanged(int)),this,SLOT(on_HSVScrollBarChanged(int)));
    connect(ui->bar19,SIGNAL(valueChanged(int)),this,SLOT(on_HSVScrollBarChanged(int)));

    connect(ui->bar20,SIGNAL(valueChanged(int)),this,SLOT(on_HSLScrollBarChanged(int)));
    connect(ui->bar21,SIGNAL(valueChanged(int)),this,SLOT(on_HSLScrollBarChanged(int)));
    connect(ui->bar22,SIGNAL(valueChanged(int)),this,SLOT(on_HSLScrollBarChanged(int)));


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

    connect(ui->l13,SIGNAL(textChanged(QString)),this,SLOT(LineEditLABChanged(QString)));
    connect(ui->l14,SIGNAL(textChanged(QString)),this,SLOT(LineEditLABChanged(QString)));
    connect(ui->l15,SIGNAL(textChanged(QString)),this,SLOT(LineEditLABChanged(QString)));

    connect(ui->l17,SIGNAL(textChanged(QString)),this,SLOT(LineEditHSVChanged(QString)));
    connect(ui->l18,SIGNAL(textChanged(QString)),this,SLOT(LineEditHSVChanged(QString)));
    connect(ui->l19,SIGNAL(textChanged(QString)),this,SLOT(LineEditHSVChanged(QString)));

    connect(ui->l20,SIGNAL(textChanged(QString)),this,SLOT(LineEditHSLChanged(QString)));
    connect(ui->l21,SIGNAL(textChanged(QString)),this,SLOT(LineEditHSLChanged(QString)));
    connect(ui->l22,SIGNAL(textChanged(QString)),this,SLOT(LineEditHSLChanged(QString)));

    connect(ui->lineEdit, SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_textEdited(const QString &)));


    updateColorDisplay();
    updateCMYKSlidersAndLabels();
    updateXYZSlidersAndLabels();
    updateLABSlidersAndLabels();
    updateHSVSlidersAndLabels();
    updateHSLSlidersAndLabels();

    //    ui->comboBox->addItem("Cmyk-rgb-xyz");
    //    ui->comboBox->addItem("rgb-lab-cmyk");

    currentColor = QColor(0, 0, 0);
    //    ui->comboBox->setCurrentText("CMYK-RGB-XYZ");

}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    bool ok;
    if (arg1.length() == 7 and arg1[0] == '#'){
        QString s(arg1);
        s.remove(0,1);
        if (s.toInt(&ok,16)){
            currentColor.setNamedColor(arg1);
            updateColorDisplay();
            updateCMYKSlidersAndLabels();
            updateXYZSlidersAndLabels();
            updateLABSlidersAndLabels();
            updateHSVSlidersAndLabels();
            updateHSLSlidersAndLabels();
        }
    }

}

void MainWindow::updateLineEditFromRGB(int r, int g, int b)
{
    QString colorCode = QString("#%1%2%3")
                            .arg(r, 2, 16, QLatin1Char('0'))
                            .arg(g, 2, 16, QLatin1Char('0'))
                            .arg(b, 2, 16, QLatin1Char('0'));
ui->lineEdit->blockSignals(true);
    ui->lineEdit->setText(colorCode);
ui->lineEdit->blockSignals(false);
}

void MainWindow::setValue(QScrollBar *item, int value)
{
    item->blockSignals(true);
    item->setValue(value);
    item->blockSignals(false);
}


void MainWindow::on_RGBScrollBarChanged(int) {

    r = ui->bar5->value();
    g = ui->bar6->value();
    b = ui->bar7->value();

    currentColor.setRgb(r, g, b);

    updateColorDisplay();
    updateCMYKSlidersAndLabels();
    updateXYZSlidersAndLabels();
    updateLABSlidersAndLabels();
    updateHSVSlidersAndLabels();
    updateHSLSlidersAndLabels();
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
    updateLineEditFromRGB(r, g, b);

}



void MainWindow::updateRGBScrollBarFromColor(const QColor &color) // для кнопки
{

    r = color.red();
    g = color.green();
    b = color.blue();

    setValue(ui->bar5,r);
    setValue(ui->bar6,g);
    setValue(ui->bar7,b);

    ui->l5->setText(QString::number(r));
    ui->l6->setText(QString::number(g));
    ui->l7->setText(QString::number(b));

    updateCMYKSlidersAndLabels();
    updateXYZSlidersAndLabels();
    updateLABSlidersAndLabels();
    updateHSVSlidersAndLabels();
    updateHSLSlidersAndLabels();

}

void MainWindow::LineEditRGBChanged(QString str)
{
    bool ok = true;
    QLineEdit* parent = dynamic_cast<QLineEdit*>(sender());
    uint N = str.toUInt(&ok);
    if (str.isEmpty()) {
        N = 0.0;
    } else
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

    double cInt = (c * 100.0);
    double mInt = (m * 100.0);
    double yInt = (y * 100.0);
    double kInt = (k * 100.0);

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
    updateXYZSlidersAndLabels();
    updateLABSlidersAndLabels();
    updateHSVSlidersAndLabels();
    updateHSLSlidersAndLabels();
}

void MainWindow::LineEditCMYKChanged(QString str)
{
    bool ok = true;
    QLineEdit* parent = dynamic_cast<QLineEdit*>(sender());
    double N = str.toDouble(&ok);
    if (str.isEmpty()) {
        N = 0.0;
    } else
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






void MainWindow::updateXYZSlidersAndLabels(){
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

void MainWindow::update_widget(QWidget *widget, QRect geometry)
{
    widget->setGeometry(geometry);
    widget->show();
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

    int R = r;
    int G = g;
    int B = b;

    setValue(ui->bar5,R);
    setValue(ui->bar6,G);
    setValue(ui->bar7,B);

    //    ui->bar5->setValue(R);
    //    ui->bar6->setValue(G);
    //    ui->bar7->setValue(B);

    currentColor.setRgb(R, G, B);

    updateColorDisplay();
    updateCMYKSlidersAndLabels();
    updateLABSlidersAndLabels();
    updateHSVSlidersAndLabels();
    updateHSLSlidersAndLabels();


}

void MainWindow::LineEditXYZChanged(QString str)
{
    bool ok = true;
    QLineEdit* parent = dynamic_cast<QLineEdit*>(sender());
    double N = str.toDouble(&ok);
    if (str.isEmpty()) {
        N = 0.0;
    } else
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
        updateXYZSlidersAndLabels();
        updateLABSlidersAndLabels();
        updateHSVSlidersAndLabels();
        updateHSLSlidersAndLabels();
        updateRGBScrollBarFromColor(currentColor);
    }
}








/// LAB
/// LAB
/// LAB
/// LAB
/// LAB







void MainWindow::updateLABSlidersAndLabels() {

    //    double fx;
    //    double fy;
    //    double fz;

    //    if((X / 95.047) >= 0.008856){
    //        fx = cbrt((X / 95.047));
    //    }
    //    else
    //        fx = (903.3*(X / 95.047)+16)/116;

    //    if((Y / 100) >= 0.008856){
    //        fy = cbrt((Y / 100));
    //    }
    //    else
    //        fy = (903.3*(Y / 100)+16)/116;

    //    if((Z / 108.883) >= 0.008856){
    //        fz = cbrt((Z / 108.883));
    //    }
    //    else
    //        fz = (903.3*(Z / 108.883)+16)/116;

    //    L = 116 * fy - 16;
    //    A = 500 *(fx - fy);
    //    B = 20* (fy - fz);


    if((Y / 100) >= 0.008856){
        L = cbrt(Y / 100);
    }
    else
        L = 7.787 * (Y / 100) + 0.137931;

    if((X / 95.047) >= 0.008856){
        A = cbrt((X / 95.047));
    }
    else
        A = 7.787 * (X / 95.047) + 0.137931;

    if((Z / 108.883) >= 0.008856){
        B = cbrt((Z / 108.883));
    }
    else
        B = 7.787 * (Z / 108.883) + 0.137931;

    A = (500 * (A - L));
    B = (200 * (L - B));
    L = ((116 * L) - 16);

    if (L > 100) L = 100;
    if (L < 0) L = 0;
    if (B > 128) B = 128;
    if (B < -128) B = -128;
    if (A > 128) A = 128;
    if (A < -128) A = -128;


    setValue(ui->bar13,L);
    setValue(ui->bar14,A);
    setValue(ui->bar15,B);


    ui->l13->setText(QString::number(L));
    ui->l14->setText(QString::number(A));
    ui->l15->setText(QString::number(B));

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

    if(pow((A/ 500) + (L+16)/116,3)>=0.008856){
        X = (pow((A/ 500) + (L+16)/116,3)) * 95.047;
    }
    else X = (116 * ((A/ 500) + (L+16)/116) - 16) / 903.3 * 95.047;
    if (X > 95.047) X = 95.047;
    if (X < 0) X = 0;

    if(pow((L + 16)/116, 3)>=0.008856){
        Y = pow((L + 16)/116, 3) * 100;
    }
    else Y = L / 903 * 100;
    if (Y<0) Y = 0;
    if (Y > 100) Y = 100;

    if(pow((L+16)/116-B/200,3)>=0.008856){
        Z =pow((L+16)/116-B/200,3) * 108.883;
    }
    else Z = (116 *((L+16)/116-B/200 - 16)/ 903.3 * 108.883);
    if (Z<0) Z = 0;
    if (Z > 108.883) Z = 108.883;

    //    if(pow((L + 16)/116, 3)>=0.008856){
    //        X = pow((L + 16)/116, 3) * 95.047;
    //    }
    //    else X = ((L + 16)/116 - 16/116) * 7.787;
    //    int d;
    //    if (Y<0) Y = 0;

    //    if(pow((A/ 500) + (L+16)/116,3)>=0.008856){
    //        Y = pow(A/ 500 + (L+16)/116,3) * 100;
    //    }
    //    else Y = (A/ 500 + (L+16)/116 - 16/116) / 7.787 * 100;
    //    if (X<0) X = 0;

    //    if(pow((L+16)/116-B/200,3)>=0.008856){
    //        Z = pow((L+16)/116-B/200,3) * 108.883;
    //    }
    //    Z = ((L+16)/116-B/200 - 16/116)/7.787* 108.883;
    //    if (Z<0) Z = 0;


    setValue(ui->bar9,X);
    setValue(ui->bar10,Y);
    setValue(ui->bar11,Z);

    ui->l9->setText(QString::number(X));
    ui->l10->setText(QString::number(Y));
    ui->l11->setText(QString::number(Z));


    X /= 100.0;
    Y /= 100.0;
    Z /= 100.0;

    double r = 3.2406 * X - 1.5372 * Y - 0.4986 * Z;
    double g = -0.9689 * X + 1.8758 * Y + 0.0415 * Z;
    double b = 0.0557 * X - 0.2040 * Y + 1.0570 * Z;

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

    setValue(ui->bar5,r);
    setValue(ui->bar6,g);
    setValue(ui->bar7,b);

    //    ui->bar5->setValue(R);
    //    ui->bar6->setValue(G);
    //    ui->bar7->setValue(B);

    currentColor.setRgb(r, g, b);

    updateColorDisplay();
    updateCMYKSlidersAndLabels();
    updateHSVSlidersAndLabels();
    updateHSLSlidersAndLabels();

}

void MainWindow::LineEditLABChanged(QString str)
{
    bool ok = true;
    QLineEdit* parent = dynamic_cast<QLineEdit*>(sender());
    double N = str.toDouble(&ok);
    if (str.isEmpty()) {
        N = 0.0;
    } else
    if(ok and N <= 128 and N>=-128){
        if (parent->objectName() == "l15"){
            setValue(ui->bar15,N);
            //ui->bar3->setValue(N);
            B = N;
        }


        if (parent->objectName() == "l14"){
            setValue(ui->bar14,N);
            //ui->bar5->setValue(N);
            A = N;
        }


        if (parent->objectName() == "l13"){
            if (N >= 0 and N <= 100){
                setValue(ui->bar13,N);
                L = N;
            } else{
                ui->l13->setText(QString::number(L));
            }
        }
    }

    else{
        ui->l13->setText(QString::number(L));
        ui->l14->setText(QString::number(A));
        ui->l15->setText(QString::number(B));
    }

}



void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    ui->CMYK_widget->hide();
    ui->RGB_widget->hide();
    ui->XYZ_widget->hide();
    ui->LAB_widget->hide();
    ui->HSV_widget->hide();
    ui->HSL_widget->hide();
    QStringList array;
    int dotPosition = arg1.indexOf('.');
    if (dotPosition != -1) {
        QString substring = arg1.mid(dotPosition + 1);
        array = substring.split("-");
    }


    update_widget(widgets[array[0]],geometry_array[0]);
    update_widget(widgets[array[1]],geometry_array[1]);
    update_widget(widgets[array[2]],geometry_array[2]);
}




// HSV
// HSV
// HSV



void MainWindow::updateHSVSlidersAndLabels() {
    double R = r / 255.0;
    double G = g / 255.0;
    double B = b / 255.0;

    double modRgb[3] = {R, G, B};
    double cmax = std::max({R, G, B});
    double cmin = std::min({R, G, B});
    double diff = cmax - cmin;


    if (cmax == cmin) {
        h = 0;
    } else if (cmax == modRgb[0]) {
        h = fmod(60 * ((modRgb[1] - modRgb[2]) / diff) + 360, 360);
    } else if (cmax == modRgb[1]) {
        h = fmod(60 * ((modRgb[2] - modRgb[0]) / diff) + 120, 360);
    } else if (cmax == modRgb[2]) {
        h = fmod(60 * ((modRgb[0] - modRgb[1]) / diff) + 240, 360);
    }

    s = (cmax == 0) ? 0 : (diff / cmax) * 100;
    v = cmax * 100;

    if (h < 0) h = 0;
    setValue(ui->bar17, h);
    setValue(ui->bar18, s);
    setValue(ui->bar19, v);

    ui->l17->setText(QString::number(h));
    ui->l18->setText(QString::number(s));
    ui->l19->setText(QString::number(v));
}




void MainWindow::on_HSVScrollBarChanged(int) {
    h = ui->bar17->value();
    s = ui->bar18->value();
    v = ui->bar19->value();

    ui->bar17->setValue(h);
    ui->bar18->setValue(s);
    ui->bar19->setValue(v);

    ui->l17->setText(QString::number(h));
    ui->l18->setText(QString::number(s));
    ui->l19->setText(QString::number(v));

    double C = (static_cast<double>(s) / 100) * (static_cast<double>(v) / 100);
    double X = C * (1 - std::abs(static_cast<double>(h) / 60.0 - 1));
    double m = (static_cast<double>(v) / 100) - C;

    fromHS(h, C, X, m, r, g, b);

    setValue(ui->bar5, r);
    setValue(ui->bar6, g);
    setValue(ui->bar7, b);
    currentColor.setRgb(r, g, b);
    updateColorDisplay();
    updateCMYKSlidersAndLabels();
    updateLABSlidersAndLabels();
    updateXYZSlidersAndLabels();
    updateHSLSlidersAndLabels();
}


void MainWindow::fromHS(int h, double C, double X, double m, int& r, int& g, int& b) {
    double rgb[3] = {0, 0, 0};

    if (h >= 0 && h < 60) {
        rgb[0] = C;
        rgb[1] = X;
        rgb[2] = 0;
    } else if (h >= 60 && h < 120) {
        rgb[0] = X;
        rgb[1] = C;
        rgb[2] = 0;
    } else if (h >= 120 && h < 180) {
        rgb[0] = 0;
        rgb[1] = C;
        rgb[2] = X;
    } else if (h >= 180 && h < 240) {
        rgb[0] = 0;
        rgb[1] = X;
        rgb[2] = C;
    } else if (h >= 240 && h < 300) {
        rgb[0] = X;
        rgb[1] = 0;
        rgb[2] = C;
    } else if (h >= 300 && h < 360) {
        rgb[0] = C;
        rgb[1] = 0;
        rgb[2] = X;
    }

    for (int i = 0; i < 3; i++) {
        rgb[i] += m;
        rgb[i] *= 255;
    }

    int clr[3];
    for (int i = 0; i < 3; i++) {
        if (rgb[i] > 255) {
            clr[i] = 255;
        } else if (rgb[i] < 0) {
            clr[i] = 0;
        } else {
            clr[i] = static_cast<int>(rgb[i]);
        }
    }

    r = clr[0];
    g = clr[1];
    b = clr[2];
}



void MainWindow::LineEditHSVChanged(QString str){

    bool ok = true;
    QLineEdit* parent = dynamic_cast<QLineEdit*>(sender());
    double N = str.toDouble(&ok);
    if (str.isEmpty()) {
        N = 0.0;
    } else
    if(ok and N <= 360 and N >= 0){
        if (parent->objectName() == "l20"){
            setValue(ui->bar17,N);
            //ui->bar3->setValue(N);
            h = N;
        }


        if (parent->objectName() == "l21"){
            if (N <= 100){
                setValue(ui->bar18,N);
                s = N;
            } else{
                ui->l18->setText(QString::number(s));
            }
        }


        if (parent->objectName() == "l22"){
            if (N <= 100){
                setValue(ui->bar19,N);
                v = N;
            } else{
                ui->l19->setText(QString::number(v));
            }
        }

    }

    else{
        ui->l17->setText(QString::number(h));
        ui->l18->setText(QString::number(s));
        ui->l19->setText(QString::number(v));
    }


}




// HSL
// HSL
// HSL

void MainWindow::updateHSLSlidersAndLabels() {
    double R = r / 255.0;
    double G = g / 255.0;
    double B = b / 255.0;

    double modRgb[3] = {R, G, B};
    double cmax = std::max({R, G, B});
    double cmin = std::min({R, G, B});
    double diff = cmax - cmin;

    if (cmax == cmin) {
        H = 0;
    } else if (cmax == modRgb[0]) {
        H = fmod(60 * ((modRgb[1] - modRgb[2]) / diff) + 360, 360);
    } else if (cmax == modRgb[1]) {
        H = fmod(60 * ((modRgb[2] - modRgb[0]) / diff) + 120, 360);
    } else if (cmax == modRgb[2]) {
        H = fmod(60 * ((modRgb[0] - modRgb[1]) / diff) + 240, 360);
    }

    l = (cmax + cmin) / 2.0;

    if (cmax == cmin) {
        S = 0;
    } else if (l <= 0.5) {
        S = (diff / (cmax + cmin)) * 100;
    } else {
        S = (diff / (2.0 - cmax - cmin)) * 100;
    }

    l *= 100; // Приводим L к диапазону [0, 100]

    if (H < 0) H = 0;
    setValue(ui->bar20, H);
    setValue(ui->bar21, S);
    setValue(ui->bar22, l);

    ui->l20->setText(QString::number(H));
    ui->l21->setText(QString::number(S));
    ui->l22->setText(QString::number(l));
}





void MainWindow::on_HSLScrollBarChanged(int) {
    H = ui->bar20->value();
    S = ui->bar21->value();
    l = ui->bar22->value();

    ui->bar20->setValue(H);
    ui->bar21->setValue(S);
    ui->bar22->setValue(l);

    ui->l20->setText(QString::number(H));
    ui->l21->setText(QString::number(S));
    ui->l22->setText(QString::number(l));

    double C = (1 - std::abs(2 * l / 100 - 1)) * S / 100;
    double X = C * (1 - std::fabs(std::fmod(H / 60.0, 2.0) - 1.0));
    double m = l / 100 - C / 2;

    int r, g, b;
    fromHS(H, C, X, m, r, g, b);

    setValue(ui->bar5, r);
    setValue(ui->bar6, g);
    setValue(ui->bar7, b);
    currentColor.setRgb(r, g, b);
    updateColorDisplay();
    updateCMYKSlidersAndLabels();
    updateLABSlidersAndLabels();
    updateXYZSlidersAndLabels();
    updateHSVSlidersAndLabels();
}


void MainWindow::LineEditHSLChanged(QString str){

    bool ok = true;
    QLineEdit* parent = dynamic_cast<QLineEdit*>(sender());
    double N = str.toDouble(&ok);
    if (str.isEmpty()) {
        N = 0.0;
    } else
    if(ok and N <= 360 and N >= 0){
        if (parent->objectName() == "l20"){
            setValue(ui->bar20,N);
            //ui->bar3->setValue(N);
            H = N;
        }


        if (parent->objectName() == "l21"){
            if (N <= 100){
                setValue(ui->bar21,N);
                S = N;
            } else{
                ui->l21->setText(QString::number(S));
            }
        }


        if (parent->objectName() == "l22"){
            if (N <= 100){
                setValue(ui->bar22,N);
                l = N;
            } else{
                ui->l22->setText(QString::number(l));
            }
        }
    }

    else{
        ui->l20->setText(QString::number(H));
        ui->l21->setText(QString::number(S));
        ui->l22->setText(QString::number(l));
    }


}













