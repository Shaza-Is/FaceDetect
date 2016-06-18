#include "facedetector.h"
#include <QDebug>
FaceDetector::FaceDetector()
{
    face_cascade_name = "/home/shaza/Desktop/Projects/AvidBeam/InterviewTask/FaceDetect/haarcascade_frontalface_default.xml";
    if( !face_cascade.load( face_cascade_name ) ){ qDebug() << "--(!)Error loading\n";}

    /*8 colors collection*/
    colorsCol   << cvScalar(0.0,0.0,255.0)   << cvScalar(0.0,128.0,255.0)
                << cvScalar(0.0,255.0,255.0) << cvScalar(0.0,255.0,0.0)
                << cvScalar(255.0,128.0,0.0) << cvScalar(255.0,255.0,0.0)
                << cvScalar(255.0,0.0,0.0)   << cvScalar(255.0,0.0,255.0);
}

QImage FaceDetector::detect(Mat frame)
{
    Mat frame_gray;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //Detection
    face_cascade.detectMultiScale(frame_gray,
                                  foundFaces,
                                   1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));

    int n = foundFaces.size();
    //Draw rectangles around faces
    CvRect rect;
    for(int i = 0; i < n ; i++)
    {
        rect = foundFaces[i];
        rectangle(frame, cvPoint(rect.x, rect.y),
                    cvPoint((rect.x + rect.width), (rect.y + rect.height)),
                    colorsCol[i%8]);
    }

    // Convert Mat to QImage
    QImage result = QImage((const uchar *)frame.data,
                                          frame.cols,
                                          frame.rows,
                                          frame.step,
                                          QImage::Format_RGB888).rgbSwapped();
    return result;
}

