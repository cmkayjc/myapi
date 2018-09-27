#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>
#include <functional>
#include <unistd.h>

namespace MyAPI {
    using std::chrono::high_resolution_clock;
    using std::chrono::system_clock;
    class Timer
    {
    public:
        Timer(int64_t ns_time_out
              , const std::function<void(void)>& callback)
            :mf_cb(callback)
        {
            std::thread th(&Timer::run, this
                           ,system_clock::duration(ns_time_out));
            th.detach();
        }
        bool isRunning() {return m_isRunning;}
        void stop() {m_isRunning = false;}
    private:
        //microseconds m_dur_ms;
        bool m_isRunning;
        ///1ms = 1e6 ns
        const int64_t US_FINE_CHECKING = 1e3;//1ms = 1000us
        void run(const system_clock::duration& ns_time_out)
        {
           while(isRunning())
               {
                 system_clock::time_point st_now =  high_resolution_clock::now();
                 mf_cb();
                 system_clock::duration dur =
                         high_resolution_clock::now().time_since_epoch()
                         -st_now.time_since_epoch();

                 //wait till last US_FINE_CHECKING us
                 int64_t us_sleep = (ns_time_out.count() - dur.count())/1000 - US_FINE_CHECKING;
                 us_sleep = us_sleep > 0 ? us_sleep : 0;
                 usleep(us_sleep);
                 while (high_resolution_clock::now().time_since_epoch()
                         - st_now.time_since_epoch() < ns_time_out)
                     {}
               }
        }
        std::function<void(void)> mf_cb;
    };

}

#endif // TIMER_H
