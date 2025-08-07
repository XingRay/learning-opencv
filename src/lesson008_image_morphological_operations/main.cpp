#include <format>

#include <vector>
#include <opencv2/opencv.hpp>
#include "Log.h"
#include "Window.h"

int main() {
    // 生成图像
    // 创建空白图像（300x300，黑色背景）
    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);

    // 绘制前景形状（白色）
    cv::circle(image, cv::Point(100, 200), 20, cv::Scalar(255, 255, 255), -1);
    cv::circle(image, cv::Point(500, 250), 40, cv::Scalar(255, 255, 255), -1);
    cv::circle(image, cv::Point(130, 400), 45, cv::Scalar(255, 255, 255), -1);
    cv::circle(image, cv::Point(460, 370), 50, cv::Scalar(255, 255, 255), -1);
    cv::rectangle(image, cv::Rect(250, 300, 80, 80), cv::Scalar(255, 255, 255), -1); // 正方形
    cv::line(image, cv::Point(50, 50), cv::Point(550, 150), cv::Scalar(255, 255, 255), 3); // 斜线

    // 添加噪声（随机白点）
    cv::RNG rng(12345);
    for (int i = 0; i < 200; i++) {
        int x = rng.uniform(0, image.cols);
        int y = rng.uniform(0, image.rows);
        image.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
    }

    for (int i = 0; i < 200; i++) {
        int x = rng.uniform(0, image.cols);
        int y = rng.uniform(0, image.rows);
        image.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
    }

    // 显示原图
    cvlite::Window originImageWindow("originImage");
    originImageWindow.showWaitAnyKey(image);

    // 腐蚀
    // 腐蚀操作可以消除图像中的小物体或细节，使得前景物体变小。

    // 怎么定义前景/背景
    // For Binary Images (CV_8UC1 with 0/255 values)
    // Foreground: Pixels with value 255 (white)
    // Background: Pixels with value 0 (black)

    // For Grayscale Images (CV_8UC1 with 0-255 values)
    // Morphological operations treat pixel values as heights (like a topographic map):
    // Foreground: Higher-intensity pixels (closer to 255)
    // Background: Lower-intensity pixels (closer to 0)

    // For Color Images (CV_8UC3)
    // OpenCV applies the operation to each channel (B, G, R) separately, treating each channel as a grayscale image

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat erodeImage;
    cv::erode(image, erodeImage, kernel);
    cvlite::Window erodeImageWindow("erodeImage");
    erodeImageWindow.showWaitAnyKey(erodeImage);


    // 开运算
    // 开运算是先腐蚀后膨胀的操作，常用于去除小物体或噪声。
    cv::Mat morphOpenImage;
    cv::morphologyEx(image, morphOpenImage, cv::MORPH_OPEN, kernel);
    cvlite::Window morphOpenImageWindow("morphOpenImage");
    morphOpenImageWindow.showWaitAnyKey(morphOpenImage);


    // 闭运算
    // 闭运算是先膨胀后腐蚀的操作，常用于填补前景物体中的小孔。
    cv::Mat morphCloseImage;
    cv::morphologyEx(image, morphCloseImage, cv::MORPH_CLOSE, kernel);
    cvlite::Window morphCloseImageWindow("morphCloseImage");
    morphCloseImageWindow.showWaitAnyKey(morphCloseImage);

    // 形态学梯度
    // 形态学梯度是膨胀和腐蚀的差值，可以用于提取物体的边缘。
    cv::Mat morphGradientImage;
    cv::morphologyEx(image, morphGradientImage, cv::MORPH_GRADIENT, kernel);
    cvlite::Window morphGradientImageWindow("morphGradientImage");
    morphGradientImageWindow.showWaitAnyKey(morphGradientImage);

    return 0;
}
