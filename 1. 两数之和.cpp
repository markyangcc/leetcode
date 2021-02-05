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