#include <cmath>
#include <iostream>

using namespace std;
int mySqrt(int x)
{
  int i = 0;
  int j = x;
  int mid;

  while (i < j)
  {
    mid = (i + j) / 2;

    if (mid == i)
      return mid;
    if (pow(mid, 2) > x)
      j = mid;
    else
      i++;
  }
  return mid;
}

int main()
{
  int c = mySqrt(15);
  cout << pow(0,2);
}