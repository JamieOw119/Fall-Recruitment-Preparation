# 第二章：面试需要的基础知识

## 1. 赋值运算符函数

## 2. 实现 Singleton 模式

## 3. 数组中重复的数字

```
class Solution {
public:
    /*
     * @param numbers int vector 
     * @return int
     */
    int duplicate(vector<int>& numbers) {
        int dup = -1;
        if(numbers.size()==0)
        {
            return -1;
        }
        for(int i=0; i<numbers.size(); i++)
        {
            if(numbers[i]<0||numbers[i]>numbers.size()-1)
            {
                return  -1;
            }
        }
        
        for(int i=0; i<numbers.size(); i++)
        {
            while(numbers[i] != i)
            {
                if(numbers[i] == numbers[numbers[i]])
                {
                    return numbers[i];
                }
                int tmp = numbers[i];
                numbers[i] = numbers[tmp];
                numbers[tmp] = tmp;
            }
        }
        
        return -1;
    }
};
```

> 不修改数组找出重复数字

```
class Solution {
public:
    /*
     * @param numbers int整型vector 
     * @return int整型
     */
    int duplicate(vector<int>& numbers) {
        int dup = -1;
        if(numbers.size()==0)
        {
            return -1;
        }
        for(int i=0; i<numbers.size(); i++)
        {
            if(numbers[i]<1||numbers[i]>numbers.size())
            {
                return  -1;
            }
        }
        
        int start = 1, end = numbers.size() - 1;

        while(end > start)
        {
            int mid = (end - start) >> 1 + start;
            int count = countRange(numbers, start, mid);
            if(end == start)
            {
                if(count > 1)
                {
                    return start;
                }
                else
                {
                    break;
                }
            }
            if(count > (middle - start + 1))
            {
                end = middle;
            }
            else
            {
                start = mid + 1;
            }
        }

        return -1;
    }

    int countRange(vector<int> &numbers, int start, int end)
    {
        if(numbers.size() == 0)
        {
            return 0;
        }
        int count = 0;
        for(int i=0; i<length; i++)
        {
            if(numbers[i]>=start && numbers[i] <= end)
            {
                count++;
            }
        }
        return count;
    }
};
```

## 4. 二维数组中的查找

## 5. 替换空格

## 6. 从尾部到头打印链表

## 7. 重建二叉树

## 8. 二叉树的下一个节点

## 9. 用两个栈实现队列


