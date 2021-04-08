/*
实现 pow(x, n) ，即计算 x 的 n
次幂函数（即，xn）。不得使用库函数，同时不需要考虑大数问题。

-100.0 < x < 100.0
-231 <= n <= 231-1
-104 <= xn <= 104

 */

//快速幂解析（二分法角度）：
//快速幂实际上是二分思想的一种应用。

/* 转化为位运算：
向下整除 n // 2n//2 等价于 右移一位 n >> 1n>>1 ；
取余数 n \% 2n%2 等价于 判断二进制最右一位值 n \& 1n&1 ；

根据二分推导，可通过循环 x = x^2x=x 2操作，每次把幂从 nn 降至 n//2n//2
，直至将幂降为 00 ； 设 res=1res=1 ，则初始状态 x^n = x^n \times resx n=x^n ×
res 。在循环二分时，每当 nn 为奇数时，将多出的一项 xx 乘入 resres ，则最终可化至
x^n = x^0 \times res = resx n =x^0 × res=res ，返回 resres 即可

 */
class Solution {
public:
  double myPow(double x, int n) {

    long b = (long)n; //防止溢出，linux下long是8个字节

    double res = 1.0;

    if (b < 0) {
      x = 1 / x;
      b = -b;
    }

    while (b) {
      if (b % 2 == 1)
        res *= x; //将奇数多出来的 x 乘进res中
      x *= x;     // x = x^2
      b >>= 1;    // n//2 向下取整
    }

    return res;
  }
};