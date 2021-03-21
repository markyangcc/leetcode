/*给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0
。请使用 原地 算法。

输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
输出：[[1,0,1],[0,0,0],[1,0,1]]

*/

class Solution {
public:
  void setZeroes(vector<vector<int>> &matrix) {
    set<int> rows, cols;
    for (int i = 0; i < matrix.size(); i++)
      for (int j = 0; j < matrix[0].size(); j++)
        if (matrix[i][j] == 0) {
          rows.insert(i);
          cols.insert(j);
        }

    for (int j = 0; j < matrix[0].size(); j++)
      for (auto k : rows) {
        matrix[k][j] = 0;
      }

    for (auto k : cols)
      for (int i = 0; i < matrix.size(); i++) {
        matrix[i][k] = 0;
      }
  }
};