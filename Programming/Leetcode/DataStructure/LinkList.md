# Data Structure

## 链表

### Kind 1: 两个链表操作

#### 2. 两数相加

```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        ListNode *head = new ListNode(-1);
        ListNode *p = head;
        int sum = 0;
        bool carry = false;

        while(l1 || l2)
        {
            sum = 0;
            if(l1)
            {
                sum += l1->val;
                l1 = l1->next;
            }
            if(l2)
            {
                sum += l2->val;
                l2 = l2->next;
            }
            if(carry)
            {
                sum ++;
            }
            p->next = new ListNode(sum % 10);
            p = p->next;
            carry = sum / 10? true: false;
        }
        
        if(carry)
        {
            p->next = new ListNode(1);
        }
        return head->next;
    }
};
```