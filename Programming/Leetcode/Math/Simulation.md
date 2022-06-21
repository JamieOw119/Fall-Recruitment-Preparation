# Math

## 模拟类问题

### 模拟运算

#### 7. 整数反转

```
class Solution {
public:
    int reverse(int x) {
        int ans = 0;
        while(x)
        {
            int pop = x % 10;
            if(ans > INT_MAX / 10 || (ans == INT_MAX / 10) && pop > 7)
                return 0;
            if(ans < INT_MIN / 10 || (ans == INT_MIN / 10) && pop < -8)
                return 0;
            ans = ans * 10 + pop;
            x /= 10;
        }
        return ans;
    }
};
```

#### 9. 回文数

```
class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0 || (x%10 == 0) && x != 0)
        {
            return false;
        }

        int temp = 0;
        while(x > temp)
        {
            temp = temp * 10 + x % 10;
            x /= 10;
        }
        return x == temp || x == temp / 10;
    }
};
```

#### 43. 字符串相乘

```
class Solution {
public:
    string multiply(string num1, string num2) {
        if(num1 == "0" || num2 == "0")
        {
            return "0";
        }

        int m = num1.size(), n = num2.size();
        auto ansArr = vector<int>(m + n);

        for (int i = m - 1; i >= 0; i--) 
        {
            int x = num1.at(i) - '0';
            for (int j = n - 1; j >= 0; j--) 
            {
                int y = num2.at(j) - '0';
                ansArr[i + j + 1] += x * y;
            }
        }
        for (int i = m + n - 1; i > 0; i--) 
        {
            ansArr[i - 1] += ansArr[i] / 10;
            ansArr[i] %= 10;
        }

        int index = ansArr[0] == 0 ? 1 : 0;
        string ans;
        while (index < m + n) 
        {
            ans.push_back(ansArr[index]);
            index++;
        }
        for (auto &c: ans) 
        {
            c += '0';
        }
        return ans;
    }
};
```

#### 48. 旋转图像

```
class Solution {
public:
    void rotate(vector<vector<int>>& matrix)
    {
        int row = matrix.size();
        int col = matrix[0].size();
        for(int i = 0; i < col; i++)
        {
            for(int j = i + 1; j < row; j ++)
            {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        for(int i = 0; i < row; i++)
        {
            for(int j = 0, k = col - 1; j < k; j ++, k --)
            {
                swap(matrix[i][j], matrix[i][k]);
            }
        }
        return;
    }
};
```