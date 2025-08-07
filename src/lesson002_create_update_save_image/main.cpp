#include <iostream>

#include <opencv2/opencv.hpp>
#include "Log.h"


// 全局变量用于存储图像
cv::Mat image;
bool isPressing = false;

// 鼠标回调函数
void onMouse(int event, int x, int y, int flags, void* userdata) {
    LOG_D("onMouse: event:%d, x:%d, y:%d. flags:%d, userdata:%p", event, x, y, flags, userdata);
    switch (event) {
        case cv::EVENT_LBUTTONDOWN: isPressing = true;
            break;
        case cv::EVENT_LBUTTONUP: isPressing = false;
            break;
        case cv::EVENT_MOUSEMOVE: {
            if (isPressing) {
                if (x >= 0 && x < image.cols && y >= 0 && y < image.rows) {
                    cv::Vec3b& color = image.at<cv::Vec3b>(y, x);
                    LOG_D("鼠标点击坐标: (%d,%d), pixel:(%d, %d, %d)", x, y, color[0], color[1], color[2]);

                    // 你也可以在图像上标记点击的位置
                    // cv::circle(image, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);

                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;

                    cv::imshow("Display Image", image);
                }
            }
        }
        break;
        default: break;
    }
}

// https://www.runoob.com/opencv/cpp-opencv-basic.html
int main() {
    // // 创建一个640x480的图像,默认是灰白色的 (205,205,205)
    // image = cv::Mat(480, 640, CV_8UC3);
    // // 可以指定图片像素的初始值
    // image = cv::Mat(480, 640, CV_8UC3, cv::Scalar(0, 0, 255));
    //
    // // 可以改变像素值
    // // 将图像初始化为白色
    // image.setTo(cv::Scalar(255, 255, 255));

    // 创建空白图像（300x300，黑色背景）
    image = cv::Mat::zeros(480, 640, CV_8UC3);

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
    const char* windowsName = "Display Image";
    cv::namedWindow(windowsName, cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback(windowsName, onMouse, nullptr);

    imshow(windowsName, image);

    // 等待按键
    cv::waitKey(0);
    // 保存图片
    cv::imwrite("output.png", image);

    // 关闭窗口
    cv::destroyAllWindows();

    return 0;
}
