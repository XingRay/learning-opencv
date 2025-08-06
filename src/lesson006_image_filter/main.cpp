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


    // 均值滤波
    cv::Mat blurImage;
    // 3x3的均值滤波
    cv::blur(image, blurImage, cv::Size(3, 3));
    cvlite::Window dstImageWindow("blurImage");
    dstImageWindow.showWaitAnyKey(blurImage);

    // 高斯滤波
    cv::Mat gaussianBlurImage;
    // 5x5的高斯滤波
    cv::GaussianBlur(image, gaussianBlurImage, cv::Size(5, 5), 0);
    cvlite::Window gaussianBlurImageWindow("gaussianBlurImage");
    gaussianBlurImageWindow.showWaitAnyKey(gaussianBlurImage);


    // 中值滤波
    cv::Mat medianBlurImage;
    // 5x5的中值滤波
    cv::medianBlur(image, medianBlurImage, 5);
    cvlite::Window medianBlurImageWindow("medianBlurImage");
    medianBlurImageWindow.showWaitAnyKey(medianBlurImage);

    // 自定义滤波器
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << 1, 0, -1, 0, 0, 0, -1, 0, 1);
    cv::Mat customFilterImage;
    cv::filter2D(image, customFilterImage, -1, kernel);
    cvlite::Window customFilterImageWindow("customFilterImage");
    customFilterImageWindow.showWaitAnyKey(customFilterImage);

    return 0;
}
