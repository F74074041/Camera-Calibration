# 相機校正
## 使用軟體
Visual Studio 2015、OpenCV 3.3.1
## 程式功能
- #### Corner Detection
> 找出15張照片中棋盤的corner。
> 
> ![](https://i.imgur.com/lceTpdZ.png)
> 
- #### Intrinsic Matrix 
> 找出15張照片的內部參數。
> 
> ![](https://i.imgur.com/bAwByZW.png)
> 
- #### Extrinsic Matrix 
> 輸出第N張照片的外部參數。(N=1~15，由使用者輸入)
> 圖片是第一張照片的外部參數。
> ![](https://i.imgur.com/TN1hAPr.png)
- #### Distortion Matrix 
> ``` [-0.1285033045420692,0.1008858560159019,-0.0006246536885478679,0.0004287595745350963, -0.02321046075299173] ```

- #### The Undistorted  Result 
> ![](https://i.imgur.com/Qn2BHrl.png)




