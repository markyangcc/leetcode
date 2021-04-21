#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    int a = 12343;
    vector<int> nums;
    while (a)
    {
        nums.push_back((a % 10));
        a /= 10;
    }
    reverse(nums.begin(), nums.end());
    // for (auto i : nums)
    //     cout << i;

    int maxbitpos = max_element(nums.begin(), nums.end()) - nums.begin();
    // cout << maxpos << endl;
    if (maxbitpos == 0)
        return -1;
    
    if (maxbitpos == nums.size() - 1)
    {
        int temp = nums[maxbitpos];
        nums[maxbitpos] = nums[maxbitpos - 1];
        nums[maxbitpos - 1] = temp;
    }
    

    reverse(nums.begin(), nums.end());

    int sum = 0;
    for (int i = 0; i < nums.size(); i++)
        sum += nums[i] * pow(10, i);
    cout << sum;
}