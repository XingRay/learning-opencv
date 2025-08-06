#include <vector>

#include <opencv2/opencv.hpp>
#include "Log.h"
#include "Window.h"

int main() {
    // 读取图像
    cv::Mat image = cv::imread("resource/image/001.png");

    // 检查图像是否成功加载
    if (image.empty()) {
        LOG_D("错误：无法加载图像，请检查路径是否正确。");
        return -1;
    }

    int width = image.cols;
    int height = image.rows;
    int channels = image.channels();
    LOG_D("width:%d, height:%d, channels:%d", width, height, channels);

    cv::Mat showImage = image.clone();

    cv::Point2f perspectSrcPoints[4];
    int perspectSrcPointsIndex = 0;

    cv::Point2f perspectDstPoints[4];

    // 目标点（变换后的四个点，模拟透视效果）
    perspectDstPoints[0] = cv::Point2f(0, 0);
    perspectDstPoints[1] = cv::Point2f(width - 1, 0);
    perspectDstPoints[2] = cv::Point2f(width - 1, height - 1);
    perspectDstPoints[3] = cv::Point2f(0, height - 1);

    // 加载原图
    cvlite::Window originImageWindow("originImage");
    originImageWindow.setMouseCallback([&](int event, int x, int y, int flags) {
        LOG_D("event:%d, x:%d, y:%d", event, x, y);
        if (event == cv::EVENT_LBUTTONDOWN) {
            cv::circle(showImage, cv::Point(x, y), 5, cv::Scalar(0, 0, 255), -1);
            originImageWindow.show(showImage);

            perspectSrcPoints[perspectSrcPointsIndex] = cv::Point2f(x, y);
            perspectSrcPointsIndex++;
            if (perspectSrcPointsIndex == 4) {
                // 计算透视变换矩阵
                cv::Mat perspectiveMatrix = cv::getPerspectiveTransform(perspectSrcPoints, perspectDstPoints);

                // 应用透视变换
                cv::Mat perspectiveImage;
                cv::warpPerspective(image, perspectiveImage, perspectiveMatrix, image.size());

                // 显示结果
                cvlite::Window perspectiveImageWindow("perspectiveImage");
                perspectiveImageWindow.showWaitAnyKey(perspectiveImage);
            }
        }
    });
    originImageWindow.showWaitAnyKey(showImage);

    return 0;
}
