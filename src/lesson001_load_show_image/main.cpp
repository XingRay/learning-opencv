#include <iostream>

#include <opencv2/opencv.hpp>
#include "Log.h"

// https://www.runoob.com/opencv/cpp-opencv-basic.html
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

    // 显示图像
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    imshow("Display Image", image);

    // 等待按键
    cv::waitKey(0);

    // 关闭窗口
    cv::destroyAllWindows();

    return 0;
}
