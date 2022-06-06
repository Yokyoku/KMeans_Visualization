//インクルードファイル指定
#include <opencv2/opencv.hpp>
#include <stdlib.h>
//自作ヘッダの読み込み
#include "Point.hpp"

void Point::setCondition(int x, int y, cv::Scalar Color){
	pos_x = x;
	pos_y = y;
	color = Color;
	return;
}
int Point::getPosx(void){
	return pos_x;
}
int Point::getPosy(void){
	return pos_y;
}
void Point::changePosx(int x){
	pos_x = x;
}
void Point::changePosy(int y){
	pos_y = y;
}
cv::Scalar Point::getColor(void){
	return color;
}
void Point::changeColor(cv::Scalar S){
	color = S;
}