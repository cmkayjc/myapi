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

void cb_time_out()
{
  std::cout<<"timeout!"<<std::endl;
}

int main(int argc, char *argv[])
{
    int a[] = {1,2,3,4,5};
    printAllElements(Iterator<int>(&a[0],&a[4]));
    Timer tm(500000000,cb_time_out);
    while (tm.isRunning())
      {
        if (getchar() == 'q')
          tm.stop();
      }
    return 0;
}
