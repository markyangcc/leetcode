/*
输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。

例如，一个链表有 6 个节点，从头节点开始，它们的值依次是
1、2、3、4、5、6。这个链表的倒数第 3 个节点是值为 4 的节点。


示例：
给定一个链表: 1->2->3->4->5, 和 k = 2.
返回链表 4->5.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
 public:
  ListNode* getKthFromEnd(ListNode* head, int k) {
    ListNode* slow = head;
    ListNode* fast = head;

    int count = 0;
    while (fast != NULL) {
      // 使用变量count 和 k的大小比较可以省去一个循环，精巧
      if (count >= k) slow = slow->next;

      fast = fast->next;
      count++;
    }

    // for(int i= 0;i<count-k ;i++){
    //     slow = slow->next;
    // }

    return slow;
  }
};