//
// Created by leixing on 2025-08-05.
//

#pragma once

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

namespace cvlite {
    class Window {
    private:
        const char* mName;
        bool mIsOwner;

    public:
        Window(const char* windowName, cv::WindowFlags flags = cv::WINDOW_AUTOSIZE);

        ~Window();

        Window(const Window& other) = delete;

        Window& operator=(const Window& other) = delete;

        Window(Window&& other) noexcept;

        Window& operator=(Window&& other) noexcept;

        void show(const cv::Mat& image);

        void showWaitAnyKey(const cv::Mat& image);

        void destroy();
    };
} // cvlite
