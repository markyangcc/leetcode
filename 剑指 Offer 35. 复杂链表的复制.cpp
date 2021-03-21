/*
请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，每个节点除了有一个
next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

主要是Random指针的 Deep Copy

输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]

*/


// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
//-----------------------------------------------------------------
class Solution {
public:
  Node *copyRandomList(Node *head) {
    if (head == NULL)
      return head;

    Node *curhead = head; // bakeup

    //就地复制
    while (curhead != NULL) {
      Node *copyNode = new Node(curhead->val);
      copyNode->next = curhead->next;
      curhead->next = copyNode;

      curhead = curhead->next->next;
    }

    // 统一处理random pointer
    curhead = head; // reset head
    while (curhead != NULL) {
      if (curhead->random != NULL)
        curhead->next->random = curhead->random->next;

      curhead = curhead->next->next;
    }

    //分离链表
    curhead = head;             // reset head
    Node *newhead = head->next; // backup
    Node *copyhead = head->next;

    while (curhead != NULL) {
      //原链
      curhead->next = curhead->next->next;
      curhead = curhead->next;

      //新链
      if (copyhead->next != NULL) {
        copyhead->next = copyhead->next->next;
        copyhead = copyhead->next;
      }
    }

    return newhead;
  }
};