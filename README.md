# KMeans_Visualization
A program that clusters the input image using the KMeans(K=5) method and visualizes the process.  
入力画像に対してKMeans法(K=5)でのクラスタリングを施し、その過程を可視化するプログラム

# Requirement
open-cv 4.2.0  

# Usage
1. Enter the target image name.  
![input_interface](https://user-images.githubusercontent.com/17018251/172254012-2046f46d-ef13-4089-88c0-df0f2c45cea4.png)  
![test_input](https://user-images.githubusercontent.com/17018251/172253876-8146c9e3-a792-48e4-9018-76488579af04.png)  

2. The black-and-white point cloud image calculated by the FAST feature, the controller window, and the clustered image are displayed. The number of this color can be set from COLOR_NUM in main.cpp. At this time, a black and white point cloud image is output as out1.png.  
![out1](https://user-images.githubusercontent.com/17018251/172254166-350762cb-c0f9-4fc3-b7a3-dde1aa94674a.png)  
![phase1_1](https://user-images.githubusercontent.com/17018251/172256486-b7e3f29d-b7ee-4206-98d5-58eb5e0d0f55.png)  
![Controller1](https://user-images.githubusercontent.com/17018251/172254196-a2a0caf4-0bc8-4fc7-939d-3a677e1d41b2.png)  

3. The state of clustering can be advanced one step by clicking the controller window.  
4. Click the controller window.  
5. First, apply 5 random colors to each point clud in the point cloud image.  
![phase1_2](https://user-images.githubusercontent.com/17018251/172256545-d6c7dd2d-b8c6-4c64-82fe-4260f5382644.png)  


6. Calculate the center of gravity points of the points of each color, connect each color point cloud and the center of gravity points of each color, and visualize the clustering situation.  
![phase1_3](https://user-images.githubusercontent.com/17018251/172256571-595ca3fe-049f-4765-bbe8-a867bbd47cb5.png)  


7. For each point, reassign the color to the center of gravity point that is the closest to each color.  
![phase1_4](https://user-images.githubusercontent.com/17018251/172256609-1e9820dd-0272-4991-899f-8405f01a82e9.png)  
![phase1_5](https://user-images.githubusercontent.com/17018251/172256619-39d7524a-5a2a-4779-96c7-b288243f3269.png)  


8. Repeat 4 ~ 7, and when the color of all points does not change, it ends and the result is output as out2.png.  
![phase_END](https://user-images.githubusercontent.com/17018251/172256823-70caac04-1e6d-4a10-a788-328cd37585eb.png)  
 


1.対象画像名を入力します。  
2.FAST特徴量によって算出された白黒の点群画像とコントローラーウィンドウ、クラスタリングされた画像が表示されます。この色の数はmain.cpp内のCOLOR_NUMから設定できます。このとき、out1.pngとして白黒の点群画像が出力されます。  
3.クラスタリングの様子はコントローラーウィンドウをクリックすることで一段階進むようになっています。  
4.コントローラーウィンドウをクリックします。  
5.まず、点群画像の各点群に対してランダムな5色の色を塗ります。  
6.各色の点の重心点を算出し、各色点群と各色の重心点をつなぎクラスタリング状況を可視化します。  
7.各点に対し、各色の最も距離が近い重心点に色を割り振りなおします。  
8.4~7を繰り返し、すべての点の色が変化しなくなったら終了となり、結果をout2.pngとして出力します。  
  
# Sample
As an example, we have prepared target_input.png as the input image, out1.png as the intermediate generated black and white point cloud image, and out2.png as the final output image.  
As the input image (test_input.png), you can see the pictures of 5 spherical objects, and in the final output image (out2.png), you can see that the 5 colored spherical objects are color-coded.  
![test_input](https://user-images.githubusercontent.com/17018251/172256710-3770ba84-adfe-4aad-a168-e3b3fc2eb0b0.png)  
![out1](https://user-images.githubusercontent.com/17018251/172256723-20574e13-52eb-4484-9d41-e294b2a3f710.png)  
![out2](https://user-images.githubusercontent.com/17018251/172256732-78df98a4-40df-4222-ae06-4b3d34289ea7.png)  
  
  
例として、入力画像としてtarget_input.png、中間生成される白黒点群画像としてout1.png、最終出力画像としてout2.pngを用意しました。  
入力画像(test_input.png)としては5個の球状の物体の写真を採用し、最終出力画像(out2.png)では5色の球状の物体が色分けされているのが分かると思います。  
