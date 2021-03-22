/*
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。
 
示例 1:

输入: [1, 2, 3, 2, 2, 2, 5, 4, 2]
输出: 2

*/

//摩尔投票法——投票法简单来说就是不同则抵消，占半数以上的数字必然留到最后。
// hashtable(unordered_map) 可以
//排序后直接返回中位数也可以
class Solution {
public:
  int majorityElement(vector<int> &nums) {
    int player, votes;

    for (const auto i : nums) {
      if (votes == 0)
        player = i;

      votes += (player == i ? 1 : -1);
    }

    return player;
  }
};