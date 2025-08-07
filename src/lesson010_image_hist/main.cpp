#include <format>

#include <vector>
#include <opencv2/opencv.hpp>
#include "Log.h"
#include "Window.h"

// 绘制直方图
cv::Mat drawHist(cv::Mat& hist) {
    // 参数
    const int histSize[1] = {256};
    int hist_w = 512; //画布宽高
    int hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize[0]);

    // 创建图像
    cv::Mat displayHistImage = cv::Mat::zeros(cv::Size(hist_w, hist_h), CV_8UC3);

    // 归一化
    cv::normalize(hist, hist, 0, hist_h, cv::NORM_MINMAX, -1, cv::Mat());

    // 绘制直方图
    for (int histIndex = 0; histIndex < 256; histIndex++) {
        // 计算线段顶点
        cv::Point p01(bin_w * histIndex, hist_h - cvRound(hist.at<float>(histIndex)));
        cv::Point p02(bin_w * histIndex, hist_h);
        // 绘制线段
        cv::line(displayHistImage, p01, p02, cv::Scalar(255, 255, 255), 1, 8, 0);
    }

    return displayHistImage;
}

cv::Mat calcHist(const cv::Mat& image) {
    // Calculate histogram
    //定义参数变量
    const int channelCounts[1] = {0};
    const int histSize[1] = {256};

    float xrange[2] = {0, 255};
    const float* ranges[1] = {xrange};

    cv::Mat channelHist;
    cv::calcHist(&image, 1, channelCounts, cv::Mat(), channelHist, 1, histSize, ranges);
    return channelHist;
}

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

    // 图像直方图
    // 直方图是图像处理中用于分析图像亮度分布的工具。常见的直方图操作包括计算直方图、直方图均衡化和直方图对比。

    // 计算直方图
    // 直方图可以反映图像中像素值的分布情况。
    for (int i = 0; i < channelCount; i++) {
        cv::Mat& channel = channels[i]; // Ensure this is CV_8UC1

        // Show the channel (optional)
        cvlite::Window channelWindow(std::format("Channel {}", i));
        channelWindow.showWaitAnyKey(channel);

        cv::Mat channelHist = calcHist(channel);

        cv::Mat displayHistImage = drawHist(channelHist);

        // Show histogram
        cvlite::Window displayHistImageWindow(std::format("Histogram of Channel {}", i));
        displayHistImageWindow.showWaitAnyKey(displayHistImage);
    }


    // 直方图均衡化
    // 直方图均衡化可以增强图像的对比度，使得图像的亮度分布更加均匀。
    for (int i = 0; i < channelCount; i++) {
        cv::Mat& channel = channels[i]; // Ensure this is CV_8UC1

        // Show the channel (optional)
        cvlite::Window channelWindow(std::format("Channel {}", i));
        channelWindow.showWaitAnyKey(channel);

        // 直方图均衡化
        cv::equalizeHist(channel, channel);
        cv::Mat channelHist = calcHist(channel);
        cv::Mat displayHistImage = drawHist(channelHist);

        // Show histogram
        cvlite::Window displayHistImageWindow(std::format("Histogram of Channel {}", i));
        displayHistImageWindow.showWaitAnyKey(displayHistImage);
    }


    // double compare = cv::compareHist(hist1, hist2, cv::HISTCMP_CORREL);

    // 直方图匹配（Histogram Matching）
    // 也称为直方图规定化或直方图规范化。给定一个参考图像，在某些特定的条件下需要将原图直方图映射成指定的分布形式。它通过调整原始图像的像素值，使其直方图与参考图像的直方图相似，
    // 从而达到两幅图像之间颜色和对比度的匹配。 匹配的原理不解释了，OpenCV中没有直接进行匹配的函数，可自行使用LUT来进行相关的映射来改变像素值。大致步骤：
    // 1）计算两张图像直方图的累积概率。
    // 2）构建累积概率误差矩阵。
    // 3）生成LUT映射表


    cv::Mat histTemplate = cv::imread("resource/image/hist_template.jpg");
    if (histTemplate.empty()) {
        LOG_E("histTemplate open failed");
        return -1;
    }
    cv::Mat imageGray, histTemplateGray, imageGrayEqualized;
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(imageGray, imageGrayEqualized);

    cv::cvtColor(histTemplate, histTemplateGray, cv::COLOR_BGR2GRAY);

    // 计算两张图像直方图
    cv::Mat hist1 = calcHist(imageGray);
    cv::Mat hist2 = calcHist(histTemplateGray);
    cv::Mat hist3 = calcHist(imageGrayEqualized);

    // 归一化
    cv::Mat histImage1 = drawHist(hist1);
    cvlite::Window histImageWindow1("原图直方图");
    histImageWindow1.showWaitAnyKey(histImage1);

    cv::Mat histImage2 = drawHist(hist2);
    cvlite::Window histImageWindow2("模板直方图");
    histImageWindow2.showWaitAnyKey(histImage2);

    cv::Mat histImage3 = drawHist(hist3);
    cvlite::Window histImageWindow3("均值化后直方图");
    histImageWindow3.showWaitAnyKey(histImage3);

    //1.计算两张图像直方图的累积概率
    float hist1_cdf[256] = {hist1.at<float>(0)};
    float hist2_cdf[256] = {hist2.at<float>(0)};
    for (int i = 1; i < 256; i++) {
        hist1_cdf[i] = hist1_cdf[i - 1] + hist1.at<float>(i);
        hist2_cdf[i] = hist2_cdf[i - 1] + hist2.at<float>(i);
    }
    //2.构建累积概率误差矩阵
    float diff_cdf[256][256];
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            diff_cdf[i][j] = fabs(hist1_cdf[i] - hist2_cdf[j]);
        }
    }
    //3.生成LUT映射表
    cv::Mat lut(1, 256, CV_8U);
    for (int i = 0; i < 256; i++) {
        // 查找源灰度级为i的映射灰度
        //　和i的累积概率差值最小的规定化灰度
        float min = diff_cdf[i][0];
        int index = 0;
        //寻找累积概率误差矩阵中每一行中的最小值
        for (int j = 1; j < 256; j++) {
            if (min > diff_cdf[i][j]) {
                min = diff_cdf[i][j];
                index = j;
            }
        }
        lut.at<uchar>(i) = (uchar) index;
    }

    cv::Mat matchImg;
    //cv::LUT(image1, lut, matchImg);
    cv::LUT(imageGray, lut, matchImg);

    cvlite::Window imageGrayWindow("原图");
    imageGrayWindow.showWaitAnyKey(imageGray);

    cvlite::Window histTemplateGrayWindow("模板图");
    histTemplateGrayWindow.showWaitAnyKey(histTemplateGray);

    cvlite::Window matchImgWindow("匹配图");
    matchImgWindow.showWaitAnyKey(matchImg);

    cvlite::Window imageGrayEqualizedWindow("equ");
    imageGrayEqualizedWindow.showWaitAnyKey(imageGrayEqualized);

    cv::Mat hist4 = calcHist(matchImg);
    cv::Mat hisImage4 = drawHist(hist4);
    cvlite::Window hisImageWindow4("匹配直方图");
    hisImageWindow4.showWaitAnyKey(hisImage4);

    return 0;
}
