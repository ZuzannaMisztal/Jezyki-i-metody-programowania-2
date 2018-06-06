//
// Created by dell on 01.06.2018.
//

#ifndef JIMP_EXERCISES_TIMERECORDER_H
#define JIMP_EXERCISES_TIMERECORDER_H

#include <chrono>
#include <utility>

namespace profiling{
    template<class T>
    auto TimeRecorder(T arg){
        static std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        auto object=arg();

        std::chrono::duration<double, std::milli> time=std::chrono::high_resolution_clock::now()-start;
        return std::pair<decltype(object), double>(object, time.count());
    };
}


#endif //JIMP_EXERCISES_TIMERECORDER_H
