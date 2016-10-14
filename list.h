#ifndef LIST_H
#define LIST_H

#define NULLNODE (ListNode *)NULL

struct _ListNode;

typedef struct _ListNode
{
	void *value;
   struct _ListNode *prev;
	struct _ListNode *next;
}ListNode;

struct _LinkedList;

typedef struct _LinkedList
{
   ListNode *head;
   ListNode *tail;
   int element_size;
   int num_elements;
}LinkedList;

// ListNode
ListNode* new_node(void *value, ListNode *prevNode, ListNode *nextNode, int dataSize);
void set_value(ListNode *node, void *newValue, int dataSize);
void set_prev(ListNode *node, ListNode *prevNode);
void set_next(ListNode *node, ListNode *nextNode);

// Linked List
LinkedList *new_list(int element_size);
void list_add(LinkedList *list, void *element);
void *list_get(LinkedList *list, int index);
#endif // LIST_H