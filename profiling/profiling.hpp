#pragma once
#include <chrono>
#include <vector>

using namespace std::chrono;

namespace Profiling {
    struct Task {
        std::string name;
        high_resolution_clock::time_point point;
    };

    struct TimeMeasure {
        high_resolution_clock::time_point start;
        std::vector<Task> tasks;

        void add_task(const std::string &name) {
            Task task;
            task.name = name;
            task.point = high_resolution_clock::now();
            tasks.emplace_back(task);
        }

        void reset() {
            tasks.clear();
            start = high_resolution_clock::now();
        }

        void profile() {
            high_resolution_clock::time_point begin = start;
            for (auto &t : tasks) {
                auto microseconds = duration_cast<::microseconds>(t.point - start).count();
                std::cout << t.name << " | " << microseconds << " microseconds" << std::endl;
                begin = t.point;
            }
        }
    };
}