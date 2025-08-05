#include <iostream>

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
    int channels = image.channels();
    LOG_D("width:%d, height:%d, channels:%d", width, height, channels);

    // 加载原图
    cvlite::Window originImageWindow("Display Image");
    originImageWindow.showWaitAnyKey(image);

    // 缩放测试
    int newWidth = image.cols / 2;
    int newHeight = image.rows / 2;
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(newWidth, newHeight));
    cvlite::Window resizedImageWindow("resizedImage");
    resizedImageWindow.showWaitAnyKey(resizedImage);

    // 旋转测试
    cv::Point2f center(static_cast<float>(width) / 2.0, static_cast<float>(height) / 2.0);
    float angle = 30.0f;
    // 旋转的同时可以进行缩放
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 0.75f);
    cv::Mat rotatedImage;
    cv::warpAffine(image, rotatedImage, rotationMatrix, image.size());
    cvlite::Window rotatedImageWindow("rotatedImage");
    rotatedImageWindow.showWaitAnyKey(rotatedImage);

    return 0;
}
