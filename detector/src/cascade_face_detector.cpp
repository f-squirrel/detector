#include "cascade_face_detector.h"
#include "detector_exception.h"

namespace detector {

CvSeq* detectFaceInImage(IplImage *inputImg, CvHaarClassifierCascade* cascade) {
	// Smallest face size.
	CvSize minFeatureSize = cvSize(20, 20);
	
	CvMemStorage* storage = cvCreateMemStorage(0);
	cvClearMemStorage( storage );

	// If the image is color, use a greyscale copy of the image.
	IplImage *detectImg = (IplImage*)inputImg;
	IplImage* greyImg = 0;
	if (inputImg->nChannels > 1) {
		CvSize size = cvSize(inputImg->width, inputImg->height);
		greyImg = cvCreateImage(size, IPL_DEPTH_8U, 1 );
		cvCvtColor( inputImg, greyImg, CV_BGR2GRAY );
		detectImg = greyImg;	// Use the greyscale image.
	}

	// Detect all the faces in the greyscale image.
	double t = (double)cvGetTickCount();
	CvSeq* rects = cvHaarDetectObjects( detectImg, cascade, storage,
			1.1f, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_DO_ROUGH_SEARCH, minFeatureSize);

	t = (double)cvGetTickCount() - t;
	int ms = cvRound( t / ((double)cvGetTickFrequency() * 1000.0) );
	int nFaces = rects->total;
	std::cout << "Face Detection took " << ms << " ms and found " << nFaces << " objects\n";
		
	if (greyImg)
		cvReleaseImage( &greyImg );

	return rects;
}

cascade_face_detector::cascade_face_detector(const std::string& cascade_file_name, bool use_cpp_detect) : m_cascade(cascade_file_name), m_cascade_file_name(cascade_file_name), m_use_cpp_detect(use_cpp_detect) {}

cascade_face_detector::~cascade_face_detector() {}

	void cascade_face_detector::c_detect(cv::Mat source_image) {
	CvRect rc;
	IplImage * isource = &source_image.operator IplImage();
	CvHaarClassifierCascade* faceCascade = (CvHaarClassifierCascade*)cvLoad(m_cascade_file_name.c_str(), 0, 0, 0);
		
	CvSeq* rects = detectFaceInImage(isource, faceCascade);
	std::cout << "faces detected: " << rects->total << std::endl;
		
	for( int i = 0; i < rects->total; i++ ) {
		rc = *(CvRect*)cvGetSeqElem( rects, i );
		cv::rectangle(source_image, rc, cv::Scalar(255, 0, 0), 4);
	}
	cvReleaseMemStorage( &(rects->storage) );
	cvReleaseHaarClassifierCascade( &faceCascade );
}
	
void cascade_face_detector::cpp_detect(cv::Mat source_image) {
	cv::Mat frame_gray;
	cv::cvtColor(source_image, frame_gray, CV_BGR2GRAY);
	cv::equalizeHist(frame_gray, frame_gray);

	std::vector<cv::Rect> faces;
	// detect faces
	double t = (double)cvGetTickCount();
	m_cascade.detectMultiScale( frame_gray, faces, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_DO_ROUGH_SEARCH, cv::Size(30, 30) );
	t = (double)cvGetTickCount() - t;
	int ms = cvRound( t / ((double)cvGetTickFrequency() * 1000.0) );
	std::cout << "Face Detection took " << ms << " ms and found " <<  faces.size() << " objects\n";

	for( size_t i = 0; i < faces.size(); i++ ) {
		cv::rectangle(source_image, faces[i], cv::Scalar(255, 0, 0), 4);
	}
}

void cascade_face_detector::detect(cv::Mat source_image) {
	if (!is_ready()) {
		throw detector_runtime_exception("Detector is not ready: cascade is empty\n");
	}

	if (m_use_cpp_detect) {
		cpp_detect(source_image);
	}
	else {
		c_detect(source_image);
	}
}

}