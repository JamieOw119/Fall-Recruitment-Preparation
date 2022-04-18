# 第七章 两个面试案例

## 1. 把字符串转换成整数(atoi)

```
class Solution {
public:
    int StrToInt(string s) 
    {
        int len = s.size();
        int index = 0;
        
        // 去除前导空格
        while(index < len) 
        {
            if(s[index] != ' ')
            {
                break;
            }
            index ++;
        }
        if(index == len)
        {
            return 0;
        }
        
        int sign = 1;
        if(s[index] == '+')
        {
            index ++;
        }
        else if(s[index] == '-')
        {
            index ++;
            sign = -1;
        }
        
        int res = 0;
        while(index < len)
        {
            char c = s[index];
            if(c<'0' || c>'9')
            {
                break;
            }
            if(res > INT_MAX / 10 || (res == INT_MAX / 10 && (c - '0') > INT_MAX % 10))
                return INT_MAX;
            if(res < INT_MIN / 10 || (res == INT_MIN / 10 && (c- '0') > -(INT_MIN % 10)))
                return INT_MIN;
            res = res * 10 + sign * (c - '0');
            index ++;
        }
        return res;
    }
};
```


## 2. 树中两个节点的最低公共祖先

> 二叉搜索树

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
    int ret = 0;
    int lowestCommonAncestor(TreeNode* root, int p, int q) 
    {
        TreeNode *cur = root;
        while(true)
        {
            if(p < cur->val && q < cur->val)
            {
                cur = cur->left;
            }
            else if(p > cur->val && q > cur->val)
            {
                cur = cur->right;
            }
            else
            {
                break;
            }
        }
        return cur->val;
    }
};
```

> 二叉树但非搜索树

> 先序版本

```
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 * };
 */

class Solution {
public:
    int lowestCommonAncestor(TreeNode* root, int o1, int o2) {
        TreeNode *lca = LCA(root, o1, o2);
        return lca->val;
    }
    
    TreeNode *LCA(TreeNode *r, int o1, int o2)
    {
        if(!r)
        {
            return nullptr;
        }
        if(r->val == o1 || r->val == o2)
        {
            return r;
        }
        TreeNode *left = LCA(r->left, o1, o2);
        TreeNode *right = LCA(r->right, o1, o2);
        if(!left) return right;
        if(!right) return left;
        return r;
    }
};
```

> 非递归版本

```
/**
 * struct TreeNode {
 *    int val;
 *    struct TreeNode *left;
 *    struct TreeNode *right;
 * };
 */

class Solution {
public:
    int lowestCommonAncestor(TreeNode* root, int o1, int o2) 
    {
        stack<int> s1;
        stack<int> s2;
        getPath(root, o1,s1);
        getPath(root, o2,s2);
        int same = 0;
        while(!s1.empty() && !s2.empty())
        {
            if(s1.top() != s2.top())
            {
                return same;
            }
            same = s1.top();
            s1.pop();
            s2.pop();
        }
        return same;
    }
    bool getPath(TreeNode* root, int p,stack<int>& stk)
    {
        if(root == NULL )
        {
            return false;
        }
        if(root->val == p || getPath(root->left,p,stk) || getPath(root->right, p,stk))
        {
            stk.push(root->val);
            return true;
        }
        return false;
    }

};
```

> p.s.1 也可以用链表来存储 path，然后用求两个链表公共节点的方法来求最近祖先节点