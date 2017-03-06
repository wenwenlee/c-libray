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

extern   int image_count;
extern   int corner_count;
extern	 CvSize image_size;
extern     CvSize board_size ;
extern	 Seq<CvPoint2D32f> image_points_seq;

extern Matrix<double> object_points_2;
   extern Matrix<double> image_points_2;
   extern CvMat *object_points;
   extern CvMat *image_points;


  // extern Matrix<double> rotation_vectors;
  // extern Matrix<double> translation_vectors;