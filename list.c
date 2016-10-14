#include <stdlib.h>
#include <string.h>
#include "list.h"

ListNode *new_node(void *value, ListNode *prevNode, ListNode *nextNode, int dataSize)
{
	ListNode *tmp = malloc(sizeof(ListNode));
	set_value(tmp, value, dataSize);
	set_prev(tmp, prevNode);
	set_next(tmp, nextNode);
	return tmp;
}

void set_value(ListNode *node, void *newValue, int dataSize)
{
	if (node != NULLNODE)
	{
		node->value = malloc(dataSize);
		memcpy(node->value, newValue, dataSize);
		//node->value = newValue;
	}
}

void set_prev(ListNode *node, ListNode *prevNode)
{
	if (node != NULLNODE)
	{
		node->prev = prevNode;
	}
}

void set_next(ListNode *node, ListNode *nextNode)
{
	if (node != NULLNODE)
	{
		node->next = nextNode;
	}
}

LinkedList *new_list(int element_size)
{
	LinkedList *tmp = malloc(sizeof(LinkedList));
	ListNode *dummy = malloc(sizeof(ListNode));
	dummy->prev = dummy;
	dummy->next = dummy;
	tmp->head = dummy;
	tmp->tail = dummy;
	tmp->element_size = element_size;
	tmp->num_elements = 0;
	return tmp;
}

void list_add(LinkedList *list, void *element)
{
	ListNode *new = new_node(element, NULLNODE, NULLNODE, list->element_size);
	ListNode *tmp = list->head;

	while (tmp->next != list->head) {
		tmp = tmp->next;
	}

	new->next = tmp->next;
	new->prev = tmp;
	tmp->next->prev = new;
	tmp->next = new;

	list->num_elements++;
	list->tail = new;
}

void *list_get(LinkedList *list, int index)
{
	if (index >= list->num_elements) {
		return NULL;
	}

	ListNode *tmp = list->head;
	for (int x = 0; x < index + 1; x++) {
		tmp = tmp->next;
	}

	return tmp->value;
}