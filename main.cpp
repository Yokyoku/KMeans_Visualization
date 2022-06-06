//インクルードファイル指定
#include <opencv2/opencv.hpp>

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

#pragma comment(lib, "opencv_features2d" CV_VER CV_EXT)

//自作ヘッダの読み込み
#include "Point.hpp"

#define COLOR_NUM 5
#define CONT_WIDTH 400
#define CONT_LENGTH 100
#define MAX_NUM 100000
int showendflag = 0;
bool buttoncheck = 0; //左クリックの状態を確認
int status = 0; // 行っている分割のステージ 0:スタート状態(色なし) 1:色分け　2: クラスタ重心の表示　3: 点の再塗り分け(2、又は4へ)　4:終了　
int IMAGE_WIDTH;
int IMAGE_LENGTH;
int POINT_NUM;
Point *Points;
float **CoG;
cv::Scalar *Colors = (cv::Scalar*)malloc(sizeof(cv::Scalar) * COLOR_NUM);
int endflag = 0;
int loopcount = 0;
cv::Mat *Controller;
cv::Mat *InputImage; 



double distance(int x1, int y1, int x2, int y2){
	return pow((x2 -x1)*(x2 - x1) +(y2 -y1) * (y2 - y1),0.5);
}
void Batu(int x, int y ,cv::Scalar Color,cv::Mat *img){
	cv::line(*img, cv::Point(x-1.4142*5,y-1.4142*5),cv::Point(x+1.4142*5,y+1.4142*5),Color,3,16);
	cv::line(*img, cv::Point(x+1.4142*5,y-1.4142*5),cv::Point(x-1.4142*5,y+1.4142*5),Color,3,16);
	return;
}

void SetColor(void){
	int random = (unsigned)time(NULL); 
	srand(random);		
	int r,g,b;
	for(int i = 0;i < COLOR_NUM; i++){
			r = rand()%255;
			g = rand()%255;
			b = rand()%255;
			Colors[i] = cv::Scalar(r,g,b);
			for(int j = 0; j < i;j++)//ダブリの確認,およびわかりにくい色の除外
				if(((Colors[i] == Colors[j])&&(i != j))||((r + g +b) > 255)){
					i--;
					break;
				}
		}
}

void ChangeColor(cv::Mat *img){
		int *changeflag = (int *)malloc(sizeof(int)*POINT_NUM);
		cv::Size img_size(IMAGE_WIDTH,IMAGE_LENGTH);
		cv::Mat tmpimg = cv::Mat::zeros(img_size,CV_8UC3);
		img = &tmpimg;
		int tmpcolor = -1;
		double tmpd = 100000;
		int checkcolor[COLOR_NUM];
				for(int i = 0; i < COLOR_NUM;i++)
					checkcolor[i] = 0;
		for(int i = 0;i < POINT_NUM; ++ i){ //所属する色の更新
			for(int j = 0; j < COLOR_NUM; j++){
				if(tmpd >= distance(CoG[j][0],CoG[j][1],Points[i].getPosx(),Points[i].getPosy())){//より近い重心を発見した場合
					tmpd = distance(CoG[j][0],CoG[j][1],Points[i].getPosx(),Points[i].getPosy());
					tmpcolor = j;
					if(Points[i].getColor() != Colors[tmpcolor])
						changeflag[i] = 1;
					else
						changeflag[i] = 0;
				}
			}
			Points[i].changeColor(Colors[tmpcolor]);	
			checkcolor[tmpcolor]++;
			cv::circle(*img,cv::Point(Points[i].getPosx(),Points[i].getPosy()),2,Points[i].getColor(),-1,16);//色付き点の描画
			//初期化
			tmpd = 10000;
			tmpcolor = -1;
			}	

		for(int i = 0; i < COLOR_NUM;i++)
					printf("Color%d : %d\n",i,checkcolor[i]);
		printf("\n\n\n");
		//重心に線を引いていく
			for(int i = 0;i < POINT_NUM;i++){
				for(int j = 0; j < COLOR_NUM;j++)
					if(Points[i].getColor() == Colors[j])
						cv::line(*img,cv::Point(Points[i].getPosx(),Points[i].getPosy()),cv::Point(CoG[j][0],CoG[j][1]),Points[i].getColor(),1,16);
			}
	
		//重心の描画
		for(int i = 0; i < COLOR_NUM;i++)
			Batu(CoG[i][0], CoG[i][1], Colors[i], img);
		
		//終了判定
		int checkflag = 0;
		for(int i = 0; i < POINT_NUM;i++)
			if(changeflag[i] != 0)
				checkflag = 1;
		if(checkflag == 0)
			endflag = 1;


		if(endflag == 1){
			for(int y = 0; y < (*Controller).rows; ++y){
				for(int x = 0; x < (*Controller).cols; ++x){
					// 画像のチャネル数分だけループ。　　
					for(int c = 0; c < (*Controller).channels(); ++c){
						(*Controller).data[ y * (*Controller).step + x * (*Controller).elemSize() + c ] = 0;
					}
				}
			}
				cv::putText(*Controller, "End", cv::Point(50,60), cv::FONT_HERSHEY_SIMPLEX, 1.2, cv::Scalar(0,0,200), 2, 16);
						cv::imshow("Controller",*Controller);
									cv::imwrite("out2.png",*img);

		}


		cv::imshow("image",*img);
	return;


}

void ShowPointsColor(cv::Mat *img){
		cv::Size img_size(IMAGE_WIDTH,IMAGE_LENGTH);
		cv::Mat tmpimg = cv::Mat::zeros(img_size,CV_8UC3);
		img = &tmpimg;
		for(int i = 0;i < POINT_NUM; ++ i){
		//色付きの点の描画
			cv::circle(*img,cv::Point(Points[i].getPosx(),Points[i].getPosy()),2,Points[i].getColor(),-1,16);
		}
		cv::imshow("image",*img);
	return;
}



void ShowCoG(cv::Mat *img){
		cv::Size img_size(IMAGE_WIDTH,IMAGE_LENGTH);
		cv::Mat tmpimg = cv::Mat::zeros(img_size,CV_8UC3);
		img = &tmpimg;

		//CoGの初期化
		for(int i = 0;i < COLOR_NUM;i++){
			CoG[i][0] = 0;
			CoG[i][1] = 0;
		}

		int count = 0;
		for(int i = 0;i < COLOR_NUM;i++){
			for(int j = 0; j < POINT_NUM;j++){
				if(Points[j].getColor() ==Colors[i]){
					CoG[i][0] += Points[j].getPosx();
					CoG[i][1] += Points[j].getPosy();
					count++;
				}
			}
			if(count != 0){
			CoG[i][0] /= count;
			CoG[i][1] /= count;
			}
			else if (count == 0){
				CoG[i][0] = -1000;
				CoG[i][1] = 1000;
			}
			
			count = 0;
		}
		//色付きの点の描画
		for(int i = 0;i < POINT_NUM; ++ i){
			cv::circle(*img,cv::Point(Points[i].getPosx(),Points[i].getPosy()),2,Points[i].getColor(),-1,16);
		}
		//重心の描画
		for(int i = 0; i < COLOR_NUM;i++)
			Batu(CoG[i][0], CoG[i][1], Colors[i], img);
		//重心に線を引いていく
		for(int i = 0;i < POINT_NUM;i++){
			for(int j = 0; j < COLOR_NUM;j++)
				if(Points[i].getColor() == Colors[j])
					cv::line(*img,cv::Point(Points[i].getPosx(),Points[i].getPosy()),cv::Point(CoG[j][0],CoG[j][1]),Points[i].getColor(),1,16);
		}
		//重心の描画
		for(int i = 0; i < COLOR_NUM;i++)
			Batu(CoG[i][0], CoG[i][1], Colors[i], img);
		cv::imshow("image",*img);

	return;
};




void my_mouse_callback(int event, int x, int y, int flags, void* param){
    cv::Mat *image = static_cast<cv::Mat*>(param);

	if(endflag == 0)
    switch (event){

    case cv::EVENT_LBUTTONDOWN:
		if(buttoncheck == 0){
			switch(status){
					case 0:
						printf("0:ShowPointsColor\n");
						loopcount++;
						ShowPointsColor(image);
						break;
					case 1:
						printf("1:Show Centers of the Gravity\n");
						ShowCoG(image);
						break;
					case 2:
						printf("2:Assign Points to New Groups\n");
						ChangeColor(image);
						break;
					default :
						break;
			}
			status++;
			status = status%4;
		}
		buttoncheck = 1;
        break;

    case cv::EVENT_LBUTTONUP:
		if(buttoncheck == 1)
		buttoncheck = 0;
        break;
	}
	else if(endflag == 1)
		if(showendflag == 0){
			printf("End of K-Means(ShowPointsColor was called %d times)\n",loopcount);
			showendflag = 1;
		}
}


int fast_detect( std::string filename )
{
    cv::Mat img = cv ::imread(filename, 1);
	cv::Mat out = cv::Mat::zeros(img.size().height, img.size().width, CV_8UC3);
    if(img.empty()) return -1;
    cv::Mat gray_img;
    cv::cvtColor(img, gray_img, cv::COLOR_BGR2RGBA);
    cv::normalize(gray_img, gray_img, 0, 255, cv::NORM_MINMAX);
    std::vector<cv::KeyPoint> keypoints;
    std::vector<cv::KeyPoint>::iterator itk;
    auto detector = cv::FastFeatureDetector::create(10, false);
    detector->detect(gray_img, keypoints);
    cv::Scalar color(255,255,255);
    for(itk = keypoints.begin(); itk!=keypoints.end(); ++itk)
    {
        cv::circle(out, itk->pt, 1, color, -1);
        if(itk->angle>=0)
        {
            cv::Point pt2(itk->pt.x + cos(itk->angle)*itk->size,
                itk->pt.y +sin(itk->angle)*itk->size);
            cv::line(out, itk->pt, pt2, color, 1, 1);
        }
    }
    cv::imshow("FAST Feature", out);
	cv::imwrite("out1.png",out);
	return 0;
}



int main(int argc, char *argv[])
{/******  MatポインタとしてInputImageを使用しimreadに繋げようとするとバグが出る  ****/
	std::cout << "input filename:" <<std::endl;
	std::string filename;
	std::cin >> filename;

	fast_detect(filename);
	cv::Mat img = cv::imread("out1.png");

	if((img).empty())
		return 0;
	
	InputImage = &img;
	IMAGE_LENGTH = img.rows;
	IMAGE_WIDTH = img.cols;

	cv::Size img_size2(CONT_WIDTH,CONT_LENGTH);

	cv::Mat con = cv::Mat::zeros(img_size2,CV_8UC3);
	Controller = &con;
	//ウィンドウの作成
	cv::namedWindow("image", cv::WINDOW_AUTOSIZE|cv::WINDOW_FREERATIO);
	cv::namedWindow("Controller", cv::WINDOW_AUTOSIZE|cv::WINDOW_FREERATIO);





	//CoGの準備 2*COLOR_NUM行列の準備
		CoG =(float **)malloc(sizeof(float)*COLOR_NUM);
	

		for(int i = 0;i < COLOR_NUM;i++){
			CoG[i] = (float*)malloc(sizeof(int)*2);
			(CoG[i])[0] = 0;
			(CoG[i])[1] = 0;
		}

	//Pointオブジェクトの生成
	Point p[MAX_NUM];		
	Points = p;
	//色の設定
	SetColor();
	int colorcheck[COLOR_NUM];
	for(int i = 0; i < COLOR_NUM;i++)
		colorcheck[i] = 0;

	//点の設定

	int fcount = 0;
	int tmpc;
	int tmpcount = 0;

	for(int y = 0; y < img.rows; ++y){
		for(int x = 0; x < img.cols; ++x){
						if(img.data[ y * img.step + x * img.elemSize()] >= 255){	
							printf("(%d,%d)\n",x,y);
							printf("%d\n",img.data[ y * img.step + x * img.elemSize()]);
							printf("%d\n",img.data[ y * img.step + x * img.elemSize()+1]);
							printf("%d\n",img.data[ y * img.step + x * img.elemSize()]+2);


							tmpc = rand()%COLOR_NUM;
							colorcheck[tmpc]++;
							Points[tmpcount].setCondition(x,y,Colors[tmpc]);
							tmpcount++;						
						}
		}
	}
	POINT_NUM = tmpcount -1;

		for(int i = 0; i < COLOR_NUM;i++)
		printf("Color%d : %d\n",i,colorcheck[i]);
		printf("\n\n\n");



	// コントローラーいろいろ
    cv::setMouseCallback("Controller", my_mouse_callback, (void *)&img);
	cv::putText(con, "Controller", cv::Point(50,60), cv::FONT_HERSHEY_SIMPLEX, 1.2, cv::Scalar(0,0,200), 2, 16);

		cv::Size img_size3(IMAGE_WIDTH,IMAGE_LENGTH);
		img = cv::Mat::zeros(img_size3,CV_8UC3);

	for(int i = 0;i < POINT_NUM; ++ i){
		//はじめての点の描画
		//cv::circle(img,cv::Point(Points[i].getPosx(),Points[i].getPosy()),2,cv::Scalar(255,255,255),-1,16);
	}

		cv::imshow("image",img);
		cv::imshow("Controller",con);



		cv::waitKey(0);
		cv::destroyAllWindows();
		
	return 0;
}