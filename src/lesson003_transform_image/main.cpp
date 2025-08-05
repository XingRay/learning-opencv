#include <iostream>

#include <opencv2/opencv.hpp>
#include "Log.h"

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
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    cv::waitKey(0);
    cv::destroyWindow("Display Image");

    // 缩放测试
    int newWidth = image.cols / 2;
    int newHeight = image.rows / 2;
    cv::Mat resizedImage;
    cv::resize(image, resizedImage, cv::Size(newWidth, newHeight));
    cv::imshow("resizedImage", resizedImage);
    cv::waitKey(0);
    cv::destroyWindow("resizedImage");

    // 旋转测试
    cv::Point2f center(static_cast<float>(width) / 2.0, static_cast<float>(height) / 2.0);
    float angle = 30.0f;
    // 旋转的同时可以进行缩放
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center, angle, 0.75f);
    cv::Mat rotatedImage;
    cv::warpAffine(image, rotatedImage, rotationMatrix, image.size());
    imshow("rotatedImage", rotatedImage);
    cv::waitKey(0);

    // 检查窗口是否仍然存在，避免重复销毁
    // OpenCV 的窗口在手动关闭后，内部资源会被自动释放，但 destroyWindow 不会检查窗口是否有效，直接操作导致崩溃。
    //
    // cv::getWindowProperty() 返回窗口状态：
    // >=1：窗口存在
    // <=0：窗口已被关闭
    if (cv::getWindowProperty("rotatedImage", cv::WND_PROP_VISIBLE) >= 1) {
        cv::destroyWindow("rotatedImage");
    }

    return 0;
}
