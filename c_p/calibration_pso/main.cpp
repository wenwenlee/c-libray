#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"math.h"
#include "iostream"
#include "string"
#include <cvut.h>
#include <opencv.hpp>
#include "fstream"
#include "function.h"
#include "gv.h"

//using namespace std;
using namespace cvut;
using namespace std;
 
const int NUM=40;//粒子数
const int DIM=8;//维数
const int DIM2=13;//维数
const int N = 160;

double c1;
double c2;
double w ;
double gbestx[DIM2];//全局最优位置
double gbestf;//全局最优适应度

double xmin[DIM2]={514,517,269,189,-0.5,-0.5,-0.5,-0.5,1,0.1,1,0.1,6};
double xmax[DIM2]={614,617,319,289,0.5,0.5,0.5,0.5,3,1,3,1,20};
double Vmax[DIM2];
double Vmin[DIM2];
double pbestf[NUM];
double pbestx[NUM][DIM2];
double x2[NUM][DIM2];
double v2[NUM][DIM2];
double fit;

void setv()
{
for (int i = 0; i < DIM2; i++)
{
	Vmax[i] = (xmax[i]-xmin[i])/x2[i][12];
	Vmin[i] = 0-Vmax[i];
}
}
void init()  
{
	 for(int i=0; i<NUM; i++) //初始化粒子群
	   {             
           for(int j=0; j<DIM2; j++)
			   {
				   x2[i][j]=random()*(xmax[j]-xmin[j])+xmin[j];
				    v2[i][j]=0.0; 
				
	                                                     	}
          pbestf[i]=f1(x2[i]);	
		
		   
       }
	  for(int i=0; i<DIM2; i++)//初始化全局最优
		{
			gbestx[i]=random()*(xmax[i]-xmin[i])+xmin[i];
	     }
            gbestf=f1(gbestx);
	
}
int main()
{
	ofstream fout("result160.txt");
	//cali();
	init();
	setv();
	for (int n = 0; n < N; n++)
	{
		
		for (int i = 0; i < NUM; i++)
		{
			double Wmax = x2[i][8];
           double Wmin = x2[i][9];
            double cmax = x2[i][10];
           double cmin = x2[i][11];
		    double w = Wmax-(Wmax-Wmin)*n/N;
	       double c1 = cmax-(cmax-cmin)*n/N;
	       double c2 = cmin+(cmax-cmin)*n/N;
		   setv();
			for (int j = 0; j < DIM2; j++)
			{
				v2[i][j]=w*v2[i][j]+c1*random()*(pbestx[i][j]-x2[i][j])+c2*random()*(gbestx[j]-x2[i][j]);
			
				if (v2[i][j]>Vmax[j])
			        {
						 
				              v2[i][j]=Vmax[j];
			                                      }
		      	else if (v2[i][j]<Vmin[j])
			        {
						 
				               v2[i][j]=Vmin[j];
				
			                                       }
			
				x2[i][j]=v2[i][j]+x2[i][j];
				if (x2[i][j]>xmax[j])
			        {
						
				               x2[i][j]=xmax[j];
							 
							  
			        }
		      	else if (x2[i][j]<xmin[j])
			        {
						
				              x2[i][j]=xmax[j];
				
			        }
			
			}
			
		
			if(pbestf[i]>f1(x2[i])) //改变历史最优
			  {
				
				
				     pbestf[i]=f1(x2[i]);
                     for(int j=0;j<DIM2;j++)
			         	{
					         pbestx[i][j]=x2[i][j];
     						
				        }
					
               }
			if(gbestf>f1(x2[i])) //改变全局最优
			  {
				
				     gbestf=f1(x2[i]);
                     for(int j=0;j<DIM2;j++)
			         	{
					         gbestx[j]=x2[i][j];	 
				        }
				
               }
			
			
		}
	}

	
	 cout<<"gbestf:"<<gbestf<<"\n";
	 fout<<"gbestf：\n";
     fout<<gbestf<<'\n';
	for (int i = 0; i < DIM2; i++)
	{
		cout<<gbestx[i]<<"\n";
		
        fout<<gbestx[i]<<'\n';

	}
}




