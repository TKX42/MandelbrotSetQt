#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <complex>

#define DEBUG false

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap *pixmap;
    QList<QPoint> mandelbrotPunkte = QList<QPoint>();

    void setProperties();
    std::complex<double> mandelbrot(std::complex<double> z, std::complex<double> c, int iter);
    bool istInMandelbrotmenge(std::complex<double> x);
    void calculatePoints();

    // cartesian x coordinates
    double startRe = -2;
    double endRe = 1;
    // cartesian y coordinates
    double startIm = 1;
    double endIm = -1;

    // The maximal recursion used in the mandelbrot calculation
    int maxRec = 20;

    // The scaling factor, how the data is presented. For example: scaling 100, startRe = -2, endRe = 1 --> width = 300px
    int pixelScalingFactor = 200;
};
#endif // MAINWINDOW_H
