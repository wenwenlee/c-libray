#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"math.h"
#include "iostream"
#include "string"
#include <cvut.h>
#include <opencv.hpp>
#include "fstream"
#include "gv.h"

using namespace std;
using namespace cvut;



double f1(double x[])
{
	double a[9] = {x[0],0,x[2],
	               0,x[1],x[3],
	               0,0,1
	                          };  
	double b[4] = {x[4],x[5],x[6],x[7]};
	/*double a[9] = {896.387,0,345.335,
	               0,898.084,246.971,
	               0,0,1
	                          };  
	double b[4] = {-0.230964,1.9064,-0.00264958,0.00443806};*/



	Matrix<double> image_points2(1,corner_count,2);
	CvMat intrinsic_matrix = cvMat(3,3,CV_64FC1,a);
    CvMat distortion_coeffs = cvMat(1,4,CV_64FC1,b);
    double err = 0.0,err2=0.0;
	double total_err = 0.0;
	int count = 13;
 
    

	//for (int i = 0; i < image_count; i++)
	for (int i = 0; i < count; i++)
	{
		
		 CvMat* rotation_vectors=cvCreateMat(1,3,CV_64FC1);
        CvMat* translation_vectors=cvCreateMat(1,3,CV_64FC1);

		cvFindExtrinsicCameraParams2( object_points_2.get_cols(i * corner_count,(i+1)*corner_count-1).cvmat,
		        image_points_2.get_cols(i * corner_count,(i+1)*corner_count-1).cvmat,
		          &intrinsic_matrix,
	                    &distortion_coeffs,
	                        rotation_vectors,
	                            translation_vectors
                                     );//根据内参求外参

		cvSave("translation_vectors.xml",translation_vectors);
		
	/*	cvProjectPoints2( object_points_2.get_cols(i * 35,(i+1)*35-1).cvmat, rotation_vectors.get_col(i).cvmat,
      translation_vectors.get_col(i).cvmat,&intrinsic_matrix,
							  &distortion_coeffs, image_points2.cvmat,
                               0,0,0,0); */
							   //重投影误差

		cvProjectPoints2( object_points_2.get_cols(i * corner_count,(i+1)*corner_count-1).cvmat, rotation_vectors,
      translation_vectors,&intrinsic_matrix,
							  &distortion_coeffs, image_points2.cvmat,
                               0,0,0,0);
		//err += cvNorm(image_points_2.get_cols(i*corner_count,(i+1)*corner_count-1).cvmat, image_points2.cvmat, CV_L1);
		/*err = cvNorm(image_points_2.get_cols(i*corner_count,(i+1)*corner_count-1).cvmat, image_points2.cvmat, CV_L1);

		err2 = err*err;*/
		err = cvNorm(image_points_2.get_cols(i*corner_count,(i+1)*corner_count-1).cvmat, image_points2.cvmat, CV_L2);
		err = sqrt(err*err/corner_count);
		total_err += err;

	
	}
	//total_err = err/(corner_count*count);
	total_err = total_err/count;
	//total_err = err/count;
	return total_err;

 


	//return 0;
}

double random()
{
	//srand((int)time(0));
	double a = (rand()%10000)*0.0001;
	return a;
}
void cali()
{
	ifstream fin("data.txt");
	//ofstream fout("result.txt");
	string s;
	
	CvPoint2D32f * image_points_buf = new CvPoint2D32f[board_size.width*board_size.height];
	cout<<board_size.width*board_size.height<<"\n";
    while(getline(fin,s))
	{
		++image_count;
	cout<<image_count<<"\n";
	cout<<s;
	
	 int count;
	cout<<"\n 将鼠标焦点移到标定图像所在窗口并输入回车进行下一幅图像的角点提取 \n";
    Image<uchar> view(s);

	 cvNamedWindow ("windows",CV_WINDOW_AUTOSIZE);
	 cvShowImage("windows",view.cvimage);
	 cvWaitKey();
		if (image_count == 1)
  {
   
   image_size.width = view.size().width;
   image_size.height = view.size().height;
   
  	cout<<image_size.width;
   cout<<"\n";
		 cout<<image_size.height;
   
  }
	
 if (0 == cvFindChessboardCorners( view.cvimage, board_size,
            image_points_buf, &count, CV_CALIB_CB_ADAPTIVE_THRESH ))
   
  {
   cout<<"can not find chessboard corners!\n";
   cout<<image_points_buf;
   exit(1);
  }
 else {
   Image<uchar> view_gray(view.size(),8,1);
   
   rgb2gray(view,view_gray);
   
   
   cvFindCornerSubPix( view_gray.cvimage, image_points_buf, count, cvSize(11,11),
    cvSize(-1,-1), cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));
  
   
   image_points_seq.push_back(image_points_buf,count);
   
   
   cvDrawChessboardCorners( view.cvimage, board_size, image_points_buf, count, 1);
   view.show("calib");
  
   cvWaitKey(); 
   view.close();
  }
 
}
   delete []image_points_buf; 
 cout<<"角点提取完成！\n"<<endl;

  cout<<"开始定标………………"<<"\n"<<endl;
 CvSize square_size = cvSize(30,30); 
 
 
 Matrix<double> object_points(1,board_size.width*board_size.height*image_count,3);
 
 Matrix<double> image_points(1,image_points_seq.cvseq->total,2);
 
 Matrix<int>    point_counts(1,image_count,1);

 int i,j,t;
 for (t=0;t<image_count;t++) {
  for (i=0;i<board_size.height;i++) {
   for (j=0;j<board_size.width;j++) {
    
    
    object_points(0,t*board_size.height*board_size.width + i*board_size.width + j,0) = i*square_size.width;
    object_points(0,t*board_size.height*board_size.width + i*board_size.width + j,1) = j*square_size.height;
    object_points(0,t*board_size.height*board_size.width + i*board_size.width + j,2) = 0;
   }
  }
 }
 cvSave("object_points.xml",object_points.cvmat);/*保存成xml格式，便于调用*/
 char  str[10];
 itoa(image_points_seq.cvseq->total,str,10);
 cout<<str<<"\n"<<endl;
 
 for (i=0;i<image_points_seq.cvseq->total;i++)
 {
  image_points(0,i,0) = image_points_seq[i].x;
  image_points(0,i,1) = image_points_seq[i].y;
 }
 cvSave("image_points.xml",image_points.cvmat);/*保存成xml格式，便于调用*/
 /*for (i=0;i<image_count;i++)
  point_counts(0,i) = board_size.width*board_size.height;*/

 
}

