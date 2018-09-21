#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>
#include <functional>

namespace MyAPI {
    using std::chrono::high_resolution_clock;
    using std::chrono::nanoseconds;
    using std::chrono::system_clock;
    class Timer
    {
    public:
        Timer(int64_t ns_time_out
              , const std::function<void(void)>& callback)
            :m_start(high_resolution_clock::now())
                                ,mf_cb(callback)
        {
            std::thread th(&Timer::run, this
                           ,nanoseconds(ns_time_out));
            th.detach();
        }
        bool isRunning() {return m_isRunning;}
        void stop() {m_isRunning = false;}
    private:
        //microseconds m_dur_ms;
        system_clock::time_point m_start;
        bool m_isRunning;
        void run(const nanoseconds& ns)
        {
           while(isRunning())
               {
                 system_clock::time_point st_now =  high_resolution_clock::now();
                 if (st_now.time_since_epoch() - m_start.time_since_epoch()
                         > system_clock::duration(ns))
                    {
                        mf_cb();
                        m_start = st_now;
                    }
               }
        };
        std::function<void(void)> mf_cb;
    };

}

#endif // TIMER_H
