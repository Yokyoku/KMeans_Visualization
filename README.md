# KMeans_Visualization
A program that clusters the input image using the KMeans(K=5) method and visualizes the process.  
入力画像に対してKMeans法(K=5)でのクラスタリングを施し、その過程を可視化するプログラム

# Requirement
open-cv 4.2.0  

# Usage
1. Enter the target image name.  
2. The black-and-white point cloud image calculated by the FAST feature, the controller window, and the clustered image are displayed. The number of this color can be set from COLOR_NUM in main.cpp. At this time, a black and white point cloud image is output as out1.png.  
3. The state of clustering can be advanced one step by clicking the controller window.  
4. Click the controller window.  
5. First, apply 5 random colors to each point cloud in the point cloud image.  
6. Calculate the center of gravity points of the points of each color, connect each color point cloud and the center of gravity points of each color, and visualize the clustering situation.  
7. For each point, reassign the color to the center of gravity point that is the closest to each color.  
8. Repeat 4 ~ 7, and when the color of all points does not change, it ends and the result is output as out2.png.  

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
As the input image (target_input.png), you can see the pictures of 5 spherical objects, and in the final output image (out2.png), you can see that the 5 colored spherical objects are color-coded.  
  
例として、入力画像としてtarget_input.png、中間生成される白黒点群画像としてout1.png、最終出力画像としてout2.pngを用意しました。  
入力画像(target_input.png)としては5個の球状の物体の写真を採用し、最終出力画像(out2.png)では5色の球状の物体が色分けされているのが分かると思います。  
