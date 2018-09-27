#include <iostream>
#include "myapi/iterator.h"
#include "myapi/timer.h"
#include <cstdio>

using namespace std;
using MyAPI::Iterator;
using MyAPI::Timer;

template<typename T>
void printAllElements(Iterator<T>&& in)
{
   while (in != in.end())
   {
      std::cout<<*in<<","<<std::endl;
      ++in;
   }
}

int main(int argc, char *argv[])
{
    int a[] = {1,2,3,4,5};
    printAllElements(Iterator<int>(&a[0],&a[4]));
    auto last = std::chrono::high_resolution_clock::now().time_since_epoch();
    auto cb = [&last](){
        auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
        auto dur = now - last;
        std::cout<<dur.count()*1e-6<<std::endl;
        last = now;
      };
    Timer tm(100000000,cb);
    while (tm.isRunning())
      {
        if (getchar() == 'q')
          tm.stop();
      }
    return 0;
}
