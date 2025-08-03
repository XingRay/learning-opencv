#include <iostream>

#include <opencv2/opencv.hpp>

// https://www.runoob.com/opencv/cpp-opencv-basic.html
int main() {
    // 读取图像
    cv::Mat image = cv::imread("resource/image/test.jpg");

    // 检查图像是否成功加载
    if (image.empty()) {
         << "错误：无法加载图像，请检查路径是否正确。" << endl;
        return -1;
    }

    // 显示图像
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);

    // 等待按键
    waitKey(0);

    // 关闭窗口
    destroyAllWindows();

    return 0;

    return 0;
}
