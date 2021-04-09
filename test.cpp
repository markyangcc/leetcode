#include <iostream>
#include <vector>

vector<int> sortArray(vector<int> &nums)
{
    QuickSort(nums, 0, nums.size() - 1);
    return nums;
}

int partition(vector<int> &nums, int low, int high)
{
    int pivot = nums[low];
    while (low < high)
    {
        while (low < high && pivot <= nums[high])
            high--;
        nums[low++] = nums[high];

        while (low < high && pivot > nums[low])
            low++;
        nums[high--] = nums[low];
    }
    nums[low] = pivot;
    return pivot;
}

void QuickSort(vector<int> &nums, int low, int high)
{
    //递归结束条件
    if (low < high)
    {
        int pivot = partition(nums, low, high);
        QuickSort(nums, low, pivot - 1);
        QuickSort(nums, pivot + 1, high);
    }
}

int main()
{
    vector<int> arr = {5, 1, 1, 2, 0, 0};
    for (int n : arr)
        cout << n << " ";
    cout << endl;

    QuickSort(arr, 0, 6 - 1);

    for (int n : arr)
        cout << n << " ";
    cout << endl;
}