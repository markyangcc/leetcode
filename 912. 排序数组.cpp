/* 给你一个整数数组 nums，请你将该数组升序排列。 */

class Solution {
public:
    // 封装快排
    vector<int> sortArray(vector<int>& nums) {
        QuickSort(nums,0,nums.size() -1);
        return nums;
    }
    //找轴点
    int partition(vector<int> &A, int low, int high) {
        int pivot = A[low];
        while (low < high) {
            while (low < high && A[high] >= pivot)
                --high;
            A[low] = A[high];
            while (low < high && A[low] <= pivot)
                ++low;
            A[high] = A[low];
        }
        A[low] = pivot;
        return low;
    }
    
    //快速排序主函数
    void QuickSort(vector<int> &A, int low, int high) {
        if (low < high) {
            int pivot = partition(A, low, high);
            QuickSort(A, low, pivot - 1);
            QuickSort(A, pivot + 1, high);
        }
    }
};