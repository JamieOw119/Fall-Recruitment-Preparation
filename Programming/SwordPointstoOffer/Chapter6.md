# 面试中的各项能力

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