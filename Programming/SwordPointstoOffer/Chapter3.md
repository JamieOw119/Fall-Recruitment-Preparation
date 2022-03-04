# 第三章： 高质量的代码

## 1. 数值的整数次方

```
class Solution {
public:
    double Power(double base, int exponent) {
        if(base==0)
        {
            return 0;
        }
        if(exponent == 0)
        {
            return 1;
        }
        
        bool flag = false;
        if(exponent < 0)
        {
            exponent = -exponent;
            flag = true;
        }
        
        double ret = 1;
        while(exponent)
        {
            if(exponent & 1)
            {
                ret *= base;
            }
            base *= base;
            exponent >>= 1;
        }
        
        if(flag)
        {
            ret = 1 / ret;
        }
        return ret;
    }
};
```

## 2. 打印从 1 到最大的 n 位数

> 普通做法

```
class Solution {
public:
    vector<int> printNumbers(int n) {
        vector<int> ret;
        int maxn = pow(10, n) - 1;
        for(int i=1; i<= maxn; i++)
        {
            ret.push_back(i);
        }
        return ret;
    }
};
```

> 完善做法

```
void Print1ToMaxOfNDigits(int n)
{
    if (n <= 0)
        return;

    char* number = new char[n + 1];
    number[n] = '\0';

    for (int i = 0; i < 10; ++i)
    {
        number[0] = i + '0';
        Print1ToMaxOfNDigitsRecursively(number, n, 0);
    }

    delete[] number;
}

void Print1ToMaxOfNDigitsRecursively(char* number, int length, int index)
{
    if (index == length - 1)
    {
        PrintNumber(number);
        return;
    }

    for (int i = 0; i < 10; ++i)
    {
        number[index + 1] = i + '0';
        Print1ToMaxOfNDigitsRecursively(number, length, index + 1);
    }
}

void PrintNumber(char* number)
{
    bool isBeginning0 = true;
    int nLength = strlen(number);

    for (int i = 0; i < nLength; ++i)
    {
        if (isBeginning0 && number[i] != '0')
            isBeginning0 = false;

        if (!isBeginning0)
        {
            printf("%c", number[i]);
        }
    }

    printf("\t");
}
```

## 3. 删除链表的重复节点

```
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(head == nullptr)
        {
            return head;
        }
        if(head->next == nullptr)
        {
            if(head->val == val)
            {
                return nullptr;
            }
            else
            {
                return head;
            }
        }
        if(head->val == val)
        {
            return head->next;
        }
        
        ListNode *pre = head;
        ListNode *cur = head->next;
        while(cur->val != val)
        {
            pre = pre->next;
            cur = cur->next;
        }
        if(cur->val == val)
        {
            pre->next = cur->next;
            delete cur;
        }
        return head;
    }
};
```

> 相关题目 1： 删除有序链表的重复节点

```
class Solution {
public:
    ListNode *deleteDuplicates(ListNode *head) {
        if(head == nullptr||head->next == nullptr)
        {
            return head;
        }
        
        ListNode *cur = head;
        while(cur != NULL){
            while(cur->next != NULL && cur->val == cur->next->val){
                ListNode *tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }
            cur = cur->next;
        }
        return head;
    }
};
```

> 相关题目 2： 删除无序链表的重复节点
> 
> Solution 1：使用 set，时间复杂度 O(nlogn) 空间复杂度 o(n)
> 
> Solution 2：重建链表，时间复杂度 O(n^2）空间复杂度 o(n)

## 4. 正则表达式匹配

```
class Solution {
public:
    bool match(string str, string pattern) 
    {
        if(pattern.empty() || str.empty())
        {
            return false;
        }
        
        char *str_char = new char[str.size() + 1];
        char *pattern_char = new char[pattern.size()];
        strcpy(str_char, str.data());
        strcpy(pattern_char, pattern.data());
        str_char[str.size()] = '\0';
        pattern_char[pattern.size()] = '\0';
        
        return matchCore(str_char, pattern_char);
    }
    
    bool matchCore(char *str, char *pattern)
    {
        if(*str == '\0' && *pattern == '\0')
        {
            return true;
        }
        if(*str != '\0' && *pattern == '\0')
        {
            return false;
        }
        if(*(pattern+1) == '*')
        {
            if(*pattern == *str || (*pattern == '.' && *str != '\0'))
            {
                return matchCore(str+1, pattern+2) || matchCore(str+1, pattern) || matchCore(str, pattern+2);
            }
            else
            {
                return matchCore(str, pattern+2);
            }
            
        }
        if(*str==*pattern||(*pattern=='.' && *str != '\0'))
        {
            return matchCore(str+1, pattern+1);
        }
        
        return false;
    }
};
```

## 5. 表示数值的字符串

```
class Solution {
public:
    int i = 0; 
   
    bool scanIntger(string str){
        if(str[i]=='+' || str[i]=='-'){
            i++;
        }
        return scanfUnsignIntger(str);
    }
   
    bool scanfUnsignIntger(string str){
        int k = i;
        while('0'<=str[i] && str[i]<='9'){
            i++;
        }
        return i>k;
    }
     
    bool isNumeric(string str) {
        while(str[i]==' ') i++;
        bool ans = scanIntger(str);
 
        if(i<str.size() && str[i]=='.'){
            i++;
            ans = scanfUnsignIntger(str) || ans;
        }
         
        if(i<str.size() && (str[i]=='E'|| str[i]=='e')){
            i++;
            ans = scanIntger(str) && ans;
        }
        while(str[i]==' ') i++;
         
        if(ans==true && i==str.size()){
            return true;
        }else{
            return false;
        }
    }
};
```

## 6. 调整数组顺序使奇数位于偶数前面

```
class Solution {
public:
    vector<int> reOrderArray(vector<int>& array) {
        int count=0;
        for(int i =0;i<array.size();i++)
        {
            if(array[i]&0x01)
                count++;
        }
        vector<int> retans(array.size());
        int odd=0,even=count;
        for(int i =0;i<array.size();i++)
        {
            if(array[i]&0x01)
                retans[odd++]=array[i];
            else
                retans[even++]=array[i];
        }
        return retans;
    }
};
```

> 不使用额外空间

```
class Solution {
public:
    vector<int> reOrderArray(vector<int>& array) {
        int firstEven = 0;
        for(int i=0; i<array.size(); i++)
        {
            if(array.at(i) & 0x01 && i == firstEven)
            {
                firstEven++;
            }
            else if(array.at(i) & 0x01){
                int temp = array.at(i);
                int pre = array.at(firstEven);
                for(int j = firstEven + 1;j < i + 1;j++){
                    int tmp = array.at(j);
                    array.at(j) = pre;
                    pre = tmp;
                }
                array.at(firstEven) = temp;
                firstEven++;
            }
        }
        return array;
    }
};
```

## 7. 打印链表的倒数第 k 个节点

```
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pHead, int k) {
        // write code here
        if(pHead == nullptr)
        {
            return nullptr;
        }
        ListNode *fast = pHead;
        ListNode *slow = pHead;
        while(k-- != 1)
        {
            if(!fast->next)
            {
                return nullptr;
            }
            fast = fast->next;
        }
        while(fast->next)
        {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
```

## 8. 链表中环的入口节点

```
/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        ListNode* meetingNode = MeetingNode(pHead);
        if(meetingNode == nullptr)
            return nullptr;

        int nodesInLoop = 1;
        ListNode* pNode1 = meetingNode;
        while(pNode1->next != meetingNode)
        {
            pNode1 = pNode1->next;
            ++nodesInLoop;
        }

        pNode1 = pHead;
        for(int i = 0; i < nodesInLoop; ++i)
            pNode1 = pNode1->next;

        ListNode* pNode2 = pHead;
        while(pNode1 != pNode2)
        {
            pNode1 = pNode1->next;
            pNode2 = pNode2->next;
        }

        return pNode1;
    }
    
    ListNode* MeetingNode(ListNode* pHead)
    {
        if(pHead == nullptr)
            return nullptr;

        ListNode* pSlow = pHead->next;
        if(pSlow == nullptr)
            return nullptr;

        ListNode* pFast = pSlow->next;
        while(pFast != nullptr && pSlow != nullptr)
        {
            if(pFast == pSlow)
                return pFast;

            pSlow = pSlow->next;

            pFast = pFast->next;
            if(pFast != nullptr)
                pFast = pFast->next;
        }

        return nullptr;
    }
};
```

## 9. 反转链表

```
class Solution {
public:
    ListNode* ReverseList(ListNode* pHead) {
        if(pHead == nullptr)
        {
            return nullptr;
        }
        
        ListNode *cur = pHead;
        ListNode *nxt = nullptr;
        ListNode *pre = nullptr;
        ListNode *newHead = nullptr;
        
        while(cur)
        {
            nxt = cur->next;
            if(nxt == nullptr)
            {
                newHead = cur;
            }
            cur->next = pre;
            pre = cur;
            cur = nxt;
        }
        return newHead;
    }
};
```

> 递归实现反转链表

```
class Solution {
public:
    ListNode *ReverseList(ListNode *pHead)
    {
        if(pHead == nullptr || pHead->next == nullptr)
        {
            return pHead;
        }
        
        ListNode *ans = ReverseList(pHead->next);
        pHead->next->next = pHead;
        pHead->next = nullptr;
        return ans;
    }
};
```

## 10. 合并两个有序链表

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
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        if(!pHead1)
        {
            return pHead2;
        }
        if(!pHead2)
        {
            return pHead1;
        }
        
        ListNode *pMergeHead = nullptr;
        
        if(pHead1->val < pHead2->val)
        {
            pMergeHead = pHead1;
            pMergeHead->next = Merge(pHead1->next, pHead2);
        }
        else
        {
            pMergeHead = pHead2;
            pMergeHead->next = Merge(pHead1, pHead2->next);
        }
        return pMergeHead;
    }
};
```

## 11. 树的子结构

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
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
        bool result = false;
        if(pRoot1 && pRoot2)
        {
            if(pRoot1->val == pRoot2->val)
                result = DoesTree1HaveTree2(pRoot1, pRoot2);
            if(!result)
                result = HasSubtree(pRoot1->left, pRoot2);
            if(!result)
                result = HasSubtree(pRoot1->right, pRoot2);
        }
        return result;
    }
    
    bool DoesTree1HaveTree2(TreeNode *tree1, TreeNode *tree2)
    {
        if(tree2 == nullptr)
        {
            return true;
        }
        if(tree1 == nullptr)
        {
            return false;
        }
        if(tree1->val != tree2->val)
        {
            return false;
        }
        bool leftResult = DoesTree1HaveTree2(tree1->left, tree2->left);
        bool rightResult = DoesTree1HaveTree2(tree1->right, tree2->right);
        return leftResult && rightResult;
    }
};
```