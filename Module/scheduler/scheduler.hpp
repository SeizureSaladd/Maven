#pragma once

#include <string>
#include <queue>
#include <iostream>

#include "../offsets.hpp"
#include "../api/api.hpp"

namespace scheduler {
    inline int get_job() {
        std::uint32_t job_start = *reinterpret_cast<std::uint32_t*>(get_scheduler() + offsets::scheduler::start);
        std::uint32_t job_end = *reinterpret_cast<std::uint32_t*>(get_scheduler() + offsets::scheduler::end);
        std::string job_name{ "WaitingHybridScriptsJob" };
        int job{};

        while (job_start != job_end) {
            if (*reinterpret_cast<std::string*>(*reinterpret_cast<std::uint32_t*>(job_start) + 16) == job_name)
                job = *reinterpret_cast<std::uint32_t*>(job_start);

            job_start += 8;
        }

        // std::printf("[Scheduler] -> Found %s.", job_name);

        return job;                       
    }

    __forceinline int get_script_context() {
        static int job = get_job();
        return *reinterpret_cast<std::uint32_t*>(job + offsets::scheduler::context);
    }
}