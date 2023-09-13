#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QColor currentColor;

    void onComboBoxIndexChanged(int index);

    void updateColorDisplay();
    void updateRGBScrollBarFromColor(const QColor &color);
    void updateCMYKScrollBarFromColor(const QColor &color);
    void updateCMYKSlidersAndLabels();

    void solutionXYZSlidersAndLabels();
    void decisionXYZSlidersAndLabels();

    /*void solutionLABSlidersAndLabels();*/

    /*void updateLABSlidersAndLabels();*/
    void setValue(QScrollBar* item, int value);

    int r;
    int g;
    int b;

    double c;
    double m;
    double y;
    double k;

    double X;
    double Y;
    double Z;

    double L;
    double A;
    double B;

private slots:
    void on_RGBScrollBarChanged(int);
    void on_CMYKScrollBarChanged(int);
    void on_XYZScrollBarChanged(int);
    /* void on_LABScrollBarChanged(int);*/

    void LineEditRGBChanged(QString str);
    void LineEditXYZChanged(QString str);
    void LineEditCMYKChanged(QString str);
    /*void LineEditLABChanged(QString str);*/



    void on_pushButton_clicked();

};

#endif // MAINWINDOW_H
