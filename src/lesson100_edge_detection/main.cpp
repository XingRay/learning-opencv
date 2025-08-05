#include <iostream>

#include <opencv2/opencv.hpp>
#include "Log.h"

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        LOG_E("错误：无法打开视频文件或摄像头！");
        return -1;
    }


    cv::Mat frame;
    cv::Mat edges;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }

        // 边缘检测
        cv::Canny(frame, edges, 100, 200);

        cv::imshow("frame", frame);
        imshow("Edges", edges);

        // 按 ESC 退出
        if (cv::waitKey(30) == 27) {
            break;
        }

        // 点击关闭窗口按钮
        if (cv::getWindowProperty("frame", cv::WND_PROP_VISIBLE) <= 0) {
            break;
        }
    }

    if (cv::getWindowProperty("frame", cv::WND_PROP_VISIBLE) >= 1) {
        cv::destroyWindow("frame");
    }
    if (cv::getWindowProperty("Edges", cv::WND_PROP_VISIBLE) >= 1) {
        cv::destroyWindow("Edges");
    }

    return 0;
}
