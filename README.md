# leetcode
Leetcode 刷题

1、两数之和

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
    vector<int> retvec;

        for (int i = 0; i < nums.size(); i++)
        {
            for(int j =i+1;j < nums.size();j++)
            {
                if ((nums[i] + nums[j] )==target)
                {
                    retvec.push_back(i);
                    retvec.push_back(j);
                    return retvec;
                }      
            }
        }
        
       return retvec;
    }
};
```



2、前缀和

最朴素的想法是存储数组 nums 的值，每次调用 sumRange 时，通过循环的方法计算数组 从下标 i 到下标 j 范围内的元素和，需要计算 `j-i+1` 个元素的和。由于每次检索的时间和检索的下标范围有关，因此检索的时间复杂度较高，如果检索次数较多，则会超出时间限制。

由于会进行多次检索，即多次调用 sumRange，因此为了降低检索的总时间，应该降低 sumRange 的时间复杂度，最理想的情况是时间复杂度 O(1)。为了将检索的时间复杂度降到 O(1)，需要在初始化的时候进行预处理。

提前将结果计算好，之后直接运行一次减法即可。

```c++
/*
给定一个整数数组  nums，求出数组从索引 i 到 j（i ≤ j）范围内元素的总和，包含 i、j 两点。

实现 NumArray 类：

NumArray(int[] nums) 使用数组 nums 初始化对象
int sumRange(int i, int j) 返回数组 nums 从索引 i 到 j（i ≤ j）范围内元素的总和，包含 i、j 两点（也就是 sum(nums[i], nums[i + 1], ... , nums[j])）
*/
class NumArray {
public:
    vector<int> sums;//vector默认值为零

    NumArray(vector<int>& nums) {
        int size = nums.size();
        sums.resize(size+1);

        for(int i=0;i<size;i++){
            sums[i+1] = sums[i] +nums[i];
        }
    }
    
    int sumRange(int i, int j) {
        return sums[j+1] -sums[i];
    }
};
```



复杂度分析

时间复杂度：初始化 O(n)，每次检索 O(1)，其中 n是数组 nums 的长度。
初始化需要遍历数组 nums 计算前缀和，时间复杂度是 O(n)。
每次检索只需要得到两个下标处的前缀和，然后计算差值，时间复杂度是 O(1)。

空间复杂度：O(n)，其中 nn 是数组 nums 的长度。需要创建一个长度为 n+1 的前缀和数组。

