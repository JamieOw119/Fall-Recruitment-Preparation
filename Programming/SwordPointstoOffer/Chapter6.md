# 第六章 面试中的各项能力

# 1. 在排序数组中查找数字

> 1.1 数字在排序数组中出现的次数

```
class Solution {
public:
    int BinarySearch(vector<int> vec, double k)
    {
        int beg = 0;
        int end = vec.size() - 1;
        while(beg <= end)
        {
            int mid = (beg + end) >> 1;
            if(k < vec[mid])
            {
                end = mid - 1;
            }
            else
            {
                beg = mid + 1;
            }
        }
        return beg;
    }
    
    int GetNumberOfK(vector<int> data ,int k) 
    {
        int start = BinarySearch(data, k-0.5);
        int end = BinarySearch(data, k+0.5);
        return end - start;
    }
};
```

> 1.2 0～n-1 中缺失的数字

```
class Solution {
public:
    int missingNumber(vector<int>& nums) 
    {
        int left = 0;
        int right = nums.size() - 1;
        while(left <= right) 
        {
            int mid = (left + right) >> 1;
            if(nums[mid] == mid) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }
};
```

> 1.3 数组中下标和值相等的数字

```
class Solution {
public:
    int equalToIndex(vector<int>& nums) 
    {
        int left = 0;
        int right = nums.size() - 1;
        vector<int> res;
        while(left <= right) 
        {
            int mid = (left + right) >> 1;
            int num = nums[mid];
            if(num == mid)
            {
                res.push_back(mid);
            }
            else if(num < mid)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        sort(res.begin(), res.end());
        return res;
    }
};
```

## 2. 二叉搜索树的第k个节点

```
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */

class Solution {
public:
    TreeNode* res = NULL;
    int count = 0;
    
    void midOrder(TreeNode* root, int k){
        if(root == NULL || count > k) 
            return;
        midOrder(root->left, k);
        count++;
        if(count == k) 
            res = root;
        midOrder(root->right, k);
    }
    
    int KthNode(TreeNode* proot, int k) {
        midOrder(proot, k);
        if(res)
            return res->val;
        else 
            return -1;
    }
};
```

## 3. 二叉树的深度

> 递归版本

```
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    int TreeDepth(TreeNode* pRoot) {
        if(!pRoot) return 0;
        int ldepth = TreeDepth(pRoot->left);
        int rdepth = TreeDepth(pRoot->right);
        return max(ldepth, rdepth) + 1;
    }
};
```

> 非递归版本

```
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    int TreeDepth(TreeNode* pRoot) {
        if(!pRoot) return 0;
        queue<TreeNode *> q;
        q.push(pRoot);
        int level = 0;
        while(!q.empty())
        {
            int sz = q.size();
            while(sz--)
            {
                auto node = q.front();
                q.pop();
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            level ++;
        }
        return level;
    }
};
```

> p.s.1 平衡二叉树

```
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    int height(TreeNode* root) {
        if (root == NULL) {
            return 0;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
            return -1;
        } else {
            return max(leftHeight, rightHeight) + 1;
        }
    }

    bool isBalanced(TreeNode* root) {
        return height(root) >= 0;
    }
};
```

## 4. 数组中只出现一次的两个数字

```
class Solution {
public:
    vector<int> FindNumsAppearOnce(vector<int>& array) {
        vector<int> ans(2);
        int res = 0;
        for(int x: array)
        {
            res ^= x;
        }
        int m = 1;
        while(!(m&res))
        {
            m <<= 1;
        }
        for(int x: array)
        {
            if(!(m&x))
            {
                ans[0] ^= x;
            }
            else
            {
                ans[1] ^= x;
            }
        }
        if(ans[0]>ans[1])
        {
            swap(ans[0], ans[1]);
        }
        return ans;
    }
};
```

> p.s.1 数组中唯一只出现一次的数字

```
class Solution {
public:
    int singleNumber(vector<int>& nums) 
    {
        int ans = 0, bit = 0;
        for(int i=30; i>=0; i--)
        {
            for( int num : nums)
            {
                bit += (num>>i) & 1;
            }
            ans = (ans<<=1) + (bit % 3);
            bit = 0;
        }
        return ans;
    }
};
```

## 5. 和为S的两个数字

```
class Solution {
public:
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        int left = 0;
        int right = array.size() - 1;
        vector<int> v;
        while(left<right)
        {
            int cur = array[left] + array[right];
            if(cur > sum)
            {
                right --;
            }
            else if(cur < sum)
            {
                left ++;
            }
            else if(cur == sum)
            {
                v.push_back(array[left]);
                v.push_back(array[right]);
                break;
            }
        }
        return v;
    }
};
```

> 和为 s 的正数序列

```
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> vec;
        vector<int> res;

        for(int l = 1, r = 2; l < r;)
        {
            int sum = (l + r) * (r - l + 1) >> 1;
            if(sum == target)
            {
                res.clear();
                for(int i = l; i <= r; i ++)
                {
                    res.emplace_back(i);
                }
                vec.emplace_back(res);
                l ++;
            }
            else if(sum < target)
            {
                r ++;
            }
            else
            {
                l ++;
            }
        }
        return vec;
    }
};
```

## 6. 翻转字符串

```
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());

        int n = s.size();
        int idx = 0;
        for (int start = 0; start < n; ++start) {
            if (s[start] != ' ') {
                if (idx != 0) s[idx++] = ' ';

                int end = start;
                while (end < n && s[end] != ' ') s[idx++] = s[end++];

                reverse(s.begin() + idx - (end - start), s.begin() + idx);

                start = end;
            }
        }
        s.erase(s.begin() + idx, s.end());
        return s;
    }
};
```
 
> p.s.1 左旋转字符串

```
class Solution 
{
public:
    string LeftRotateString(string str, int n) {
        if(!str.length())
            return str;
        if(n>str.length())
            n = n % str.length();
        string res=str.substr(n)+str.substr(0,n);   
    }
};
```

## 7. 滑动窗口的最大值

```
class Solution {
public:
    string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int n = s.size();
        int idx = 0;
        for(int start = 0; start < n; start ++)
        {
            if(s[start] != ' ')
            {
                if(idx != 0)
                {
                    s[idx ++] = ' ';
                }
                int end = start;
                while(end < n && s[end] != ' ')
                {
                    s[idx ++] = s[end ++];
                }
                reverse(s.begin() + idx - (end - start), s.begin() + idx);
                start = end;
            }
        }
        s.erase(s.begin() + idx, s.end());
        return s;
    }
};
```

## 8. 滑动窗口的最大值

```
class Solution {
public:
    vector<int> maxInWindows(const vector<int>& nums, int size) {
        vector<int> v;
        deque<int> dq;
        if(size > nums.size() || !size)
        {
            return v;
        }
        for(int i = 0; i < nums.size(); i++)
        {
            while(!dq.empty() && nums[dq.back()] < nums[i])
            {
                dq.pop_back();
            }
            dq.push_back(i);
            if(dq.front() + size <= i)
            {
                dq.pop_front();
            }
            if(i + 1 >= size)
            {
                v.push_back(nums[dq.front()]);
            }
        }
        return v;
    }
};
```

> 队列的最大值

```
class MaxQueue {
    queue<int> q;
    deque<int> d;
public:
    MaxQueue() {}
    
    int max_value() 
    {
        if (d.empty())
            return -1;
        return d.front();
    }
    
    void push_back(int value) 
    {
        while (!d.empty() && d.back() < value) 
        {
            d.pop_back();
        }
        d.push_back(value);
        q.push(value);
    }
    
    int pop_front() 
    {
        if (q.empty())
            return -1;
        int ans = q.front();
        if (ans == d.front()) 
        {
            d.pop_front();
        }
        q.pop();
        return ans;
    }
};
```

## 9. n个骰子的点数

```
class Solution {
public:
    vector<double> dicesProbability(int n) 
    {
        vector<double> dp(6, 1.0 / 6.0);
        for (int i = 2; i <= n; i++) 
        {
            vector<double> tmp(5 * i + 1, 0);
            for (int j = 0; j < dp.size(); j++) 
            {
                for (int k = 0; k < 6; k++) 
                {
                    tmp[j + k] += dp[j] / 6.0;
                }
            }
            dp = tmp;
        }
        return dp;
    }
};
```

> p.s.1 扑克牌中的顺子

```
class Solution {
public:
    bool IsContinuous( vector<int> numbers ) 
    {
        int flag = 0;
        int _min = 14, _max = 0;
        for(auto i: numbers)
        {
            if(i == 0)
            {
                continue;
            }
            _min = min(_min, i);
            _max = max(_max, i);
            if((flag&(1<<i)) !=0 )
            {
                return false;
            }
            flag |= (1 << i);
        }
        return _max - _min < 5;
    }
};
```

## 10. 孩子们的游戏

> 约瑟夫环

```
class Solution {
public:
    int LastRemaining_Solution(int n, int m) 
    {
        if(n < 1 || m < 1)
        {
            return -1;
        }
        int last = 0;
        for(int i=2; i<=n; i++)
        {
            last = (last + m) % i;
        }
        return last;
    }
};
```

## 11. 买卖股票的最好时机

```
class Solution {
public:
    int maxProfit(vector<int>& prices) 
    {
        if(prices.size()<2)
        {
            return 0;
        }
        int min = prices[0];
        
        if(prices.size()>2)
        {
            int maxDiff = 0;
            for(int i=2; i < prices.size(); i++)
            {
                if(prices[i-1]<min)
                {
                    min = prices[i-1];
                }
                int currentDiff = prices[i] - min;
                if(currentDiff > maxDiff)
                {
                    maxDiff = currentDiff;
                }
            }
            return maxDiff;
        }
        else
        {
            return prices[1] > prices[0] ? prices[1] - prices[0] : 0;
        }
    }
};
```

## 12. 求 1 + 2 + ... + n

> 递归

```
class Solution {
public:
    int res = 0;
    int Sum_Solution(int n) {
        // n = 0 时停止递归
        n && (n += Sum_Solution(n-1));
        return n;
    }
};
```

> 一半内存的大小

```
class Solution {
public:
    int res = 0;
    int Sum_Solution(int n) {
        bool buffer[n][n + 1];
        return sizeof(buffer) >> 1;
    }
};
```

> 快速乘法

```
class Solution {
public:
    int res = 0;
    int Sum_Solution(int n) {
        int res = 0;
        int A = n, B = n + 1;
        //14次快速乘法
        (B & 1) && (res += A);
        A <<= 1;
        B >>= 1;
        (B & 1) && (res += A);
        A <<= 1;
        B >>= 1;
        (B & 1) && (res += A);
        A <<= 1;
        B >>= 1;
        (B & 1) && (res += A);
        A <<= 1;
        B >>= 1;
        (B & 1) && (res += A);
        A <<= 1;
        B >>= 1;
        (B & 1) && (res += A);
        A <<= 1;
        B >>= 1;
        (B & 1) && (res += A);
        A <<= 1;
        B >>= 1;
        (B & 1) && (res += A);
        A <<= 1;
        B >>= 1;
        return res >> 1; //除2
    }
};
```

> 构造函数

```
class Temp
{
public:
    Temp(){++ N; sum += N;}
    static void Reset(){N = 0; Sum = 0;}
    static unsigned GetSum() {return Sum;}

private:
    static unsigned int N;
    static unsigned int Sum;
}

unsigned int Temp::N = 0;
unsigned int Temp::Sum = 0;

unsigned int Sum_Solution(unsigned int n)
{
    Temp::Reset();
    Temp *a = new Temp[n];
    delete []a;
    a = nullptr;
    return Temp::GetSum();
}
```

> 虚函数

```
class A;
A *array[2];

class A
{
public:
    virtual unsigned int Sum(unsigned int n)
    {
        return 0;
    }
};
    
class B: publicA
{
public:
    virtual unsigned int Sum(unsigned n)
    {
        return Array[!!n]->Sum(n-1)+n;
    }
};

int Sum_Solution(int n)
{
    A a;
    B b;
    Array[0] = &a;
    Array[1] = &b;
    int value = Array[1]->Sum(n);
    return value;
}
```

> 函数指针

```
typedef unsigned int (*fun)(unsigned int);

unsigned int Solution_Terminator(unsigned int n)
{
    return 0;
}

unsigned int Sum_Solution(unsigned int n)
{
    static fun f[2] = {Solution_Terminator, Sum_Solution};
    return n + f[!!n](n + 1);
}
```

> 模板类型

```
template<unsigned int n> struct Sum_Solution
{
    enum Value {N = Sum_solution<n-1>::N+n};
}

template<> struct Sum_Solution<>
{
    enum Value {N = 1};
}
```

## 13. 不用加减乘除做加法

> 自增

```
class Solution {
public:
    int Add(int num1, int num2) 
    {
        if(num1>0)
        {
            while(num1--)
            {
                num2 ++;
            }
        }
        else if(num1 < 0)
        {
            while(num1 ++)
            {
                num2 --;
            }
        }
        return num2;
    }
};
```

> 位运算

```
class Solution {
public:
    int Add(int num1, int num2) 
    {
        while(num2)
        {
            int sum = num1 ^ num2; // 当前位的和
            int tmp = (unsigned int)(num1 & num2) << 1; // 进位
            num1 = sum;
            num2 = tmp;
        }
        return num1;
    }
};
```

```
class Solution {
public:
    int Add(int num1, int num2) 
    {
        
        if(num2 == 0)
        {
            return num1;
        } 
        return Add(num2 ^ num1, (unsigned int)(num1 & num2) << 1);
    }
};
```

## 14. 构建乘积数组

```
class Solution {
public:
    vector<int> multiply(const vector<int>& A) {
        int len = A.size();
        vector<int> B;
        int mul = 1;
        for(int i=0; i<len; i++) 
        {
            for(int j=0; j<len; j++) 
            {
                if(i!=j)
                {
                    mul *= A[j];
                }
            }
            B.push_back(mul);
            mul = 1;
        }
        return B;
    }
};
```

