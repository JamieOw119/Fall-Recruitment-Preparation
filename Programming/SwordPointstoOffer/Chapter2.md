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
class Solution {
public:
    bool double_binary(vector<vector<int>> arr,int x1,int x2,int y1, int y2,int target){
        if(x1 == x2 || y1 == y2) return false;
        int xmid = (x1+x2)/2, ymid = (y1+y2)/2;
        int num = arr[xmid][ymid];
        if(num == target) return true;
        if(num > target)
        {
           if(double_binary(arr, x1, xmid, y1, y2, target)) return true;
           if(double_binary(arr,xmid,x2,y1,ymid,target)) return true;
        }
        else
        {
            if(double_binary(arr, xmid+1, x2, y1, y2, target)) return true;
            if(double_binary(arr, x1, xmid+1, ymid+1, y2, target)) return true;
        }
        return false;
    }
    bool Find(int target, vector<vector<int> > array) {
        if(array.size() == 0) return false;
        return double_binary(array, 0, array.size(), 0, array[0].size(), target);
    }
};
```

## 5. 替换空格
```
class Solution {
public:
    string replaceSpace(string s) {
        if(s.size()==0)
        {
            return s;
        }
        
        int count = 0;
        for(int i=0;i<s.size();i++)
        {
            if(s[i]==' ')
            {
                count ++;
            }
        }
        
        int index_old = s.size() - 1;
        int index_new = s.size() + count*2 - 1;
        s.resize(s.size()+count*2);
        
        while(index_old != -1)
        {
            if(s[index_old]==' ')
            {
                s[index_new--]='0';
                s[index_new--]='2';
                s[index_new--]='%';
                index_old--;
            }
            else
            {
                s[index_new--] = s[index_old--];
            }
        }
        return s;
    }
};
```

> 相关题目：两个有序数组 A1 和 A2，内存中 A1 末尾有足够空间容纳 A2。请实现一个函数，把 A2 中所有数字插入 A1 中，并且保持有序。

```
class Solution
{
public:
    // p.s. Suppose the data is arranged in ascending order
    void array_insert(vector<int> &arr1, vector<int> arr2)
    {
        int len1 = arr1.size();
        int len2 = arr2.size();
        if(len1 == 0 || len2 == 0)
        {
            return;
        }
        
        arr1.resize(arr1.size()+arr2.size());
        int index1 = len1 - 1;
        int index2 = len2 - 1;

        for(int i = arr1.size() - 1; i >=0; i--)
        {
            if(arr1[index1] > arr2[index2])
            {
                arr1[i] = arr1[index1--];
            }
            else
            {
                arr1[i] = arr2[index2--];
            }
        }
        return;
    }
};
```

## 6. 从尾部到头打印链表
```
/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        ListNode *pNode = head;
        stack<ListNode *> nodes;
        vector<int> res;
        
        if(head == nullptr)
        {
            return res;
        }
        
        while(pNode != nullptr)
        {
            nodes.push(pNode);
            pNode = pNode->next;
        }
        
        while(!nodes.empty())
        {
            pNode = nodes.top();
            nodes.pop();
            res.push_back(pNode->val);
        }
        return res;
    }
};
```

## 7. 重建二叉树
```
class Solution {
private:
    TreeNode *root;
    vector<int> i, p;
public:
    TreeNode* build(int lp, int rp, int lv, int rv)
    {
        if(lp > rp)
        {
            return nullptr;
        }
        TreeNode *now = new TreeNode(p[lp]);
        int index = lv;
        while(index <= rv && p[lp] != i[index])
        {
            index ++;
        }
        int len = index - lv;
        now->left = build(lp+1, lp+len, lv, index - 1);
        now->right = build(lp + len + 1, rp, index + 1, rv);
        return now;
    }
    
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        p = pre, i = vin;
        TreeNode *root = build(0, pre.size()-1, 0, vin.size()-1);
        return root;
    }
};
```

## 8. 二叉树的下一个节点
```
/*
struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};
*/
class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode) {
        if(!pNode)
        {
            return nullptr;
        }
        if(pNode->right)
        {
            TreeLinkNode* rightChild = pNode->right;
            while(rightChild->left)
            {
                rightChild = rightChild->left;
            }
            return rightChild;
        }
        while(pNode->next)
        {
            if(pNode->next->left == pNode)
            {
                return pNode->next;    
            }
            pNode = pNode->next;
        }
        return nullptr;
    }
};
```

## 9. 用两个栈实现队列
```
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        int cur, tmp;
        while(!stack1.empty())
        {
            cur = stack1.top();
            stack1.pop();
            stack2.push(cur);
        }
        stack2.pop();
        while(!stack2.empty())
        {
            tmp = stack2.top();
            stack2.pop();
            stack1.push(tmp);
        }
        return cur;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
```

## 10. 斐波那契数列
> recurrence

```
class Solution {
public:
    int Fibonacci(int n) {
        int MOD = 1000000007;
        if (n < 2) {
            return n;
        }
        int p = 0, q = 0, r = 1;
        for (int i = 2; i <= n; ++i) {
            p = q; 
            q = r; 
            r = (p + q)%MOD;
        }
        return r;
    }
};
```

> recursion

```
class Solution {
public:
    int recursion(int n)
    {
        if(n==0)
        {
            return 0;
        }
        if(n==1)
        {
            return 1;
        }
        return recursion(n-1) + recursion(n-2);
    }
    
    int Fibonacci(int n) 
    {
        return recursion(n);
    }
};
```

> magic: O(logn)

```
struct Matrix2x2
{
    int m_00;
    int m_01;
    int m_10;
    int m_11;
    Matrix2x2
    (
        int m00 = 0,
        int m01 = 0,
        int m10 = 0,
        int m11 = 0
    ):m_00(m00),m_01(m01),m_10(m10),m_11(m11){}
};

Matrix2x2 MatrixMultiply(const Matrix2x2 &mat1, const Matrix2x2 &mat2)
{
    return Matrix2x2
    (
        mat1.m_00 * mat2.m_00 + mat1.m_01 * mat2.m_10,
        mat1.m_00 * mat2.m_01 + mat1.m_01 * mat2.m_11,
        mat1.m_10 * mat2.m_00 + mat1.m_11 * mat2.m_10,
        mat1.m_10 * mat2.m_01 + mat1.m_11 * mat2.m_11
    );
}

Matrix2x2 MatrixPower(int n)
{
    // a little bit inappropriate ...
    if(n == 0) return Matrix2x2(0, 0, 0, 0);
    
    Matrix2x2 mat;
    if(n==1)
    {
        mat = Matrix2x2(1,1,1,0);
    }
    else if(n % 2 == 0)
    {
        mat = MatrixPower(n / 2);
        mat = MatrixMultiply(mat, mat);
    }
    else if(n % 2 == 1)
    {
        mat = MatrixPower((n-1)/2);
        mat = MatrixMultiply(mat, mat);
        mat = MatrixMultiply(mat, Matrix2x2(1,1,1,0));
    }
    return mat;
}

class Solution {
public:
    int Fibonacci(int n) 
    {
        if(n==0) return 0;
        if(n==1) return 1;
        Matrix2x2 mat = MatrixPower(n-1);
        return mat.m_00;
    }
};
```

> 相关题目 1：青蛙跳台阶问题
> - 实质是斐波那契问题
> - 进阶版数学归纳法证明 [证明过程的地址](https://blog.csdn.net/weixin_43160744/article/details/120472548)
> - 还有常数计算复杂度的解法（不强求）

```
class Solution {
public:
     int numWays(int n) {
        int i0 = 1,i1 = 1,i2 = 2, sum = 0;
        if(n < 2){
            return 1;
        }
        for(int i = 2;i <= n;i++){
            sum = (i0 + i1) % 1000000007;
            i0 = i1;
            i1 = sum;
        }
        return sum;
    }
};
```

> 
> 相关题目 2：矩形覆盖问题
> - f(8) = 2*f(6) + f(7)
> - f(2) = 3
> - f(1) = 1

## 11. 旋转数组的最小数字
```
class Solution {
public:
    int minNumberInRotateArray(vector<int> rotateArray) {
        if(rotateArray.size()==0)
            return 0;
        int index1 = 0, index2 = rotateArray.size() - 1;
        int indexMid = index1;
        
        while(rotateArray[index1]>=rotateArray[index2])
        {
            // index2 已经指向最小数字
            if(index2-index1==1)
            {
                indexMid = index2;
                break;
            }
            
            int indexMid = (index1 + index2) / 2;
            
            // original array: 0 1 1 1 1
            // changed array 1: 1 0 1 1 1
            // changed array 2: 1 1 1 0 1
            if(rotateArray[index1]==rotateArray[index2]
               &&rotateArray[index1]==rotateArray[indexMid])
            {
                int result = rotateArray[index1];
                for(int i=index1+1; i<=index2; i++)
                {
                    if(result>rotateArray[i])
                    {
                        result = rotateArray[i];
                    }
                }
                return result;
            }
            
            // 落在前半段，向两段交界靠拢
            if(rotateArray[indexMid]>=rotateArray[index1])
            {
                index1 = indexMid;
            }
            // 落在后半段，向两段交界靠拢
            else if(rotateArray[indexMid]<=rotateArray[index2])
            {
                index2 = indexMid;
            }
        }
        
        return rotateArray[indexMid];
    }
};
```

## 12. 矩阵中的路径
```
class Solution {
public:
    int dx[4][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};
    
    bool hasPathCore(vector<vector<char> >& matrix, string &word, int row, int col, int pathLength)
    {
        if(word[pathLength] != matrix[row][col])
        {
            return false;
        }
        
        char temp  = matrix[row][col];
        matrix[row][col] = '*';
        pathLength ++;
        if(word.size() == pathLength)
        {
            return true;
        }
        
        bool hasPath;
        for(int i=0; i<4; i++)
        {
            row += dx[i][0];
            col += dx[i][1];
            if (row >= 0 && row < matrix.size() && col >= 0 && col < matrix[0].size())
            {
                if (hasPathCore(matrix, word, row, col, pathLength)){
                    return true;
                }            
            }
            row -= dx[i][0];
            col -= dx[i][1];
        }
        
        matrix[row][col]=temp;
        return false;
    }
    
    bool hasPath(vector<vector<char> >& matrix, string word) {
        if(matrix.size()==0 || matrix[0].size()==0 || word.size()==0)
        {
            return false;
        }
        
        int pathLength = 0;
        
        for(int r=0; r<matrix.size(); r++)
        {
            for(int c=0; c<matrix[0].size(); c++)
            {
                if(hasPathCore(matrix, word, r, c, pathLength))
                {
                    return true;
                }
            }
        }
        return false;
    }
};
```

## 13. 机器人的运动范围
```
class Solution {
public:
    int movingCount(int threshold, int rows, int cols) {
        if(threshold<0||rows<=0||cols<=0)
        {
            return 0;
        }
        vector<vector<bool>> map(rows, vector<bool>(cols));
        int count = dfs(threshold, 0, 0, map);
        map.clear();
        return count;
    }
    
    int getDigitSum(int num)
    {
        int sum=0;
        while(num)
        {
            sum += num % 10;
            num /= 10;
        }
        return sum;
    }
    
    int check(int threshold, int row, int col, const vector<vector<bool>> &map)
    {
        if(row >= 0 && row < map.size() && col >= 0 && col < map[0].size() 
           && !map[row][col] && getDigitSum(row) + getDigitSum(col) <= threshold)
        {
            return true;
        }
        return false;
    }
    
    int dfs(int threshold, int row, int col, vector<vector<bool>> &map)
    {
        int count = 0;
        if(check(threshold, row, col, map))
        {
            map[row][col] = true;
            count = 1 + dfs(threshold, row + 1, col, map) 
            + dfs(threshold, row - 1, col, map) 
            + dfs(threshold, row, col + 1, map) 
            + dfs(threshold, row, col - 1, map); 
        }
        
        return count;
    }
};
```

## 14.剪绳子

> 动态规划

```
class Solution {
public:
    int cutRope(int number) {
        if(number<2) return 0;
        if(number==2) return 1;
        if(number==3) return 2;
        
        int *product=new int[number+1];
        product[0] = 0;
        product[1] = 1;
        product[2] = 2;
        product[3] = 3;
        
        int max = 0;
        for(int i=4; i<=number; i++)
        {
            max = 0; 
            for(int j=1; j<=i/2; j++)
            {
                int prdt = product[j] * product[i - j];
                if(max < prdt) max = prdt;
                product[i] = max;
            }
            
        }
        
        max = product[number];
        delete product;
        return max;
    }
};
```

> 贪心算法

```
class Solution {
public:
    int cutRope(int n) {
        if(n <= 3) 
            return n - 1;
        int b = n % 3, p = 1000000007;
        long ret = 1;
        int lineNums=n/3;           
        for(int i=1;i<lineNums;i++) 
            ret = 3*ret % p;
        if(b == 0) 
            return (int)(ret * 3 % p);   
        if(b == 1) 
            return (int)(ret * 4 % p);   
        return (int)(ret * 6 % p);     // b == 2 
    }
};
```

## 15. 二进制中 1 的个数
```
class Solution {
public:
     int  NumberOf1(int n) {
         int count=0;
         while(n)
         {
             count++;
             // 把该整数最右边的 1 变成 0
             n = (n-1)&n;
         }
         return count;
     }
};
```

> 相关题目 1：判断一个整数是不是 2 的整数次方，如果是的话这个数只有 1 位是 1，其他都是 0。(n-1) & n = 0
> 
> 相关题目 2：输入两个整数 m 和 n， 需要改变 m 的二进制数多少位才能得到 n。
> - Step 1：k = m ^ n
> - Step 2：NumberOf1(k)




