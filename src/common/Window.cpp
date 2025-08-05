//
// Created by leixing on 2025-08-05.
//

#include "Window.h"


namespace cvlite {
    Window::Window(const char* name, cv::WindowFlags flags)
        : mName(name), mIsOwner(true) {
        cv::namedWindow(mName, flags);
    }

    Window::~Window() {
        if (mIsOwner) {
            destroy();
            mIsOwner = false;
        }
    }

    Window::Window(Window&& other) noexcept
        : mName(other.mName),
          mIsOwner(std::exchange(other.mIsOwner, false)) {
    }

    Window& Window::operator=(Window&& other) noexcept {
        if (this != &other) {
            mName = other.mName;
            mIsOwner = std::exchange(other.mIsOwner, false);
        }
        return *this;
    }

    void Window::show(const cv::Mat& image) {
        cv::imshow(mName, image);
    }

    void Window::showWaitAnyKey(const cv::Mat& image) {
        show(image);
        cv::waitKey(0);
        destroy();
    }

    void Window::destroy() {
        // 检查窗口是否仍然存在，避免重复销毁
        // OpenCV 的窗口在手动关闭后，内部资源会被自动释放，但 destroyWindow 不会检查窗口是否有效，直接操作导致崩溃。
        //
        // cv::getWindowProperty() 返回窗口状态：
        // >=1：窗口存在
        // <=0：窗口已被关闭
        if (mIsOwner && cv::getWindowProperty(mName, cv::WND_PROP_VISIBLE) >= 1) {
            cv::destroyWindow(mName);
        }
    }
} // cvlite
