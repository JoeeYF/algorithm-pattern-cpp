# 链表

## 基本技能

链表相关的核心点

- null/nil 异常处理
- dummy node 哑巴节点
- 快慢指针
- 插入一个节点到排序链表
- 从一个链表中移除一个节点
- 翻转链表
- 合并两个链表
- 找到链表的中间节点

## 常见题型

### [remove-duplicates-from-sorted-list](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)

> 给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次。

```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode *cur = head;
        while(cur!=NULL&&cur->next!=NULL)
        {
            if(cur->val==cur->next->val)
            cur->next = cur->next->next;
            else
            cur = cur->next;
        }
        return head;
    }
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head==NULL||head->next==NULL) return head;
        head->next = deleteDuplicates(head->next);
        return head->val==head->next->val? head->next:head;
    }
};

```

### [remove-duplicates-from-sorted-list-ii](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)

> 给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中   没有重复出现的数字。

思路：链表头结点可能被删除，所以用 dummy node 辅助删除

```c++
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head == NULL || head->next == NULL) return head;

        ListNode *dump = new ListNode(-1);
        dump->next = head;
        head = dump;

        int temp;
        while(head->next!=NULL&&head->next->next!=NULL)
        {
            if(head->next->val==head->next->next->val)
            {
                temp = head->next->val;
                while(head->next!=NULL&&head->next->val==temp)
                head->next = head->next->next;
            }
            else
            head = head->next;
        }
        return dump->next;
    }
};
```

注意点
• A->B->C 删除 B，A.next = C
• 删除用一个 Dummy Node 节点辅助（允许头节点可变）
• 访问 X.next 、X.value 一定要保证 X != nil

### [reverse-linked-list](https://leetcode-cn.com/problems/reverse-linked-list/)

> 反转一个单链表。

思路：用一个 prev 节点保存向前指针，temp 保存向后的临时指针

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *prev = NULL;
        while (head!=NULL)
        {
            ListNode *temp = head->next;
            head->next=prev;
            prev = head;
            head = temp;
        }
        return prev;

    }
};
```

### [reverse-linked-list-ii](https://leetcode-cn.com/problems/reverse-linked-list-ii/)

> 反转从位置  *m*  到  *n*  的链表。请使用一趟扫描完成反转。

思路：先遍历到 m 处，翻转，再拼接后续，注意指针处理

```c++
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *dummy = new ListNode(-1);
        ListNode *pre = dummy;
        dummy->next =head;

        for(int i=0;i<m-1;i++){
            pre = pre->next;
        }

        ListNode *cur = pre->next;
        for (int i=m;i<n;i++)
        {
            ListNode *temp=cur->next;
            cur->next=temp->next;
            temp->next=pre->next;
            pre->next=temp;
        }
        return dummy->next;
    }
};
```

### [merge-two-sorted-lists](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

> 将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

思路：通过 dummy node 链表，连接各个元素

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode newHead(0);
        ListNode *pi = &newHead;
        while(l1&&l2){
            if(l1->val<l2->val){
                pi->next=l1;
                l1=l1->next;
            }
            else{
                pi->next=l2;
                l2=l2->next;
            }
            pi = pi->next;
        }
        while(l1){
            pi->next=l1;
            l1=l1->next;
            pi=pi->next;
        }
        while(l2){
            pi->next=l2;
            l2=l2->next;
            pi=pi->next;
        }
        return newHead.next;
    }
};
//递归
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1==nullptr) return l2;
        if(l2==nullptr) return l1;

        if(l1->val < l2->val){
            l1->next=mergeTwoLists(l1->next,l2);
            return l1;
        }else{
            l2->next=mergeTwoLists(l1,l2->next);
            return l2;
        }
        }
};
```

### [partition-list](https://leetcode-cn.com/problems/partition-list/)

> 给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于  *x*  的节点都在大于或等于  *x*  的节点之前。

思路：将大于 x 的节点，放到另外一个链表，最后连接这两个链表

```c++
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        if (!head) return head;
        ListNode *dummy1 = new ListNode(-1);
        ListNode* pt1 = dummy1;
        ListNode *dummy2 = new ListNode(-1);
        ListNode* pt2 = dummy2;
        while(head){
            if(head->val<x){
                pt1->next = head;
                pt1=pt1->next;
            }else{
                pt2->next = head;
                pt2=pt2->next;
            }
            head=head->next;
        }
        pt2->next=NULL;
        pt1->next = dummy2->next;
        return dummy1->next;
    }
};
```

哑巴节点使用场景

> 当头节点不确定的时候，使用哑巴节点

### [sort-list](https://leetcode-cn.com/problems/sort-list/)

> 在  *O*(*n* log *n*) 时间复杂度和常数级空间复杂度下，对链表进行排序。

思路：归并排序，找中点和合并操作

```c++
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(head==NULL||head->next==NULL) return head;
        ListNode *slow=head;
        ListNode *fast=head->next;

        while(fast!=NULL&&fast->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
        }
        ListNode *middle = slow->next;
        slow->next=NULL;
        ListNode *right = sortList(head);
        ListNode *left = sortList(middle);
        return mergeSortList(left,right);
    }
    ListNode *mergeSortList(ListNode *left, ListNode *right){
        ListNode *dummy=new ListNode(-1);
        ListNode *cur =dummy;

        while(left!=NULL && right!=NULL){
            if(left->val<right->val){
                cur->next=left;
                left=left->next;
            }else{
                cur->next=right;
                right=right->next;
            }
            cur = cur->next;
        }

        while(left!=nullptr){
            cur->next=left;
            left=left->next;
            cur = cur->next;
        }
        while(right!=nullptr){
            cur->next=right;
            right=right->next;
            cur = cur->next;
        }
        return dummy->next;
    }

};
```

注意点

- 快慢指针 判断 fast 及 fast.Next 是否为 nil 值
- 递归 mergeSort 需要断开中间节点
- 递归返回条件为 head 为 nil 或者 head.Next 为 nil

### [reorder-list](https://leetcode-cn.com/problems/reorder-list/)

> 给定一个单链表  *L*：*L*→*L*→…→*L\_\_n*→*L*
> 将其重新排列后变为： *L*→*L\_\_n*→*L*→*L\_\_n*→*L*→*L\_\_n*→…

思路：找到中点断开，翻转后面部分，然后合并前后两个链表

```c++
class Solution {
public:
    void reorderList(ListNode* head) {
        if(head==NULL) return;
        ListNode *middle = findMiddle(head);
        ListNode *right = reverseList(middle->next);
        middle->next=NULL;

        ListNode *dummy = new ListNode(-1);
        ListNode *cur = dummy;
        bool flag = true;
        while(head!=NULL && right!=NULL){
            if (flag){
                cur->next = head;
                head=head->next;
                cur = cur->next;
            }else{
                cur->next = right;
                right=right->next;
                cur = cur->next;
            }
            flag=!flag;
        }
        if(head!=NULL) cur->next=head;
        if(right!=NULL) cur->next=right;
        head= dummy->next;

    }

    ListNode  *findMiddle(ListNode* head){
        ListNode *slow=head;
        ListNode *fast = head->next;
        while(fast!=NULL&&fast->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
        }
        return slow;
    }

    ListNode  *reverseList(ListNode* head){
        ListNode *pre=nullptr;
        ListNode *cur=head;
        while(cur!=NULL){
            ListNode *temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;

    }
};

// 另一个方法
class Solution {
public:
    void reorderList(ListNode* head) {
        if(head==NULL) return;
        vector<ListNode*> vec;
        ListNode* cur=head;
        while(cur){
            vec.push_back(cur);
            cur=cur->next;
        }
        int left=0;
        int right = vec.size()-1;
        while(left<right){
            vec[left]->next = vec[right];
            left++;
            vec[right]->next = vec[left];
            right--;
        }
        vec[left]->next=NULL;   

    }
```

### [linked-list-cycle](https://leetcode-cn.com/problems/linked-list-cycle/)

> 给定一个链表，判断链表中是否有环。

思路：快慢指针，快慢指针相同则有环，证明：如果有环每走一步快慢指针距离会减 1
![fast_slow_linked_list](https://img.fuiboom.com/img/fast_slow_linked_list.png)

```c++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head==NULL) return false;
        ListNode *slow=head;
        ListNode *fast=head->next;
        while(fast!=NULL&&fast->next!=NULL){
            if(slow==fast) return true;
            slow=slow->next;
            fast=fast->next->next;
        } 
        return false;
        
    }
};
```

### [linked-list-cycle-ii](https://leetcode-cn.com/problems/linked-list-cycle-ii/)

> 给定一个链表，返回链表开始入环的第一个节点。  如果链表无环，则返回  `null`。

思路：快慢指针，快慢相遇之后，慢指针回到头，快慢指针步调一致一起移动，相遇点即为入环点
![cycled_linked_list](https://img.fuiboom.com/img/cycled_linked_list.png)

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head==NULL)return NULL;
        ListNode *slow=head;
        ListNode *fast=head->next;
        while(fast!=NULL&&fast->next!=NULL){
            if(fast==slow){
                slow=head;
                fast=fast->next;
                while(fast!=slow){
                    slow=slow->next;
                    fast=fast->next;
                }
                return slow;
            }
            fast=fast->next->next;
            slow=slow->next;
        }
        return NULL;
    }
};
```

坑点

- 指针比较时直接比较对象，不要用值比较，链表中有可能存在重复值情况
- 第一次相交后，快指针需要从下一个节点开始和头指针一起匀速移动

另外一种方式是 fast=head,slow=head

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(head==NULL)return NULL;
        ListNode *slow=head;
        ListNode *fast=head;
        while(fast!=NULL&&fast->next!=NULL){
            if(fast==slow){
                slow=head;
                while(fast!=slow){
                    slow=slow->next;
                    fast=fast->next;
                }
                return slow;
            }
            fast=fast->next->next;
            slow=slow->next;
        }
        return NULL;
    }
};
```

这两种方式不同点在于，**一般用 fast=head.Next 较多**，因为这样可以知道中点的上一个节点，可以用来删除等操作。
- fast 如果初始化为 head.Next 则中点在 slow.Next
- fast 初始化为 head,则中点在 slow

### [palindrome-linked-list](https://leetcode-cn.com/problems/palindrome-linked-list/)

> 请判断一个链表是否为回文链表。

- 先找中间点，再反转，再比较，时间复杂度O(n)，空间复杂度O(1)。
```c++
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head==NULL) return true;
        ListNode *slow = head;
        ListNode *fast = head->next;
        while(fast!=NULL&&fast->next!=NULL){
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode *middle = slow->next;
        slow ->next = NULL;

        ListNode *prev = NULL;
        while(middle!=NULL){
            ListNode *temp = middle->next;
            middle->next=prev;
            prev=middle;
            middle=temp;
        }

        while(head!=NULL&&prev!=NULL){
            if(head->val!=prev->val)return false;
            head=head->next;
            prev=prev->next;
        }
        return true;

    }
};
//另一种
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head==NULL) return true;
        ListNode *prev = NULL;
        ListNode *cur = head;
        ListNode *fast = head;
        while(fast!=NULL&&fast->next!=NULL){
            fast = fast->next->next;
            ListNode *temp = cur->next;
            cur->next=prev;
            prev=cur;
            cur=temp;
        }
        if(fast!=NULL) cur = cur->next;
        while(prev!=NULL&&cur!=NULL){
            if(prev->val!=cur->val)return false;
            prev=prev->next;
            cur=cur->next;
        }
        return true;

    }
};
```
- 将其转为数组，时间复杂度O(n)，空间复杂度O(n)。
```c++
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head==NULL) return true;
        vector<ListNode*> vec;
        ListNode* cur=head;
        while(cur){
            vec.push_back(cur);
            cur=cur->next;
        }
        int left=0;
        int right = vec.size()-1;
        while(left<right){
            if (vec[left++]->val!=vec[right--]->val) return false;
        }
        return true;
    }
};
```

### [copy-list-with-random-pointer](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)

> 给定一个链表，每个节点包含一个额外增加的随机指针，该指针可以指向链表中的任何节点或空节点。
> 要求返回这个链表的 深拷贝。

思路：1、hash 表存储指针，2、复制节点跟在原节点后面

```c++
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head==NULL) return NULL;
        Node *cur=head;
        while(cur){
            Node *clone = new Node(cur->val,cur->next,NULL);
            Node *tmp = cur->next;
            cur->next=clone;
            cur=tmp;
        }
        cur = head;
        while(cur){
            if(cur->random) cur->next->random = cur->random->next;
            cur = cur->next->next;
        }
        cur = head;
        Node* ret = head->next;
        while(cur!=NULL&&cur->next!=NULL){
            Node *tmp = cur->next;
            cur->next = cur->next->next;
            cur=tmp;
        }
        return ret;
    }
};
```

## 总结

链表必须要掌握的一些点，通过下面练习题，基本大部分的链表类的题目都是手到擒来~

- null/nil 异常处理
- dummy node 哑巴节点
- 快慢指针
- 插入一个节点到排序链表
- 从一个链表中移除一个节点
- 翻转链表
- 合并两个链表
- 找到链表的中间节点

## 练习

- [ ] [remove-duplicates-from-sorted-list](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list/)
- [ ] [remove-duplicates-from-sorted-list-ii](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-list-ii/)
- [ ] [reverse-linked-list](https://leetcode-cn.com/problems/reverse-linked-list/)
- [ ] [reverse-linked-list-ii](https://leetcode-cn.com/problems/reverse-linked-list-ii/)
- [ ] [merge-two-sorted-lists](https://leetcode-cn.com/problems/merge-two-sorted-lists/)
- [ ] [partition-list](https://leetcode-cn.com/problems/partition-list/)
- [ ] [sort-list](https://leetcode-cn.com/problems/sort-list/)
- [ ] [reorder-list](https://leetcode-cn.com/problems/reorder-list/)
- [ ] [linked-list-cycle](https://leetcode-cn.com/problems/linked-list-cycle/)
- [ ] [linked-list-cycle-ii](https://leetcode-cn.com/problems/linked-list-cycle-ii/)
- [ ] [palindrome-linked-list](https://leetcode-cn.com/problems/palindrome-linked-list/)
- [ ] [copy-list-with-random-pointer](https://leetcode-cn.com/problems/copy-list-with-random-pointer/)
