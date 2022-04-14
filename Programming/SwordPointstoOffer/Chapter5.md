# 第五章 优化时间和空间效率

## 1. 数组中出现次数超过一半的数字

> Partition 版本 (未通过)

```
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) 
    {
        if(CheckInvalidArray(numbers))
        {
            return -1;
        }
        
        int middle = numbers.size() >> 1;
        int start = 0;
        int end = numbers.size() - 1;
        int index = Partition(numbers, start, end);
        
        while(index != middle)
        {
            if(index > middle)
            {
                end = index - 1;
            }
            else
            {
                start = index + 1; 
            }
            index = Partition(numbers, start, end);
        }
        
        int number = numbers[middle];
        if(!CheckMoreThanHalf(numbers, number))
        {
            return -1;
        }
        return number;
    }
    
    int Partition(vector<int> &numbers, int start, int end)
    {
        if(numbers.empty() || start < 0 || end >= numbers.size())
        {
            return -1;
        }
        
        int pivotIndex = start;
        int pivot = numbers[pivotIndex];
        int temp = numbers[pivotIndex];
        numbers[pivotIndex] = numbers[end];
        
        int low = start;
        int high = end;
        
        while(low < high)
        {
            while(low < high && numbers[low] < pivot) low ++;
            while(low < high && numbers[high] > pivot) high --;
            if(low < high)
            {
                temp = numbers[low];
                numbers[low] = numbers[high];
                numbers[high] = temp;
            }
        }
        
        temp = numbers[low];
        numbers[low] = numbers[end];
        numbers[end] = temp;
        return low;
    }
    
    bool inputInvalid = false;
    
    bool CheckInvalidArray(vector<int> numbers)
    {
        inputInvalid = false;
        if(numbers.empty())
        {
            inputInvalid = true;
        }
        return inputInvalid;
    }
    
    bool CheckMoreThanHalf(vector<int> numbers, int number)
    {
        int times = 0;
        int length = numbers.size();
        for(int i=0; i<length; i++)
        {
            if(numbers[i]==number)
            {
                times ++;
            }
        }
        bool isMoreThanHalf = true;
        if(times >> 1 <= length)
        {
            inputInvalid = true;
            isMoreThanHalf = false;
        }
        return isMoreThanHalf;
    }
};
```

> 哈希版本

```
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) 
    {
        unordered_map<int, int> m;
        for(const int val: numbers)
        {
            m[val] ++;
        }
        int halfLength = numbers.size() >> 1;
        for(const int val: numbers)
        {
            if(m[val] > halfLength)
            {
                return val;
            }
        }
        return 0;
    }
};
```

> 投票版本

```
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) 
    {
        int target = numbers[0];
        int count = 1;
        for(int i=1; i<numbers.size(); i++)
        {
            int val = numbers[i];
            if(count == 0)
            {
                target = val;
                count = 1;
            }
            else if(target != val)
            {
                count --;
            }
            else
            {
                count ++;
            }
        }
        return target;
    }    
};
```

## 2. 最小的 k 个数

> 冒泡思想

```
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) 
    {
        vector<int> ans;
        for(int i=0; i<k; i++)
        {
            for(int j=0; j<input.size()-1-i; j++)
            {
                if(input[j] < input[j+1])
                {
                    swap(input[j], input[j+1]);
                }
            }
            ans.push_back(input[input.size()-1-i]);
        }
        return ans;
    }
};
```

> 堆排序

```
class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        if(k == 0){
            return {};
        }
        priority_queue<int> pq;
        for(int i=0; i<k; i++){
            pq.push(input[i]);
        }
        
        for(int i=k; i<input.size(); i++){
            if(input[i] < pq.top()){
                pq.pop();
                pq.push(input[i]);
            }
        }
        
        vector<int> res;
        while(!pq.empty()){
            int a = pq.top();
            res.push_back(a);
            pq.pop();
        }
        
        return res;
    }
};
```

## 3. 数据流中的中位数

```
class Solution {
public:
    #define SCD static_cast<double>
    priority_queue<int> min_q; 
    priority_queue<int, vector<int>, greater<int>> max_q; 

    void Insert(int num)
    {
        // 最大堆放小数
        // 最小堆放大数
        min_q.push(num); 
        max_q.push(min_q.top()); 
        min_q.pop();

        if (min_q.size() < max_q.size())
        {
            min_q.push(max_q.top());
            max_q.pop();
        }
    }

    double GetMedian()
    { 
        return min_q.size() > max_q.size() ? SCD(min_q.top()) : SCD(min_q.top() + max_q.top()) / 2;
    }

};
```

## 4.连续子数组的最大和

> 贪心版本

```
class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) 
    {
        if(array.empty())
        {
            return 0;
        }
        
        int curSum = 0;
        int maxSum = -INT_MAX;
        for(const int val: array)
        {
            if(curSum <= 0)
            {
                curSum = val;
            }
            else
            {
                curSum += val;
            }
            if(curSum > maxSum)
            {
                maxSum = curSum;
            }
        }
        return maxSum;
    }
};
```

> 动态规划

```
class Solution {
public:
    int FindGreatestSumOfSubArray(vector<int> array) {
        int sz = array.size();
        vector<int> dp(sz+1, 1);
        dp[0] = 0; 
        int ret = array[0];
        for (int i=1; i<=sz; ++i) {
            dp[i] = max(array[i-1], dp[i-1]+array[i-1]);
            ret = max(ret, dp[i]);
        }
        return ret;
    }
};
```

## 5. 整数 1 出现的次数

```
class Solution {
public:
    int NumberOf1Between1AndN_Solution(int n) 
    {
        int base = 1;
        int count = 0;
        while(n / base){
            int cur = n / base % 10;
            int higher = n / base / 10;
            int lower = n % base;
            if(cur == 1)
            {
                count += higher * base + lower + 1;
            }
            else if(cur == 0)
            {
                count += higher * base;
            }
            else
            {
                count += (higher + 1) * base;
            }
            base *= 10;
        }
        return count;
    }
};
```

## 6. 数字序列中某一位的数字

```
class Solution {
public:
    int findNthDigit(int n) {
        // write code here
        int digit = 1;
        long long start = 1;
        long long cnt = 9;
        while(n>cnt)
        {
            n-=cnt;
            digit ++;
            start *= 10;
            cnt = 9 * start * digit;
        }
        n --;
        int num = start + n / digit;
        int ans = to_string(num)[n % digit] - '0';
        return ans;
    }
};
```

## 7. 把数组排成最小的数

```
bool cmp(const string &a, const string &b)
{
    string s1 = a + b;
    string s2 = b + a;
    return s1 < s2;
}

class Solution {
public:
    string PrintMinNumber(vector<int> numbers) 
    {
        vector<string> sort_nums;
        for(auto &i: numbers)
        {
            sort_nums.push_back(to_string(i));
        }
        sort(sort_nums.begin(), sort_nums.end(), cmp);
        string result = "";
        for(const auto s: sort_nums)
        {
            result += s;
        }
        return result;
    }
};
```

## 8. 把数字翻译成字符串

```
class Solution {
public:
    int solve(string nums) {
        vector<int> res(nums.size()+1,0);
        res[0] = 1;
        for(int i = 0;i<nums.size();i++){
            // 1 bit
            if(nums[i] != '0') { 
                res[i+1] += res[i];
            }
            // 2 bits
            if(i > 0 && nums[i-1] != '0' && (nums[i-1]-'0')*10+(nums[i]-'0') <= 26) {
                res[i+1] += res[i-1];
            }
        }
        return res[nums.size()];
    }
};
```

## 9. 礼物的最大价值

> 动态规划（二维备忘录）

```
class Solution {
public:
    int maxValue(vector<vector<int> >& grid) 
    {
        int dp[205][205];
        dp[1] = grid[0][0];
        int n = grid.size();
        int m = grid[0].size();
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                int x=i+1, y=j+1;
                dp[x][y]=max(dp[x-1][y], dp[x][y-1]) + grid[i][j];
            }
        }
        return dp[n][m];
    }
};
```

> 动态规划（二维备忘录，使用原数组）

```
class Solution {
public:
    int maxValue(vector<vector<int> >& grid) {
        for(int i =1;i<grid[0].size();i++){
            grid[0][i] += grid[0][i-1];
        }
        for(int i =1;i<grid.size();i++){
            grid[i][0] +=grid[i-1][0];
        }
        for(int i =1;i<grid.size();i++){
            for(int j =1;j<grid[0].size();j++){
                grid[i][j] += max(grid[i-1][j],grid[i][j-1]);
            }
        }
        return grid[grid.size()-1][grid[0].size()-1];
    }
};
```

> 动态规划（一维备忘录）

```
class Solution {
public:
    int maxValue(vector<vector<int> >& grid) {
        if(grid.size() == 0) return 0;
        vector<int> dp(grid[0].size()+1,0);
        for(int i =0;i<grid.size();i++){
            for(int j = 0;j<grid[0].size();j++){
                dp[j+1] = max(dp[j+1]+grid[i][j],dp[j]+grid[i][j]);
            }
        }
        return dp[grid[0].size()];
    }
};
```

## 10. 最长不含重复字符的子字符串

```
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> m;
        int start = 0;
        int res = 0;
        for(int i=0;i<s.size();i++){
            if(m.find(s[i])!= m.end()){
                start = max(start,m[s[i]]+1);
            }
             
            res = max(res,i-start+1);
            m[s[i]] = i;
        }
         
        return res;
    }
};
```

## 11. 丑数

```
class Solution {
public:
    int GetUglyNumber_Solution(int index) {
        if(index == 0) return 0;
        set<long long> s; // 候选值
        s.insert(1); // 初始值
        while(s.size()){
            auto v = *s.begin(); // 最小的
            s.erase(s.begin());
            if(!--index)return v; // 满足个数
            s.insert(v*2); // 扩展*2
            s.insert(v*3); // 扩展*3
            s.insert(v*5); // 扩展*5
        }
        return -1;
    }
};
```

## 12. 第一个只出现一次的字符

```
class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        unordered_map<char, int> m;
        for(char c : str) m[c]++;
        for(int i = 0; i < str.size(); i++) {
            if(m[str[i]] == 1) return i;
        }
        return -1;
    }
};
```

## 13. 数组中的逆序对

```
class Solution {
public:
    long long  merge(vector<int>& nums,int L,int M,int R ){
        vector<int>help(R-L+1);
        int sum = 0;
        int i = 0;
        int p1 = L;
        int p2 = M+1;
        while(p1<=M&&p2<=R){
            sum += nums[p1]>nums[p2]?(M-p1+1):0;
            help[i++] = nums[p1]<nums[p2]?nums[p1++]:nums[p2++];
        }
        while(p1<=M){
            help[i++] = nums[p1++];
        }
        while(p2<=R){
            help[i++] = nums[p2++];
        }
        for(int j=0;j<R-L+1;j++){
            nums[L+j] = help[j];
        }
        return sum;
    }
    long long  mergesort(vector<int>& nums,int L,int R){
        if(L == R) return 0;
        int M = L+((R-L)>>1);
        return mergesort(nums, L, M)+mergesort(nums, M+1, R)+merge(nums,L,M,R);
        
    }
    int InversePairs(vector<int> data) {
        int L = 0;
        int R = data.size()-1;
        return mergesort(data, L, R)%1000000007;
    }
};
```

## 14. 链表的第一个公共节点

```
/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if(pHead1 == nullptr || pHead2 == nullptr)
        {
            return nullptr;
        }
        
        ListNode *p1 = pHead1;
        ListNode *p2 = pHead2;
        while(p1 != p2)
        {
            p1 = p1->next;
            p2 = p2->next;
            if(p1 != p2)
            {
                if(p1 == nullptr)
                {
                    p1 = pHead2;
                }
                if(p2 == nullptr)
                {
                    p2 = pHead1;
                }
            }
        }
        return p1;
    }
};
```