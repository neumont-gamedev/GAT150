#pragma once
#include "Logger.h"

#ifdef _DEBUG
#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            viper::Logger::Error("ASSERTION FAILED: '{}'", #condition); \
            std::abort(); \
        } \
    } while(0)

#define ASSERT_MSG(condition, msg) \
    do { \
        if (!(condition)) { \
            viper::Logger::Error("ASSERTION FAILED: '{}' - {}", #condition, msg); \
            std::abort(); \
        } \
    } while(0)


#else
#define ASSERT(condition) ((void)0)
#define ASSERT_MSG(condition, msg) ((void)0)
#endif