#include <iostream>
#include "List.h"
#include "Classes.h"
#include <cmath>
#include <vector>
#define DOING_RANDOM_STUFF(x, y, z) \
        (x + y + z)
#define LINE ("___")
#define DO_STUFF_

std::size_t TOTAL_ALLOCATION = 0; 

int digital_root(int n)
{
  if (n >= 10)
    return (((n % 10) + digital_root(n / 10)) > 10 ? digital_root((n % 10) + digital_root(n / 10)) : ((n % 10) + digital_root(n / 10)));
  return n;
}

void printStuff(Shape& shape) {
  shape.Draw();
}

void setXY(Shape& shape, const int& x, const int& y) {
  shape.setXY(x, y);
}

static void foo(int & a) {
  a = 10;
}

void foo1(int a) {
  a = 10;
}

int* foo2(int& a) {
  a = 10;
  return &a;
}
int& foo3(int& a) {
  a = 10;
  return a;
}

void* operator new(std::size_t size) throw(std::bad_alloc) {
  if (size == 0)
    size = 1;
  TOTAL_ALLOCATION += size;
  return std::malloc(size);
}

void operator delete(void* ptr) throw(int) {
  if (ptr != NULL)
    std::free(ptr);
}
int maxProfit(std::vector<int>& prices) {
  int maxProf = 0;
  int prof = 0;
  int day = 0;
  std::vector<int> restPrices;
  for (int i = 0; i < prices.size(); i++) {
    for (int j = i + 1; j < prices.size(); j++) {
      prof = prices[j] - prices[i];
      if (prof > maxProf) {
        maxProf = prof;
        day = j;
      }
    }
  }
  if (day + 1 < prices.size() && day != 0) {
    for (int i = day; i < prices.size(); i++) {
      restPrices.push_back(prices[i]);
    }

    maxProf = maxProf + maxProfit(restPrices);
  }
  if (maxProf > 0) {
    return maxProf;
  }
  else {
    return 0;
  }
}
int main() {
  std::vector<int> nums = { 7,1,5,3,6,4 };
  std::cout<< maxProfit(nums);
  
  return 0;

}