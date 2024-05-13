/**
 * @file timer.h
 * @author Viktor Fejes (viktor@viktorfejes.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

#include "defines.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/time.h>
#endif

typedef struct timer {
#ifdef _WIN32
    LARGE_INTEGER start_time;
    LARGE_INTEGER frequency;
#else
    u64 start_time;
#endif
} timer;

/**
 * @brief Starts a timer.
 * 
 * @param timer Timer to start
 */
INLINE void timer_start(timer* timer) {
#ifdef _WIN32
    QueryPerformanceFrequency(&timer->frequency);
    QueryPerformanceCounter(&timer->start_time);
#else
    clock_gettime(CLOCK_MONOTONIC, &timer->start_time);
#endif
}

/**
 * @brief Returns the elapsed time in seconds.
 * 
 * @param timer Timer struct to use.
 * @return double Elapsed time.
 */
INLINE double timer_elapsed(timer* timer) {
#ifdef _WIN32
    LARGE_INTEGER current_time;
    QueryPerformanceCounter(&current_time);
    LONGLONG elapsed_cycles = current_time.QuadPart - timer->start_time.QuadPart;
    double elapsed = (double)elapsed_cycles / (double)timer->frequency.QuadPart;
#else
    u64 current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    double elapsed = current_time.tv_sec - timer->start_time.tv_sec;
    elapsed += (double)(current_time.tv_nsec - timer->start_time.tv_nsec) / 1e9;
#endif

    return elapsed;
}