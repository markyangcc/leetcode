/*
题目：
输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]


思路：
根据题意，需要特判，对于空矩阵直接返回空数组。
接下来：

定义出二维数组的左右上下四个边界，left、right、top、bottom;
循环打印：
沿着top，从左向右打印，top++;
沿着right,从上向下打印，right--;
沿着bottom，从右向左打印，bottom++；
沿着left,从下向上打印，left++;
注：在沿着下边界和左边界打印时，要确保left <= right，top <= bottom。
*/

class Solution {
 public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.size() == 0) return vector<int>{};  //返回空数组

    int left, top = 0;
    int right = matrix[0].size() - 1;  //注意减一
    int bottom = matrix.size() - 1;

    vector<int> retvec;  //不可以初始化vector大小，再结合push_back会出错

    while (top <= bottom && left <= right) {
      for (int i = left; i <= right; i++) retvec.push_back(matrix[top][i]);
      top++;  // top move to next row

      for (int i = top; i <= bottom; i++) retvec.push_back(matrix[i][right]);
      right--;  // right move to left col

      for (int i = right; i >= left && top <= bottom; i--)
        retvec.push_back(matrix[bottom][i]);
      bottom--;  // botton move up

      for (int i = bottom; i >= top && left <= right; i--)
        retvec.push_back(matrix[i][left]);
      left++;  // move to right
    }

    return retvec;
  }
};