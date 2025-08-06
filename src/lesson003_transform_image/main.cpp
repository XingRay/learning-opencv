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

    // 平移测试
    double tx = 100.0;
    double ty = 200.0;
    cv::Mat translationMatrix = (cv::Mat_<double>(2, 3) << 1, 0, tx, 0, 1, ty);
    cv::Mat translatedImage;
    cv::warpAffine(image, translatedImage, translationMatrix, image.size());
    cvlite::Window translatedImageWindow("translatedImage");
    translatedImageWindow.showWaitAnyKey(translatedImage);


    // 翻转测试
    cv::Mat flippedImage;
    // 1表示水平翻转，0表示垂直翻转
    cv::flip(image, flippedImage, 1);
    cvlite::Window flippedImageWindow("flippedImage");
    flippedImageWindow.showWaitAnyKey(flippedImage);


    // 仿射变换测试
    // 定义仿射变换的源点和目标点（3个点）
    cv::Point2f affineSrcPoints[3], affineDstPoints[3];

    // 源点（原始图像的三个点）
    affineSrcPoints[0] = cv::Point2f(0, 0); // 左上角
    affineSrcPoints[1] = cv::Point2f(width - 1, 0); // 右上角
    affineSrcPoints[2] = cv::Point2f(0, height - 1); // 左下角

    // 目标点（变换后的三个点）
    affineDstPoints[0] = cv::Point2f(50, 50); // 左上角平移 (50,50)
    affineDstPoints[1] = cv::Point2f(width - 50, 0); // 右上角向左移动50像素
    affineDstPoints[2] = cv::Point2f(0, height - 50); // 左下角向上移动50像素

    cv::Mat affineMatrix = cv::getAffineTransform(affineSrcPoints, affineDstPoints);
    cv::Mat affineImage;
    cv::warpAffine(image, affineImage, affineMatrix, image.size());

    cvlite::Window affineImageWindow("affineImage");
    affineImageWindow.showWaitAnyKey(affineImage);


    // 透视变换测试
    // 定义透视变换的源点和目标点（4个点）
    cv::Point2f perspectSrcPoints[4], perspectDstPoints[4];

    // 源点（原始图像的四个角点）
    perspectSrcPoints[0] = cv::Point2f(0, 0); // 左上角
    perspectSrcPoints[1] = cv::Point2f(width - 1, 0); // 右上角
    perspectSrcPoints[2] = cv::Point2f(width - 1, height - 1); // 右下角
    perspectSrcPoints[3] = cv::Point2f(0, height - 1); // 左下角

    // 目标点（变换后的四个点，模拟透视效果）
    perspectDstPoints[0] = cv::Point2f(150, 50); // 左上角向右下方移动
    perspectDstPoints[1] = cv::Point2f(width - 150, 50); // 右上角向左下方移动
    perspectDstPoints[2] = cv::Point2f(width - 1 - 50, height - 1 - 10); // 右下角向左上方移动
    perspectDstPoints[3] = cv::Point2f(50, height - 1 - 10); //左下角向右上方移动

    // 计算透视变换矩阵
    cv::Mat perspectiveMatrix = cv::getPerspectiveTransform(perspectSrcPoints, perspectDstPoints);

    // 应用透视变换
    cv::Mat perspectiveImage;
    cv::warpPerspective(image, perspectiveImage, perspectiveMatrix, image.size());

    // 显示结果
    cvlite::Window perspectiveImageWindow("perspectiveImage");
    perspectiveImageWindow.showWaitAnyKey(perspectiveImage);

    return 0;
}
