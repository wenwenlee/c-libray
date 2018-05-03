#include <iostream>
#include<vector>
#include<map>

using namespace std;



class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) 
    {
        
      vector<int> result;
		map<int, int> mapping;

		for (int i = 0; i < nums.size(); i++)
		{
			mapping[nums[i]] = i;
		
		}
		for (int i = 0; i < nums.size(); i++)
		{
			int searched = target - nums[i];
			if (mapping.count(searched) &&mapping[searched]!=i)
			{
				result.push_back(i);
				result.push_back(mapping[searched]);
           break;
			}
		}
		return result;
	}
 
};

int main()
{
	vector<int> nums;
	nums.push_back(3);
	nums.push_back(2);
	nums.push_back(4);
	int target = 6;
	Solution T;
	vector<int> result = T.twoSum(nums, target);
	
	cout << "iter1:" << result[0] << endl;
	cout << "iter2:" << result[1] << endl;

	return 0;
}
