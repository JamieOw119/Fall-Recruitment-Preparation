# 第四章 解决面试题的思路

## 1. 镜像二叉树

```
/**
 * struct TreeNode {
 *    int val;
 *    struct TreeNode *left;
 *    struct TreeNode *right;
 *    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */

class Solution {
public:
    TreeNode* Mirror(TreeNode* pRoot) {
        if(!pRoot)
            return NULL;
        else {
            swap<TreeNode*>(pRoot->left, pRoot->right);
            Mirror(pRoot->left);
            Mirror(pRoot->right);
        }
        return pRoot;
    }
};
```

## 2. 对称二叉树

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
};
*/
class Solution {
public:
    bool isSymmetrical(TreeNode* pRoot) {
        if(pRoot == nullptr)
        {
            return true;
        }
        return isSymmetricalCore(pRoot->left, pRoot->right);
    }
    
    bool isSymmetricalCore(TreeNode *left, TreeNode *right)
    {
        if(!left && !right)
        {
            return true;
        }
        if(!left || !right)
        {
            return false;
        }
        if(left->val == right->val)
        {
            return isSymmetricalCore(left->left, right->right)
                && isSymmetricalCore(left->right, right->left);
        }
        else
        {
            return false;
        }
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
};
*/
class Solution {
public:
    bool isSymmetrical(TreeNode* pRoot) {
        if (!pRoot)
            return true; 
        queue<TreeNode*> q; // 定义队列
        q.push(pRoot); q.push(pRoot); // 根结点入队两次
        while (!q.empty()) {
            TreeNode* n1 = q.front(); 
            q.pop(); 
            TreeNode* n2 = q.front(); 
            q.pop();
            if ((!n1 && n2) || (n1 && !n2)) 
                return false;
            if (!n1 && !n2)
                continue;
            if (n1->val != n2->val)
                return false;
            q.push(n1->left); q.push(n2->right); 
            q.push(n1->right); q.push(n2->left);
        }
        return true;
    }
};
```

## 3. 顺时针打印矩阵

```
class Solution {
public:
    vector<int> printMatrix(vector<vector<int> > matrix)
    {
        vector<int> res;
        if(matrix.size()==0 || matrix[0].size()==0)
        {
            return res;
        }
        int up = 0, down = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;
        while(true)
        {
            for(int i=left; i<=right; i++)
            {
                res.push_back(matrix[up][i]);
            }
            up ++;
            if(up>down) break;
            
            for(int i=up; i<=down; i++)
            {
                res.push_back(matrix[i][right]);
            }
            right --;
            if(left>right) break;
            
            for(int i=right; i>=left; i--)
            {
                res.push_back(matrix[down][i]);
            }
            down --;
            if(up>down) break;
            
            for(int i=down; i>=up; i--)
            {
                res.push_back(matrix[i][left]);
            }
            left ++;
            if(left>right)
            {
                break;
            }
        }
        return res;
    }
};
```

## 4. 包含 min 函数的栈

```
class Solution {
public:
    stack<int> s1;
    stack<int> s2;
    
    void push(int value) {
        if(!s2.empty())
        {
            if(value < s2.top())
            {
                s2.push(value);
            }
            else
            {
                s2.push(s2.top());
            }
        }
        else
        {
            s2.push(value);
        }
        s1.push(value);
    }
    void pop() {
        if(!s1.empty())
        {
            s1.pop();
        }
        if(!s2.empty())
        {
            s2.pop();
        }
    }
    int top() {
        if(!s1.empty())
        {
            return s1.top();
        }
        return 0;
    }
    int min() {
        if(!s2.empty())
        {
            return s2.top();
        }
        return 0;
    }
};
```

## 5. 栈的压入、弹出序列

```
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        if(pushV.size()==0 && popV.size()==0)
        {
            return true;
        }
        if(pushV.size()==0 || popV.size()==0)
        {
            return false;
        }
        
        stack<int> s;
        int j = 0;
        for(int i=0; i<pushV.size(); i++)
        {
            s.push(pushV[i]);
            while(!s.empty() && popV[j] == s.top())
            {
                s.pop();
                j++;
            }
        }
        return s.empty();
    }
};
```

## 6. 从上往下打印二叉树

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
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        vector<int> res;
        if(!root)
        {
            return res;
        }
        queue<TreeNode *> q;
        q.push(root);
        while(!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();
            res.push_back(node->val);
            if(node->left)
                q.push(node->left);
            if(node->right)
                q.push(node->right);
        }
        return res;
    }
};
```

> 题目二：分行从上到下打印二叉树

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root)
        {
            return result;
        }
        
        queue<TreeNode *> q;
        q.push(root);
        while(!q.empty())
        {
            int size = q.size();
            vector<int> res;
            while(size--)
            {
                TreeNode *node = q.front();
                q.pop();
                res.push_back(node->val);
                if(node->left)
                {
                    q.push(node->left);
                }
                if(node->right)
                {
                    q.push(node->right);
                }
            }
            result.push_back(res);
        }
        return result;
    }
};
```

> 题目三：之字形从上到下打印二叉树

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > result;
        if(!root)
        {
            return result;
        }

        queue<TreeNode *> q;
        q.push(root);
        int zigzag = -1;
        
        while(!q.empty())
        {
            int size = q.size();
            vector<int> res;

            while(size--)
            {
                TreeNode *node = q.front();
                q.pop();
                res.push_back(node->val);
                
                if(node->left)
                {
                    q.push(node->left);
                }
                if(node->right)
                {
                    q.push(node->right);
                }
            }

            if(zigzag > 0)
            {
                reverse(res.begin(), res.end());
            }
            zigzag = -zigzag;
            
            result.push_back(res);
        }
        return result;
    }
};
```

## 7. 二叉搜索树的后序遍历序列

> 递归解法

```
class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.size() == 0){
            return false; 
        }

        return checkPostTree(sequence,  0 , sequence.size() - 1 ) ;
    }

    bool checkPostTree(vector<int> sequence, int left , int right){
        if(left>=right)
            return true;

        int root = sequence[right];
        
        int j = right - 1;
        while( j>=0 && sequence[j]>root){
            j--;
        }
        
        int i = left;
        while( i <=j){
            if( sequence[i++] > root){
                return false;
            }
        }
        return checkPostTree(sequence, left , j) && checkPostTree(sequence, j+1 , right);

    }
};
```

> 非递归解法

```
class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.size() == 0){
            return false; 
        }
        vector<int> inorder(sequence);
        sort(inorder.begin(), inorder.end());
        return IsPopOrder(inorder, sequence);
    }

    bool IsPopOrder(vector<int> pushV, vector<int> popV)
    {
        int n = pushV.size();
        stack<int> s;
        int i=0, j=0;
        while(i < n)
        {
            s.push(pushV[i]);
            while(!s.empty() && s.top() == popV[j])
            {
                j ++;
                s.pop();
            }
            i ++;
        }
        return j == n;
    }
};
```

## 8. 二叉树中和为某一值的路径

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
    vector<vector<int> > result;
    
    vector<vector<int>> FindPath(TreeNode* root,int expectSum) {
        if(!root)
        {
            return result;
        }
        vector<int> path;
        int currentSum = 0;
        FindPath(root, expectSum, path, currentSum);
        return result;
    }
    
    void FindPath(TreeNode *root, int expectSum, vector<int> path, int currentSum)
    {
        currentSum += root->val;
        path.push_back(root->val);
        
        bool isLeaf = (!root->left && !root->right);
        if(currentSum == expectSum && isLeaf)
        {
            result.push_back(path);
        }
        
        if(root->left)
        {
            FindPath(root->left, expectSum, path, currentSum);
        }
        if(root->right)
        {
            FindPath(root->right, expectSum, path, currentSum);
        }
        path.pop_back();
    }
};
```

## 9.复杂链表的复制

```
/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead) {
        if (pHead == nullptr) {
            return nullptr;
        }
        RandomListNode* pCur = pHead;
        while(pCur != nullptr) {
            RandomListNode* node = new RandomListNode(pCur->label); 
            node->next = pCur->next;
            pCur->next = node; 
            pCur = pCur->next->next;
        }
        
        pCur = pHead;
        while (pCur != nullptr) {
            if (pCur->random != nullptr) {
                pCur->next->random = pCur->random->next;
            }
            pCur = pCur->next->next;
        }
        
        RandomListNode* head = pHead->next;
        RandomListNode *pCurN = head;
        pCur = pHead;
        while (pCur != nullptr) {
            pCur->next = pCurN->next;
            pCur = pCur->next;
            
            if (pCur == nullptr) {
                pCurN->next = pCur;
            } else {
                pCurN->next = pCur->next;
                pCurN = pCurN->next;
            }
        }
        
        return head;
    }
};
```

> 借助 map

```
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead) {
        if(!pHead) return nullptr;
        RandomListNode *cur = pHead;
        unordered_map<RandomListNode *, RandomListNode *> map;
        while(cur)
        {
            map[cur] = new RandomListNode(cur->label);
            cur = cur->next;
        }
        cur = pHead;
        while(cur)
        {
            map[cur]->next = map[cur->next];
            map[cur]->random = map[cur->random];
            cur = cur->next;
        }
        return map[pHead];
    }
};
```

## 10. 二叉搜索树与双向链表

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
    TreeNode* Convert(TreeNode* pRootOfTree) {
        if (pRootOfTree == nullptr)
            return pRootOfTree;

        stack<TreeNode*> ista;
        vector<TreeNode*> ivec;
        auto pin = pRootOfTree;
        while (!(ista.empty() && pin == nullptr)){
            while(pin != nullptr){
                ista.push(pin);
                pin = pin->left;
            }            
            if (!ista.empty())
            {
                pin = ista.top();
                ista.pop();
                ivec.push_back(pin);
                pin = pin->right;
            }
        }        

        ivec.front()->left = nullptr;
        ivec.back()->right = nullptr;
        int length = ivec.size();
        for (int i = 0; i != length-1; ++i){
            ivec[i]->right = ivec[i+1];
            ivec[i+1]->left = ivec[i];
        }
        return ivec.front();
    }
};
```

## 11. 序列化二叉树

```

```