#include <format>

#include <vector>
#include <opencv2/opencv.hpp>
#include "Log.h"
#include "Window.h"

int main() {
    // 读取图像
    cv::Mat image = cv::imread("resource/image/lena.png");

    // 检查图像是否成功加载
    if (image.empty()) {
        LOG_D("错误：无法加载图像，请检查路径是否正确。");
        return -1;
    }

    int width = image.cols;
    int height = image.rows;
    int channelCount = image.channels();
    LOG_D("width:%d, height:%d, channels:%d", width, height, channelCount);

    // 显示原图
    cvlite::Window originImageWindow("originImage");
    originImageWindow.showWaitAnyKey(image);


    // Sobel算子
    cv::Mat grad_x, grad_y;
    cv::Sobel(image, grad_x, CV_16S, 1, 0); // 水平方向
    cv::Sobel(image, grad_y, CV_16S, 0, 1); // 垂直方向
    cv::convertScaleAbs(grad_x, grad_x);
    cv::convertScaleAbs(grad_y, grad_y);

    cv::Mat sobelImage;
    // 合并结果
    cv::addWeighted(grad_x, 0.5, grad_y, 0.5, 0, sobelImage);

    cvlite::Window sobelImageWindow("sobelImage");
    sobelImageWindow.showWaitAnyKey(sobelImage);


    // Canny边缘检测
    cv::Mat cannyImage;
    cv::Canny(image, cannyImage, 100, 200); // 阈值1=100，阈值2=200
    cvlite::Window cannyImageWindow("cannyImage");
    cannyImageWindow.showWaitAnyKey(cannyImage);

    return 0;
}
