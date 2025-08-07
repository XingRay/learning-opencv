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

    // 加载原图
    cvlite::Window originImageWindow("originImage");
    originImageWindow.showWaitAnyKey(image);

    // 将原图像按通道进行拆分
    std::vector<cv::Mat> channels;
    cv::split(image, channels);

    // 图像阈值化
    // 图像阈值化是将图像转换为二值图像的过程，常用于图像分割。常见的阈值化方法包括二值化、自适应阈值和Otsu阈值法。

    // 二值化
    // 二值化是将图像中的像素值根据设定的阈值分为两类，通常用于简单的图像分割。
    cv::Mat threshBinaryImage;
    cv::threshold(image, threshBinaryImage, 127, 255, cv::THRESH_BINARY);
    cvlite::Window threshBinaryImageWindow("threshBinaryImage");
    threshBinaryImageWindow.showWaitAnyKey(threshBinaryImage);


    for (int i = 0; i < channelCount; i++) {
        cv::Mat& channel = channels[i];

        cvlite::Window channelImageWindow(std::format("channel{}", i));
        channelImageWindow.showWaitAnyKey(channel);

        cv::Mat channelThreshBinaryImage;
        cv::threshold(channel, channelThreshBinaryImage, 127, 255, cv::THRESH_BINARY);
        cvlite::Window channelThreshBinaryImageWindow("channelThreshBinaryImage");
        channelThreshBinaryImageWindow.showWaitAnyKey(channelThreshBinaryImage);
    }


    // 自适应阈值
    // 自适应阈值根据图像的局部区域动态计算阈值，适用于光照不均匀的图像。
    for (int i = 0; i < channelCount; i++) {
        cv::Mat& channel = channels[i];

        cvlite::Window channelImageWindow(std::format("channel{}", i));
        channelImageWindow.showWaitAnyKey(channel);

        cv::Mat adaptiveThreshImage;
        // 注意输入必须是 CV_8UC1 , 所以这里先按照通道进行拆分, 再对每个通道单独处理
        cv::adaptiveThreshold(channel, adaptiveThreshImage, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);
        cvlite::Window adaptiveThreshImageWindow("adaptiveThreshImage");
        adaptiveThreshImageWindow.showWaitAnyKey(adaptiveThreshImage);
    }


    // Otsu阈值法
    // Otsu阈值法是一种自动确定阈值的方法，适用于双峰直方图的图像。
    for (int i = 0; i < channelCount; i++) {
        cv::Mat& channel = channels[i];

        cvlite::Window channelImageWindow(std::format("channel{}", i));
        channelImageWindow.showWaitAnyKey(channel);

        cv::Mat threshOtsuImage;
        cv::threshold(channel, threshOtsuImage, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        cvlite::Window threshOtsuImageWindow("threshOtsuImage");
        threshOtsuImageWindow.showWaitAnyKey(threshOtsuImage);
    }

    return 0;
}
