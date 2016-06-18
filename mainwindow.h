#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QTimer>
#include "facedetector.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_start_clicked();
    void capturing();
    void on_stop_clicked();

private:
    Ui::MainWindow *ui;
    VideoCapture    capture;
    Mat             frame;
    FaceDetector    detector;
    QPixmap        *pixmap;
    QTimer         *intervalTimer;
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
