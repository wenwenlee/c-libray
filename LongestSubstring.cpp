class Solution{
public:
	int lengthOfLongestSubstring(string s) 
	{
	
		string sub = "";
		
		int max = 0;
		int tmp = 0;
		
		for (int i = 0; i < s.length(); i++)
		{
			if (sub.find(s[i]) == -1)
			{
				sub.append(1, s[i]);
				tmp++;
			}
			else
			{
				int in = sub.find(s[i]) + 1;
				sub.erase(0, in);
				sub.append(1, s[i]);
				tmp = tmp - in + 1;
			}
			if (max<tmp)
			{
				max = tmp;
			}
		}
	
		return max;
	}
};
