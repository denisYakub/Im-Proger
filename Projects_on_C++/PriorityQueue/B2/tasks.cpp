#include "PriorityQueue.hpp"

void task(const size_t width = 40)
{
  textConverter formatter(width);
  formatter.read();
  formatter.format();
  formatter.print();
}
