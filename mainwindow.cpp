#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    detector = FaceDetector();
    intervalTimer = new QTimer(this);
    pixmap = new QPixmap();
    scene = new QGraphicsScene();
}

MainWindow::~MainWindow()
{
    delete pixmap;
    delete scene;
    delete intervalTimer;
    delete ui;
}

void MainWindow::on_start_clicked()
{
    capture.open(-1);
    connect(intervalTimer, SIGNAL(timeout()), this, SLOT(capturing()));
    intervalTimer->start(33);
}

void MainWindow::capturing()
{
    capture.read(frame);
    QImage result = detector.detect(frame);
    pixmap = new QPixmap(QPixmap::fromImage(result));
    scene = new QGraphicsScene(ui->graphicsView);
    scene->addPixmap(*pixmap);
    scene->setSceneRect(pixmap->rect());
    ui->graphicsView->setScene(scene);
}

void MainWindow::on_stop_clicked()
{
    intervalTimer->stop();
    disconnect(intervalTimer, SIGNAL(timeout()), this, SLOT(capturing()));
    capture.release();
}
