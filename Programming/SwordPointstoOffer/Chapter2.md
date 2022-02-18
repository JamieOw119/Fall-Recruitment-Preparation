# 第二章：面试需要的基础知识

## 1. 赋值运算符函数

```
class CMyString
{
public:
    CMyString(char *pData = nullptr);
    CMyString(const CMyString &str);
    ~CMyString(void);

    CMyString &operator=(const CMyString &str);

private:
    char *m_pDate;
};

CMyString::CMyString(char *pData)
{
    if(pData == nullptr)
    {
        m_pData = new char[1];
        m_pData[0] = '\0';
    }
    else
    {
        int length = strlen(pData);
        m_pDate = new char[length + 1];
        strcpy(m_pData, pData);
    }
}

CMyString::CMyString(const CMyString &str)
{
    int length=strlen(str.m_pData);
    m_pData = new char[length+1];
    strcpy(m_pData, str.m_pData);
}

CMyString::~CMyString()
{
    delete[] m_pData;
}

CMyString &CMyString::operator = (const CMyString &str)
{
    if(this==&str)
    {
        return *this;
    }
    delete []m_pData;
    m_pData = nullptr;

    m_pData = new char[strlen(str.m_pData) + 1];
    strcpy(m_pData, str.m_pData);

    return *this;
}
```

## 2. 实现 Singleton 模式
> hungry man
```
class Singleton
{
private:
    Singleton()
    {
        cout<<"Singleton"<<endl;
    }
    static Singleton *instance;

public:
    static Singleton *GetSingleton()
    {
        return instance;
    }
    static void Destroy()
    {
        delete instance;
        instance = nullptr;
    }
};

Singleton* Singleton::instance = new Singleton();

int main()
{
    Singleton *s1 = Singleton::GetSingleton();
    Singleton *s2 = Singleton::GetSingleton();
    Singleton *s3 = Singleton::GetSingleton();
    cout<<s1<<endl;
    cout<<s2<<endl;
    cout<<s3<<endl;
    return 0;
}
```
> lazy man
```
class Singleton
{
private:
    Singleton()
    {
        cout<<"Singleton"<<endl;
    }
    static Singleton *instance;

public:
    // p.s. In c++ 11, 
    // static local variaties' initialization
    // is implemented on thread safety
    static Singleton *GetSingleton()
    {
        if(instance == nullptr)
        {
            instance = new Singleton();
            cout<<"Create Singleton"<<endl;
        }
        else
        {
            cout<<"Singleton exists"<<endl;
        }
        return instance;
    }

    static void Destory()
    {
        delete instance;
        instance = nullptr;
    }
};

Singleton* Singleton::instance = NULL;
int main()
{
    Singleton *s1 = Singleton::GetSingleton();
    Singleton *s2 = Singleton::GetSingleton();
    Singleton *s3 = Singleton::GetSingleton();
    cout<<s1<<endl;
    cout<<s2<<endl;
    cout<<s3<<endl;
    return 0;
}
```


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
```
class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        if(array.size() == 0)  return false;
        int c = array[0].size();
        int r = array.size();
        int left = 0, down = r - 1;
        while(left < c && down >= 0)
        {
            int current = array[down][left];
            if(current==target)
            {
                return true;
            }
            else if(current<target)
            {
                left ++;
            }
            else
            {
                down --;
            }
        }
        return false;
    }
};
```
> binary search
```

```

## 5. 替换空格

## 6. 从尾部到头打印链表

## 7. 重建二叉树

## 8. 二叉树的下一个节点

## 9. 用两个栈实现队列


