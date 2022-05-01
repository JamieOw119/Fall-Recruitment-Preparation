# Dynamic Programming

## 子序列/子串问题

### Kind 1: 单个序列找规律

#### 300. 最长递增子序列 median

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

#### 1218. 最长定差子序列 median

```
class Solution 
{
public:
    int longestSubsequence(vector<int> &arr, int difference) {
        int ans = 0;
        unordered_map<int, int> dp;
        for (int v: arr) 
        {
            dp[v] = dp[v - difference] + 1;
            ans = max(ans, dp[v]);
        }
        return ans;
    }
};
```

### Kind 2: 多重状态转移方程

#### 152. 乘积最大子数组 median

> 滚动数组

```
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxval = nums[0];
        int minval = nums[0];
        int ans = nums[0];
        for(int i = 1; i < nums.size(); ++i)
        {
            int num = nums[i];
            int mx = maxval, mn = minval;
            maxval = max(mx * num, max(mn * num, num));
            minval = min(mn * num, min(mx * num, num));
            ans = max(maxval, ans);
        }
        return ans;
    }
};
```

#### 1911. 最大子序列交替和 median

> 滚动数组

```
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) 
    {
        int n = nums.size();
        long long odd = 0, even = nums[0];
        for (int i = 1; i < n; ++i) 
        {
            tie(odd, even) = tuple{max(even - nums[i], odd), max(odd + nums[i], even)};
        }
        return even;
    }
};
```

### Kind 3: 两个序列找重复

#### 115. 子序列的个数 hard

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

> 一维 DP + 滚动数组

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
                temp1 = dp[j];
                temp2 = dp[j + 1];
                dp[j + 1] += (s[i] == t[j]) ? temp1 : 0;
                 // temp1 = temp2;
            }
        }
        return dp[n];
    }
};
```

#### 1143. 最长公共子序列 median

> 二维 DP

```
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) 
    {
        int n1 = text1.size();
        int n2 = text2.size();
        if (n1 < n2) 
        {
            return longestCommonSubsequence(text2, text1);
        }

        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
        for (int i = 0; i < n1; ++i) 
        {
            for (int j = 0; j < n2; ++j) 
            {
                if (text1[i] == text2[j]) 
                {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                } 
                else 
                {
                    dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
                }
            }
        } 
        return dp[n1][n2];
    }
};
```

> 一维 DP + 滚动数组

```
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) 
    {
        int n1 = text1.size();
        int n2 = text2.size();
        if (n1 < n2) 
        {
            return longestCommonSubsequence(text2, text1);
        }
        
        vector<int> dp(n2 + 1, 0);
        for (int i = 0; i < n1; ++i) 
        {
            int temp1 = 0;
            int temp2 = 0;
            for (int j = 0; j < n2; ++j) 
            {
                temp2 = dp[j + 1];
                if (text1[i] == text2[j]) 
                {
                    dp[j + 1] = temp1 + 1;
                } 
                else 
                {
                    dp[j + 1] = max(dp[j], dp[j + 1]);
                }
                temp1 = temp2;
            }
        } 
        return dp[n2];
    }
};
```

#### 718. 最长重复子序列 median

> 二维 DP

```
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int maxLen = 0;  
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < m + 1; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {  
                    if (dp[i - 1][j - 1] != 0) {     
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    } else {  
                        dp[i][j] = 1;
                    }
                } else {
                    dp[i][j] = 0;
                }
                maxLen = max(maxLen, dp[i][j]);
            }
        }
        return maxLen;
    }
};
```

> 一维 DP + 滚动数组

```
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int ans = 0;
        vector<int> dp(n+1, 0);
        for (int i = 1; i <= m; ++i) {
            int temp1 = 0;
            int temp2 = 0;
            for (int j = 1; j <= n; ++j) {
                temp2 = dp[j];
                if (nums1[i-1] == nums2[j-1]) {
                    dp[j] = temp1 + 1;
                } else {
                    dp[j] = 0;
                }
                temp1 = temp2;
                ans = max(ans, dp[j]);
            }
        }
        return ans;
    }
};
```



