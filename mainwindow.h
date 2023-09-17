#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include <map>
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
    std::map<QString,QWidget*> widgets;
    Ui::MainWindow *ui;
    QColor currentColor;
    void fromHS(int h, double C, double X, double m, int& r, int& g, int& b);
    void updateColorDisplay();
    void updateRGBScrollBarFromColor(const QColor &color);
    void updateCMYKScrollBarFromColor(const QColor &color);
    void updateCMYKSlidersAndLabels();
    void updateLABSlidersAndLabels();
    void updateXYZSlidersAndLabels();
    void updateHSVSlidersAndLabels();
    void updateHSLSlidersAndLabels();
    void update_widget(QWidget* widget,QRect geometry);
    void setValue(QScrollBar* item, int value);
    void updateLineEditFromRGB(int r, int g, int b);

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

    double h;
    double s;
    double v;

    double H;
    double S;
    double l;


    QRect geometry_array[3];
private slots:
    void on_RGBScrollBarChanged(int);
    void on_CMYKScrollBarChanged(int);
    void on_XYZScrollBarChanged(int);
    void on_LABScrollBarChanged(int);
    void on_HSVScrollBarChanged(int);
    void on_HSLScrollBarChanged(int);

    void LineEditRGBChanged(QString str);
    void LineEditXYZChanged(QString str);
    void LineEditCMYKChanged(QString str);
    void LineEditLABChanged(QString str);
    void LineEditHSVChanged(QString str);
    void LineEditHSLChanged(QString str);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);
};

#endif // MAINWINDOW_H
