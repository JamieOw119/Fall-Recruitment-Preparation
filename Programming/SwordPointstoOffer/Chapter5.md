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