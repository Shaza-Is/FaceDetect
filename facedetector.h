#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H
//opencv inculdes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"

//qt & C++ includes
#include <QImage>
#include <vector>

using namespace cv;
class FaceDetector
{
public:
    FaceDetector();

public slots:
    QImage detect(Mat frame);

private:
    String                   face_cascade_name;
    CascadeClassifier        face_cascade;
    std::vector<Rect>        foundFaces;
    QList<CvScalar>          colorsCol;
};

#endif // FACEDETECTOR_H
