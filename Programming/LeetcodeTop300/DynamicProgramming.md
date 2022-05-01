# Dynamic Programming

## 300. 最长递增子序列

```
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if(nums.size() == 0)
        {
            return 0;
        }

        vector<int> dp(nums.size(), 1);
        for(int i=0; i<nums.size(); i++)
        {
            for(int j=0; j<i; j++)
            {
                if(nums[i] > nums[j])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }

        int maxlen = 0;
        for(int i=0; i<nums.size(); i++)
        {
            maxlen = max(maxlen, dp[i]);
        }
        return maxlen;
    }
};
```

## 115. 子序列的个数

> 二维 DP

```
class Solution {
public:
    int numDistinct(string s, string t) 
    {
        if (s.size() < t.size()) 
        {
            return 0;
        }

        vector<vector<unsigned int>> dp(s.size() + 1, vector<unsigned int>(t.size() + 1, 0));
        dp[0][0] = 1;

        for (int i = 0; i < s.size(); ++i) 
        {
            dp[i + 1][0] = 1;
            for (int j = 0; j <= i && j < t.size(); ++j) {
                dp[i + 1][j + 1] = (s[i] == t[j]) ? dp[i][j] + dp[i][j + 1] : dp[i][j + 1];
            }
        }
        return dp[s.size()][t.size()];
    }
};
```

> 一维数组

```
class Solution {
public:
    int numDistinct(string s, string t) {
        if (s.size() < t.size()) {
            return 0;
        }

        int n = t.size();
        vector<unsigned int>dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < s.size(); ++i) {
            int temp1 = 1;
            int temp2 = 1;
            for (int j = 0; j <= i && j < n; ++j) {
                temp2 = dp[j + 1];
                dp[j + 1] += (s[i] == t[j]) ? temp1 : 0;
                temp1 = temp2;
            }
        }
        return dp[n];
    }
};
```

> 一维数组反向

```
class Solution {
public:
    int numDistinct(string s, string t) {
        if (s.size() < t.size()) {
            return 0;
        }

        int n = t.size();
        vector<unsigned int>dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 0; i < s.size(); ++i) {
            for (int j = min(i, n - 1); j >= 0; --j) {
                if (s[i] == t[j]) {
                    dp[j + 1] += dp[j];
                }
            }
        }
        return dp[n];
    }
};
```