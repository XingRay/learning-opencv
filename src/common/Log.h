//
// Created by one on 2024/12/10.
//

#pragma once

static const char *TAG = "learning-opencv";

#ifdef WIN32

#ifndef CUSTOM_LOG
#define CUSTOM_LOG

#define LOG_V(...) (printf("[VERBOSE] [%s] ", TAG), printf(__VA_ARGS__), printf("\n"))
#define LOG_D(...) (printf("[DEBUG]   [%s] ", TAG), printf(__VA_ARGS__), printf("\n"))
#define LOG_I(...) (printf("[INFO]    [%s] ", TAG), printf(__VA_ARGS__), printf("\n"))
#define LOG_W(...) (printf("[WARN]    [%s] ", TAG), printf(__VA_ARGS__), printf("\n"))
#define LOG_E(...) (printf("[ERROR]   [%s] ", TAG), printf(__VA_ARGS__), printf("\n"))

#endif

#endif


#ifdef __ANDROID__

#ifndef CUSTOM_LOG
#define CUSTOM_LOG
#include <android/log.h>

#define LOG_V(...) ((void)__android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__))
#define LOG_D(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOG_I(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define LOG_W(...) ((void)__android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__))
#define LOG_E(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))

#endif

#endif


#include <format>

#define LOG_VF(format_str, ...) LOG_V("%s", std::format(format_str, __VA_ARGS__).c_str())
#define LOG_DF(format_str, ...) LOG_D("%s", std::format(format_str, __VA_ARGS__).c_str())
#define LOG_IF(format_str, ...) LOG_I("%s", std::format(format_str, __VA_ARGS__).c_str())
#define LOG_WF(format_str, ...) LOG_W("%s", std::format(format_str, __VA_ARGS__).c_str())
#define LOG_EF(format_str, ...) LOG_E("%s", std::format(format_str, __VA_ARGS__).c_str())
