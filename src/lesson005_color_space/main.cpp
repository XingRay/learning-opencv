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

    // 转化为灰度图
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    cvlite::Window grayImageWindow("grayImage");
    grayImageWindow.showWaitAnyKey(grayImage);

    // RGB -> HSV
    cv::Mat hsvImage;
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);
    cvlite::Window hsvImageWindow("hsvImage");
    hsvImageWindow.showWaitAnyKey(hsvImage);


    // 图像通道的分离与合并
    std::vector<cv::Mat> channels;
    cv::split(image, channels);
    for (int i = 0; i < channelCount; i++) {
        cv::Mat channel = channels[i];
        cvlite::Window channelImageWindow(std::format("channel{}", i));
        channelImageWindow.showWaitAnyKey(channel);
    }
    cv::Mat mergedImage;
    cv::merge(channels, mergedImage);
    cvlite::Window mergedImageWindow("mergedImage");
    mergedImageWindow.showWaitAnyKey(mergedImage);

    return 0;
}
