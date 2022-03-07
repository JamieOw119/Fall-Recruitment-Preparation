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

> 先序遍历

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
    const char SEP = '&';
    const char NULL_NODE = '#';
    char* Serialize(TreeNode *root) {    
        if(!root){
            return nullptr;
        }
        stack<TreeNode*> nodes;
        TreeNode* cur = root;
        string s;
        
        while(cur || !nodes.empty()){
            while(cur){
                s.append(to_string(cur->val));
                s.push_back(SEP);
                nodes.push(cur);
                cur = cur->left;
            }
            s.push_back(NULL_NODE);
            s.push_back(SEP);
            cur = nodes.top();
            nodes.pop();
            cur = cur->right;
        }
        s.push_back(NULL_NODE);
        s.push_back(SEP);
        char* ret = new char[s.length() + 1];
        strcpy(ret, s.c_str());
        return ret;
        
    }
    
    TreeNode* Deserialize(char *str) {
        if(!str){
            return nullptr;
        }
        string s(str);
        TreeNode* root = new TreeNode(atoi(s.c_str()));
        s = s.substr(s.find_first_of(SEP) + 1);
        TreeNode* cur = root;
        stack<TreeNode*> nodes;
        while(!s.empty() && (cur || !nodes.empty())){
            while(cur){
                nodes.push(cur);
                if(s[0] == NULL_NODE){
                    cur->left = nullptr;
                }else{
                    cur->left = new TreeNode(atoi(s.c_str()));
                }
                s = s.substr(s.find_first_of(SEP)+1);
                cur = cur->left;
            }
            cur = nodes.top();
            nodes.pop();
            if(s[0] == NULL_NODE){
                cur->right = nullptr;
            }else{
                cur->right = new TreeNode(atoi(s.c_str()));
            }
            s = s.substr(s.find_first_of(SEP)+1);
            cur = cur->right;
        }
        return root;
    }
};
```

> 层次遍历

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
    const char SEP = '&';
    const char NULL_NODE = '#';
    
    char* Serialize(TreeNode *root) {    
        if(!root)
        {
            return nullptr;
        }
        queue<TreeNode *> nodes;
        nodes.push(root);
        string serialized_str;
        while(!nodes.empty())
        {
            TreeNode *head = nodes.front();
            nodes.pop();
            if(head)
            {
                serialized_str.append(to_string(head->val));
                nodes.push(head->left);
                nodes.push(head->right);
            }
            else
            {
                serialized_str.push_back(NULL_NODE);
            }
            serialized_str.push_back(SEP);
        }
        char* ret = new char[serialized_str.length() + 1];
        strcpy(ret, serialized_str.c_str());
        return ret;
    }
    
    TreeNode* Deserialize(char *str) {
        if(!str)
        {
            return nullptr;
        }
        string s(str);
        if(s[0] == NULL_NODE)
        {
            return nullptr;
        }
        queue<TreeNode*> nodes;
        TreeNode* root = new TreeNode(atoi(s.c_str()));
        nodes.push(root);
        s = s.substr(s.find_first_of(SEP)+1); 
        
        while(!nodes.empty() && !s.empty()){
            TreeNode* head = nodes.front();
            nodes.pop();
            if(s[0] == NULL_NODE){
                head->left == nullptr;
            }else{
                head->left = new TreeNode(atoi(s.c_str()));
                nodes.push(head->left);
            }
            s = s.substr(s.find_first_of(SEP) + 1);
             
            if(s[0] == NULL_NODE){
                head->right = nullptr;
            }else{
                head->right = new TreeNode(atoi(s.c_str()));
                nodes.push(head->right);
            }
            s = s.substr(s.find_first_of(SEP) + 1);
        }
        return root;
    }
};
```

## 12. 字符串的排列

> 基于 demo 的方法

```
class Solution {
public:
    vector<string> res;
    vector<string> Permutation(string str) 
    {
        if(str.empty())
        {
            return res;
        }
        vector<bool> state(str.size(), false);
        backtracking(str, "", state);
        return res;
    }
    
    void backtracking(string s, string cur, vector<bool> &state)
    {
        if(cur.size() == s.size())
        {
            res.push_back(cur);
            return;
        }
        for(int i=0; i < s.size(); i ++)
        {
            if(state[i] || (i > 0 && s[i] == s[i-1] && state[i - 1]))
            {
                continue;
            }
            state[i] = true;
            cur += s[i];
            backtracking(s, cur, state);
            state[i] = false;
            cur = cur.substr(0, cur.length()-1);
        }
    }
};
```

> 基于 swap 的方法

```
class Solution
{
    vector<vector<int> > result;

    void PermutationCore(vector<int> numbers, int position = 0, int len = 8)
    {
        if(position == len - 1 && checking(numbers))
        {
            result.push_back(numbers);
        }
        
        for(int i=position; i<len; i++)
        {
            swap(numbers[position], numbers[i]);
            PermutationCore(numbers, position + 1);
            swap(numbers[position], numbers[i]);
        }
    }

    vector<vector<int> > PermutationCore(vector<int> numbers)
    {
        if(numbers.empty())
        {
            return result;
        }
        return PermutationCore(numbers, 0, numbers.size());
    }
};

```

> 相关题目1: 字符串的组合

```
class Solution
{
    vector<vector<char> > Combine(string s)
    {
        vector<vector<char> > result;
        if(s.size() == 0)
        {
            return res;
        }

        for(int index=0; index<(1<<s.size()); index++)
        {
            vector<char> res;
            for(int i=0; i<s.size(); i++)
            {
                if(index & (1 << i))
                {
                    res.push_back(s[i]);
                }
            }
            if(!res.empty())
            {
                result.push_back(res);
            }
        }
        return result;
    }
};
```

> 相关题目2：正方体 8 个顶点上放 8 个数字，使得正方体上三组相对的面上的 4 个顶点的和相等

```
class Solution
{
    bool checking(vector<int> data)
    {
        bool ok = false;
        if (data[0] + data[1] + data[2] + data[3] == data[4] + data[5] + data[6] + data[7] &&
            data[0] + data[2] + data[4] + data[6] == data[1] + data[3] + data[5] + data[7] &&
            data[0] + data[1] + data[4] + data[5] == data[2] + data[3] + data[6] + data[7])
            ok = true;
        return ok;
    }

    // 以下参照全排列的方法，将 8 个顶点的数字的每个全排列都交给 checking 函数判断，符合条件的可以放入返回集合中。
};
```

> 相关题目3：N 皇后问题

```
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        auto solutions = vector<vector<string>>();
        auto queens = vector<int>(n, -1);
        solve(solutions, queens, n, 0, 0, 0, 0);
        return solutions;
    }

    void solve(vector<vector<string>> &solutions, vector<int> &queens, int n, int row, int columns, int diagonals1, int diagonals2) {
        if (row == n) {
            auto board = generateBoard(queens, n);
            solutions.push_back(board);
        } else {
            int availablePositions = ((1 << n) - 1) & (~(columns | diagonals1 | diagonals2));
            while (availablePositions != 0) {
                int position = availablePositions & (-availablePositions);
                availablePositions = availablePositions & (availablePositions - 1);
                int column = __builtin_ctz(position);
                queens[row] = column;
                solve(solutions, queens, n, row + 1, columns | position, (diagonals1 | position) >> 1, (diagonals2 | position) << 1);
                queens[row] = -1;
            }
        }
    }

    vector<string> generateBoard(vector<int> &queens, int n) {
        auto board = vector<string>();
        for (int i = 0; i < n; i++) {
            string row = string(n, '.');
            row[queens[i]] = 'Q';
            board.push_back(row);
        }
        return board;
    }
};
```

> p.s.1 x & (−x) 可以获得 x 的二进制表示中的最低位的 1 的位置

> p.s.2 x & (x−1) 可以将 x 的二进制表示中的最低位的 1 置成 0

> p.s.3 __builtin_ctz x末尾0的个数。x=0时结果未定义