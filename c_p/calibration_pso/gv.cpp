#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"math.h"
#include "iostream"
#include "string"
#include <cvut.h>
#include <opencv.hpp>
#include "fstream"

using namespace std;
using namespace cvut;


int image_count=0;
	 CvSize image_size;
     CvSize board_size = cvSize(6,9);
	 int corner_count = board_size.width*board_size.height;
	 Seq<CvPoint2D32f> image_points_seq;
	 
	  CvMat *object_points = (CvMat*)cvLoad("object_points.xml");
    CvMat *image_points = (CvMat*)cvLoad("image_points.xml");

	Matrix<double> object_points_2 = (CvMat*)cvLoad("object_points.xml");
	Matrix<double> image_points_2 = (CvMat*)cvLoad("image_points.xml");

	//Matrix<double> rotation_vectors = (CvMat*)cvLoad("rotation_vectors.xml");
 //Matrix<double> translation_vectors = (CvMat*)cvLoad("translation_vectors.xml");

	//Matrix<double> object_points2(1,board_size.width*board_size.height*image_count,3);
 
// Matrix<double> image_points2(1,image_points_seq.cvseq->total,2);