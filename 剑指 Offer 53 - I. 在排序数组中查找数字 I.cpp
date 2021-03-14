/*
统计一个数字在排序数组中出现的次数。

输入: nums = [5,7,7,8,8,10], target = 8
输出: 2

*/

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    // target+1 是个好主意，即使这个target可能并不存在
    return BinaryLeft(nums, target + 1) - BinaryLeft(nums, target);
  }

  //这个算法找到的是target的左边值，即小于target的第一个位置
  int BinaryLeft(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
      int mid = (left + right) / 2;

      // <target 找出来的是左边界，>target得到的是右边界
      if (nums[mid] < target) {
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    return left;  //返回左边界
  }
};