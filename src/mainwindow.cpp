#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QPainter"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.drawPoints(MainWindow::mandelbrotPunkte.toVector().data(), MainWindow::mandelbrotPunkte.count());
}

double betrag(complex<double> x) {
    return sqrt(x.imag()*x.imag() + x.real()*x.real());
}

complex<double> calc(complex<double> z, complex<double> c) {
    return z*z + c;
}

complex<double> MainWindow::mandelbrot(complex<double> z, complex<double> c, int iter)
{
    complex tmp = calc(z, c);

    if (DEBUG) cout << "iteration #" << iter << ", |z| = " << betrag(tmp) << endl;

    if (iter++ < MainWindow::maxRec)
    {
        return MainWindow::mandelbrot(tmp, c, iter);
    }
    else
    {
        return tmp;
    }
}

bool MainWindow::istInMandelbrotmenge(complex<double> x) {
    complex<double> finalZ = MainWindow::mandelbrot(0, x, 0);
    return betrag(finalZ) < 2;
}

void MainWindow::calculatePoints() {
    cout << "Starting Mandelbrot calculation..." << endl;

    MainWindow::mandelbrotPunkte.clear();

    double startX = MainWindow::startRe * MainWindow::pixelScalingFactor;
    double endX = MainWindow::endRe * MainWindow::pixelScalingFactor;
    double startY = MainWindow::startIm * MainWindow::pixelScalingFactor;
    double endY = MainWindow::endIm * MainWindow::pixelScalingFactor;

    for(int x = startX; x <= endX; x++) {
        for(int y = startY; y >= endY; y--) {
            // convert back from pixel scaling factor for the mathematical part
            double xMath = (double)x / MainWindow::pixelScalingFactor;
            double yMath = (double)y / MainWindow::pixelScalingFactor;
            if(istInMandelbrotmenge(complex<double>(xMath, yMath))) {
                MainWindow::mandelbrotPunkte.append(QPoint(x-startX, abs(y-startY)));        // convert cartesian coordinates to qt pixel system
            }
        }
    }

    cout << "Finished calculating " << MainWindow::mandelbrotPunkte.count() << " points."
         << endl << "Refreshing..." << endl;

    // Refreshing so that MainWindow::paintEvent is called and the points in MainWindow::mandelbrotPunkte are painted
    this->update();
}

// Sets the global variables to the user input
void MainWindow::setProperties() {
    MainWindow::pixelScalingFactor = this->ui->scalingEdit->text().toDouble();
    MainWindow::maxRec = this->ui->recursionEdit->text().toDouble();

    MainWindow::startRe = this->ui->startReEdit->text().toDouble();
    MainWindow::endRe = this->ui->endReEdit->text().toDouble();

    MainWindow::startIm = this->ui->startImEdit->text().toDouble();
    MainWindow::endIm = this->ui->endImEdit->text().toDouble();
}

void MainWindow::on_startButton_clicked()
{
    setProperties();
    calculatePoints();
}

