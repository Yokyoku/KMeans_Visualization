//インクルードファイル指定
#include <opencv2/opencv.hpp>
#include <stdlib.h>

#ifndef _INC_POINT
#define _INC_POINT

class Point{
	private:
		int pos_x,pos_y,flag;
		cv::Scalar color;
	public:
		 void setCondition(int x, int y, cv::Scalar Color);
		 int getPosx(void);
		 int getPosy(void);
		 cv::Scalar getColor(void);

		 void changePosx(int);
		 void changePosy(int);
		 void changeColor(cv::Scalar);
};
#endif