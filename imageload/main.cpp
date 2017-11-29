//-----------------------------------【程序说明】----------------------------------------------  
//  程序名称:：【OpenCV入门教程之三】图像的载入，显示与输出 一站式完全解析 博文配套源码  
// VS2010版   OpenCV版本：2.4.8  
//      2014年3月5日 Create by 浅墨  
//  描述： 图像的载入，显示与输出 一站式剖析   配套源码  
//  图片素材出处：dota2原画圣堂刺客 dota2 logo  动漫人物  
//------------------------------------------------------------------------------------------------  
   
   
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>
#include<unistd.h>  
#include<iostream>
#include<string>
 
using namespace cv; 
using namespace std; 
void Help(string param[], int size);
void LoadImage();
bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();
bool MultiChannelBlending();
bool Track_bar_display();

string all_command[] = {
	"End Test",
	"Show Help",
	"Load Image",
	"ROI_AddImage",
	"LinearBlending",
	"ROI_LinearBlending",
	"MultiChannelBlending",
	"Track_bar_display"
};

void Help(string param[], int size)
{
	printf("select :\n");
	for(int i = 0; i < size; i++)
	{
		printf("%d-%s\n", i, param[i].c_str());
	}
}

int main( )  
{  
	int select = 1;
	while((select < sizeof(all_command)/sizeof(all_command[0])) && select != 0)
	{
		Help(all_command, sizeof(all_command)/sizeof(all_command[0]));
		cin >> select;
		printf("%s\n", all_command[select].c_str());

		if(all_command[select] == "Load Image")
		{
			LoadImage();
		}
		else if (all_command[select] == "ROI_AddImage")
		{
			ROI_AddImage();
		}
		else if (all_command[select] == "LinearBlending")
		{
			LinearBlending();
		}
		else if (all_command[select] == "ROI_LinearBlending")
		{
			ROI_LinearBlending();
		}
		else if (all_command[select] == "MultiChannelBlending")
		{
		   if(MultiChannelBlending())  
		   {  
				  cout<<endl<<"嗯。好了，得出了你需要的混合值图像~";  
		   }  
		}
		else if (all_command[select] == "Track_bar_display")
		{
			Track_bar_display();
		}
		waitKey(0);  
   	}
	return 0;  
}  

//----------------------------------【LoadImage( )函数】----------------------------------  
// 函数名：LoadImage（）  
//     描述：图像加载 
//----------------------------------------------------------------------------------------------  
void LoadImage()
{
	//-----------------------------------【一、图像的载入和显示】--------------------------------------  
	//     描述：以下三行代码用于完成图像的载入和显示  
	//--------------------------------------------------------------------------------------------------  
	   
	Mat girl=imread("/work/cv/basesample/CVSample/imageload/image/girl.jpg"); //载入图像到Mat  
	namedWindow("【1】动漫图"); //创建一个名为 "【1】动漫图"的窗口   
	imshow("【1】动漫图",girl);//显示名为 "【1】动漫图"的窗口   
	   
	//-----------------------------------【二、初级图像混合】--------------------------------------  
	//     描述：二、初级图像混合  
	//-----------------------------------------------------------------------------------------------  
	//载入图片  
	Mat image= imread("/work/cv/basesample/CVSample/imageload/image/dota.jpg",199);  
	Mat logo= imread("/work/cv/basesample/CVSample/imageload/image/dota_logo.jpg");  
	   
	//载入后先显示  
	namedWindow("【2】原画图");  
	imshow("【2】原画图",image);  
	   
	namedWindow("【3】logo图");  
	imshow("【3】logo图",logo);  
	 /*
	//定义一个Mat类型，用于存放，图像的ROI  
	Mat imageROI;  
	//方法一  
	//imageROI=image(Rect(800,350,logo.cols,logo.rows));  
	//方法二  
	imageROI=image(Range(350,350+logo.rows),Range(800,800+logo.cols));  
	   
	//将logo加到原图上  
	addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);  
	   
	//显示结果  
	namedWindow("【4】原画+logo图");  
	imshow("【4】原画+logo图",image);  
	   
	//-----------------------------------【三、图像的输出】--------------------------------------  
	//     描述：将一个Mat图像输出到图像文件  
	//-----------------------------------------------------------------------------------------------  
	//输出一张jpg图片到工程目录下  
	imwrite("我喜欢打dota2 by浅墨.jpg",image);  
	*/ 
	//waitKey(); 

}


//----------------------------------【ROI_AddImage( )函数】----------------------------------  
// 函数名：ROI_AddImage（）  
//     描述：利用感兴趣区域ROI实现图像叠加  
//----------------------------------------------------------------------------------------------  
bool ROI_AddImage()  
{  
   
       //【1】读入图像  
       Mat srcImage1= imread("/work/cv/basesample/CVSample/imageload/image/dota.jpg");  
       Mat logoImage= imread("/work/cv/basesample/CVSample/imageload/image/dota_logo.jpg");  
       if(!srcImage1.data ) { printf("你妹，读取srcImage1错误~！ \n"); return false; }  
       if(!logoImage.data ) { printf("你妹，读取logoImage错误~！ \n"); return false; }  
   
       //【2】定义一个Mat类型并给其设定ROI区域  
       Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));  
   
       //【3】加载掩模（必须是灰度图）  
       Mat mask= imread("/work/cv/basesample/CVSample/imageload/image/dota_logo.jpg",0);  
   
       //【4】将掩膜拷贝到ROI  
       logoImage.copyTo(imageROI,mask);  
   
       //【5】显示结果  
       namedWindow("<1>利用ROI实现图像叠加示例窗口");  
       imshow("<1>利用ROI实现图像叠加示例窗口",srcImage1);  
       //waitKey();
       return true;  
}  


//---------------------------------【LinearBlending（）函数】-------------------------------------  
// 函数名：LinearBlending（）  
// 描述：利用cv::addWeighted（）函数实现图像线性混合  
//--------------------------------------------------------------------------------------------  
bool LinearBlending()  
{  
       //【0】定义一些局部变量  
       double alphaValue = 0.5;  
       double betaValue;  
       Mat srcImage2, srcImage3, dstImage;  
   
       //【1】读取图像 ( 两幅图片需为同样的类型和尺寸 )  
       srcImage2= imread("/work/cv/basesample/CVSample/imageload/image/mogu.jpg");  
       srcImage3= imread("/work/cv/basesample/CVSample/imageload/image/rain.jpg");  
   
       if(!srcImage2.data ) { printf("你妹，读取srcImage2错误~！ \n"); return false; }  
       if(!srcImage3.data ) { printf("你妹，读取srcImage3错误~！ \n"); return false; }  
   
       //【2】做图像混合加权操作  
       betaValue= ( 1.0 - alphaValue );  
       addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);  
   
       //【3】创建并显示原图窗口  
       namedWindow("<2>线性混合示例窗口【原图】 by浅墨", 1);  
       imshow("<2>线性混合示例窗口【原图】 by浅墨", srcImage2 );  
   
       namedWindow("<3>线性混合示例窗口【效果图】 by浅墨", 1);  
       imshow("<3>线性混合示例窗口【效果图】 by浅墨", dstImage );  
   	//waitKey(); 
       return true;  
        
}  


//---------------------------------【ROI_LinearBlending（）】-------------------------------------  
// 函数名：ROI_LinearBlending（）  
// 描述：线性混合实现函数,指定区域线性图像混合.利用cv::addWeighted（）函数结合定义  
//                     感兴趣区域ROI，实现自定义区域的线性混合  
//--------------------------------------------------------------------------------------------  
bool ROI_LinearBlending()  
{  
   
       //【1】读取图像  
       Mat srcImage4= imread("/work/cv/basesample/CVSample/imageload/image/dota.jpg",1);  
       Mat logoImage= imread("/work/cv/basesample/CVSample/imageload/image/dota_logo.jpg");  
   
       if(!srcImage4.data ) { printf("你妹，读取srcImage4错误~！ \n"); return false; }  
       if(!logoImage.data ) { printf("你妹，读取logoImage错误~！ \n"); return false; }  
   
       //【2】定义一个Mat类型并给其设定ROI区域  
       Mat imageROI;  
              //方法一  
       imageROI=srcImage4(Rect(200,250,logoImage.cols,logoImage.rows));  
       //方法二  
       //imageROI=srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));  
   
       //【3】将logo加到原图上  
       addWeighted(imageROI,0.5,logoImage,0.3,0.,imageROI);  
   
       //【4】显示结果  
       namedWindow("<4>区域线性图像混合示例窗口 by浅墨");  
       imshow("<4>区域线性图像混合示例窗口 by浅墨",srcImage4);  
        
       return true;  
} 


//-----------------------------【MultiChannelBlending( )函数】--------------------------------  
//     描述：多通道混合的实现函数  
//-----------------------------------------------------------------------------------------------  
bool MultiChannelBlending()  
{  
       //【0】定义相关变量  
       Mat srcImage;  
       Mat logoImage;  
       vector<Mat>channels;  
       Mat  imageBlueChannel;  
   
       //=================【蓝色通道部分】=================  
       //     描述：多通道混合-蓝色分量部分  
       //============================================  
   
       //【1】读入图片  
       logoImage=imread("/work/cv/basesample/CVSample/imageload/image/dota_logo.jpg",0);  
       srcImage=imread("/work/cv/basesample/CVSample/imageload/image/dota.jpg");  
   
       if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }  
       if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }  
   
       //【2】把一个3通道图像转换成3个单通道图像  
       split(srcImage,channels);//分离色彩通道  
   
       //【3】将原图的蓝色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变  
       imageBlueChannel=channels.at(0);  
       //【4】将原图的蓝色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中  
       addWeighted(imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,  
              logoImage,0.5,0,imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)));  
   
       //【5】将三个单通道重新合并成一个三通道  
       merge(channels,srcImage);  
   
       //【6】显示效果图  
       namedWindow("<1>游戏原画+logo蓝色通道 by浅墨");  
       imshow("<1>游戏原画+logo蓝色通道 by浅墨",srcImage);  
   
   
       //=================【绿色通道部分】=================  
       //     描述：多通道混合-绿色分量部分  
       //============================================  
   
       //【0】定义相关变量  
       Mat  imageGreenChannel;  
   
       //【1】重新读入图片  
       logoImage=imread("/work/cv/basesample/CVSample/imageload/image/dota_logo.jpg",0);  
       srcImage=imread("/work/cv/basesample/CVSample/imageload/image/dota.jpg");  
   
       if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }  
       if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }  
   
       //【2】将一个三通道图像转换成三个单通道图像  
       split(srcImage,channels);//分离色彩通道  
   
       //【3】将原图的绿色通道的引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变  
       imageGreenChannel=channels.at(1);  
       //【4】将原图的绿色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageGreenChannel中  
       addWeighted(imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,  
              logoImage,0.5,0.,imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)));  
   
       //【5】将三个独立的单通道重新合并成一个三通道  
       merge(channels,srcImage);  
   
       //【6】显示效果图  
       namedWindow("<2>游戏原画+logo绿色通道 by浅墨");  
       imshow("<2>游戏原画+logo绿色通道 by浅墨",srcImage);  
   
   
   
       //=================【红色通道部分】=================  
       //     描述：多通道混合-红色分量部分  
       //============================================  
        
       //【0】定义相关变量  
       Mat  imageRedChannel;  
   
       //【1】重新读入图片  
       logoImage=imread("/work/cv/basesample/CVSample/imageload/image/dota_logo.jpg",0);  
       srcImage=imread("/work/cv/basesample/CVSample/imageload/image/dota.jpg");  
   
       if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }  
       if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }  
   
       //【2】将一个三通道图像转换成三个单通道图像  
       split(srcImage,channels);//分离色彩通道  
   
       //【3】将原图的红色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变  
       imageRedChannel=channels.at(2);  
       //【4】将原图的红色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageRedChannel中  
       addWeighted(imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,  
              logoImage,0.5,0.,imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)));  
   
       //【5】将三个独立的单通道重新合并成一个三通道  
       merge(channels,srcImage);  
   
       //【6】显示效果图  
       namedWindow("<3>游戏原画+logo红色通道 by浅墨");  
       imshow("<3>游戏原画+logo红色通道 by浅墨",srcImage);  
   
       return true;  
}  

//-----------------------------------【全局函数声明部分】--------------------------------------  
//  描述：全局函数声明  
//-----------------------------------------------------------------------------------------------  
Mat img;  
int threshval = 160;            //轨迹条滑块对应的值，给初值160  

//-----------------------------【on_trackbar( )函数】------------------------------------  
//  描述：轨迹条的回调函数  
//-----------------------------------------------------------------------------------------------  
static void on_trackbar(int, void*)  
{  
    Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);  
  
    //定义点和向量  
    vector<vector<Point> > contours;  
    vector<Vec4i> hierarchy;  
  
    //查找轮廓  
    findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );  
    //初始化dst  
    Mat dst = Mat::zeros(img.size(), CV_8UC3);  
    //开始处理  
    if( !contours.empty() && !hierarchy.empty() )  
    {  
        //遍历所有顶层轮廓，随机生成颜色值绘制给各连接组成部分  
        int idx = 0;  
        for( ; idx >= 0; idx = hierarchy[idx][0] )  
        {  
            Scalar color( (rand()&255), (rand()&255), (rand()&255) );  
            //绘制填充轮廓  
            drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );  
        }  
    }  
    //显示窗口  
    imshow( "Connected Components", dst );  
}  

bool Track_bar_display()
{
    system("color 5F");    
    //载入图片  
    img = imread("/work/cv/basesample/CVSample/imageload/image/girl2.jpg", 0);  
    if( !img.data ) { printf("Oh，no，读取img图片文件错误~！ \n"); return -1; }  
  
    //显示原图  
    namedWindow( "Image", 1 );  
    imshow( "Image", img );  
  
    //创建处理窗口  
    namedWindow( "Connected Components", 1 );  
    //创建轨迹条  
    createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );  
    on_trackbar(threshval, 0);//轨迹条回调函数  
	return 0;
}
