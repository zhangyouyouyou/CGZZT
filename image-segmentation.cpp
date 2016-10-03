#include<iostream> 
#include<opencv2/opencv.hpp>
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include<opencv2/imgproc/imgproc.hpp>
#include<fstream>

using namespace cv; 
using namespace std;

static int beginning1=0;
static int beginning2=30;
static int beginning3=60;

int length1=35;
int length2=35;
int length3=35;

int height_=0;

int main()
{	
	ifstream file;
	file.open("f:\\zhongwenma.txt");
	if(!file){
		cerr<<"zhongwenma.txt open error!"<<endl;
		exit(1);
	}
	while(!file.eof())
	{
		char txt_cont[20];
		file.getline(txt_cont,20);
		char img_file[20];
		sprintf(img_file,"f:/cnma/%s",txt_cont);

		char filename1[9],filename2[9],filename3[9],filename4[9];
		for(int i=0;i<9;i++)
		{
			filename1[i]=NULL;
			filename2[i]=NULL;
			filename3[i]=NULL;
			filename4[i]=NULL;			
		}
		for(int i=0;i<3;i++)
		{
			filename1[i]=img_file[i+8];
			filename2[i]=img_file[i+8];
			filename3[i]=img_file[i+8];
			filename4[i]=img_file[i+8];			
		}
		filename1[3]=49; filename1[4]=46;filename1[5]=106;filename1[6]=112;filename1[7]=103;
		filename2[3]=50; filename2[4]=46;filename2[5]=106;filename2[6]=112;filename2[7]=103;
		filename3[3]=51; filename3[4]=46;filename3[5]=106;filename3[6]=112;filename3[7]=103;
		filename4[3]=52; filename4[4]=46;filename4[5]=106;filename4[6]=112;filename4[7]=103;
				
		char savename1[20],savename2[20],savename3[20],savename4[20];
		sprintf(savename1,"f:/save2/%s",filename1);
		sprintf(savename2,"f:/save2/%s",filename2);
		sprintf(savename3,"f:/save2/%s",filename3);
		sprintf(savename4,"f:/save2/%s",filename4);
		
		/*Mat src_gray;
		Mat src_=imread(img_file);
		
		threshold(src_,src_gray,130,255,1);
		imwrite(savename1,src_gray);*/

		IplImage *src_=cvLoadImage(img_file,0);//src_灰度图读入，即单通道
		
		CvScalar s;

		for(int i=0;i<src_->height;i++)//减少颜色数量处理
		{
			for(int j=0;j<src_->width;j++)
			{
				s=cvGet2D(src_,i,j);
				if(s.val[0]>130)
					s.val[0]=0;
				else
					s.val[0]=255-s.val[0];
				cvSet2D(src_,i,j,s);
			}
		}
		cvSaveImage(savename1,src_);//保存单通道图

		IplImage *src=cvLoadImage(savename1);
	
		IplImage *src1=cvCreateImage(cvSize(length1,40),IPL_DEPTH_8U,3);

		for(int i=0;i<src1->height;i++)
		{
			for(int j=0;j<src1->width;j++)
			{
				s=cvGet2D(src1,i,j);
				s.val[0]=0;
				/*s.val[1]=0;
				s.val[2]=0;*/
				cvSet2D(src1,i,j,s);
			}
		}
		
		for(int i=height_;i<40;i++)
		{
			for(int j=0;j<length1;j++)
			{
				s=cvGet2D(src,i,j+beginning1);
				cvSet2D(src1,i-height_,j,s);
			}
		}

		cvSaveImage(savename2,src1);
		Mat src11=imread(savename2);
		resize(src11,src11,Size(28,28),0,0,CV_INTER_LINEAR);
		imwrite(savename2,src11);
		//////////////////////////////////////////////////////////////////
		IplImage *src2=cvCreateImage(cvSize(length2,40),IPL_DEPTH_8U,3);
		/*cvZero(src2);*/

		for(int i=0;i<src2->height;i++)
		{
			for(int j=0;j<src2->width;j++)
			{
				s=cvGet2D(src2,i,j);
				s.val[0]=0;
				/*s.val[1]=0;
				s.val[2]=0;*/
				cvSet2D(src2,i,j,s);
			}
		}

		for(int i=height_;i<40;i++)
		{
			for(int j=0;j<length2;j++)
			{
				s=cvGet2D(src,i,j+beginning2);
				cvSet2D(src2,i-height_,j,s);
			}
		}
		cvSaveImage(savename3,src2);
		Mat src22=imread(savename3);
		resize(src22,src22,Size(28,28),0,0,CV_INTER_LINEAR);
		imwrite(savename3,src22);
		////////////////////////////////////////////
		IplImage *src3=cvCreateImage(cvSize(length3,40),IPL_DEPTH_8U,3);
		/*cvZero(src3);*/

		for(int i=0;i<src3->height;i++)
		{
			for(int j=0;j<src3->width;j++)
			{
				s=cvGet2D(src3,i,j);
				s.val[0]=0;
				/*s.val[1]=0;
				s.val[2]=0;*/
				cvSet2D(src3,i,j,s);
			}
		}

		for(int i=height_;i<40;i++)
		{
			for(int j=0;j<length3;j++)
			{
				s=cvGet2D(src,i,j+beginning3);
				cvSet2D(src3,i-height_,j,s);
			}
		}

		cvSaveImage(savename4,src3);
		Mat src33=imread(savename4);
		resize(src33,src33,Size(28,28),0,0,CV_INTER_LINEAR);
		imwrite(savename4,src33);

	}
	file.close();
	
	while(char (waitKey(1))!='q') {}

	return 0;
}

	
	