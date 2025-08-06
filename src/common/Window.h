//
// Created by leixing on 2025-08-05.
//

#pragma once

#include <memory>
#include <functional>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

namespace cvlite {
    class Window {
    private:
        const char* mName;
        bool mIsOwner;

        std::function<void(int event, int x, int y, int flags)> mMouseEventCallback;

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

        void setMouseCallback(std::function<void(int event, int x, int y, int flags)>&& callback);

    private://member
        void onMouseEvent(int event, int x, int y, int flags);

    private://static
        static void onMouse(int event, int x, int y, int flags, void* userdata);
    };
} // cvlite
