/*
给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1
成为一个有序数组。

初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。你可以假设 nums1
的空间大小等于 m + n，这样它就有足够的空间保存来自 nums2 的元素。

示例 1：

输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
示例 2：

输入：nums1 = [1], m = 1, nums2 = [], n = 0
输出：[1]

 */

class Solution {
public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {

    int sorteArr[m + n];
    int p1, p2 = 0;

    while (p1 < m || p2 < n) {
      if (nums1[p1] >= nums2[p2]) {
        sorteArr[p1] = nums2[p2];
        p2++;
      } else if (nums1[p1] < nums2[p2]) {
        sorteArr[p2] = nums1[p1];
        p1++;
      }
    }

    for (int i = 0; i < m + n; i++) {
      nums1[i] = sorteArr[i];
    }
  }
};