/*
 * node.c
 *
 *	Description: This is the linked list API library which has the below listed
 *	APIs
 *	1.	create_node
 *	2.	insert_node_at_beginning
 *	3.	insert_node_at_end
 *	4.	length_of_list
 *	5. 	print_list
 *	6.	find_element_in_list
 *	7.	reverse_list
 *	8.	delete_node_in_list
 *	9.	delete_list
 *
 *   Created on: Jun 25, 2018
 *       Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 */

#include "node.h"

/*---------------------------------------------------------------------------*/
/**
 * @brief static function to create a new node and make node->data to data
 * node->next to NULL
 *
 * @param data new node data
 *
 * @return newly created node pointer
 */
static node_t * create_node(int32_t data)
{
	node_t * new_node = NULL;
	/* Create a new node */
	new_node = (node_t *)malloc(sizeof(node_t));
	if (NULL == new_node) {
		printf("Node creation failed\n");
		return new_node;
	}
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

/*---------------------------------------------------------------------------*/

void insert_node_at_beginning(node_t ** head, int32_t data)
{
	node_t * new_node = NULL;
	/* Create a new node */
	new_node = create_node(data);
	if(NULL == new_node) {
		printf("Insert at the beginning failed\n");
		return;
	}
	/* Make next of new node as head */
	new_node->next = * head;
	*head = new_node;
}

/*---------------------------------------------------------------------------*/

void insert_node_at_end(node_t **head, int32_t data)
{
	node_t * new_node = NULL;
	node_t * temp = NULL;

	temp = *head;
	/* Create a new node */
	new_node = create_node(data);
	if (NULL == new_node) 	{
		printf("Insert at the beginning failed\n");
		return;
	}
	/* This new node is going to be the last node, so make next of it as NULL */
	new_node->next = NULL;
	/* If the Linked List is empty, then make the new node as head */
	if (*head == NULL) 	{
		*head = new_node;
		return;
	}
	/* Else traverse till the last node */
	while (temp->next != NULL) {
		temp = temp->next;
	}
	/* Change the next of last node */
	temp->next = new_node;
}

/*---------------------------------------------------------------------------*/

uint32_t length_of_list(node_t * head)
{
	uint32_t length = 0;
	node_t * temp = NULL;

	temp = head;
	while(NULL != temp) {
		length ++;
		temp = temp->next;
	}
	return length;
}

/*---------------------------------------------------------------------------*/

void print_list(node_t * head)
{
	node_t * temp = head;
	if(NULL == temp) {
		printf("List is empty!!\n");
		return;
	} else {
		printf("List: ");
		while (temp != NULL) {
			printf("%d ", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}

/*---------------------------------------------------------------------------*/

uint32_t find_element_in_list(node_t * head, int32_t data)
{
	uint32_t count = 0;
	node_t * temp = NULL;
	uint8_t flag = 0;

	temp = head;
	if (NULL == temp) {
		printf("Empty list..!!");
		return count;
	}
	while (NULL != temp) {
		count ++;
		if(data == temp->data) {
			flag = 1;
			break;
		}
		temp = temp->next;
	}
	return ((flag == 1) ? count : 0);
}

/*---------------------------------------------------------------------------*/

void reverse_list(node_t ** head)
{
	node_t * prev = NULL;
	node_t * curr = NULL;
	node_t * next = NULL;

	curr = *head;
	while(NULL != curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	* head = prev;
}

/*---------------------------------------------------------------------------*/

/**
 * @brief static helper function to reverse linked list recursively
 *
 * @param head head of the node
 *
 * @return updated head will be returned
 */
static node_t * recursive_reverse_list_helper(node_t * head)
{
	if(head->next == NULL) {
		return head;
	}
	else {
		node_t * new_head = recursive_reverse_list_helper(head->next);
		head->next->next = head;
		head->next = NULL;
		return new_head;
	}
}

/*---------------------------------------------------------------------------*/

void recursive_reverse_list(node_t **head)
{
	node_t * update_head = NULL;
	update_head = recursive_reverse_list_helper(*head);
	*head = update_head;
}

/*---------------------------------------------------------------------------*/

int32_t delete_node_in_list(node_t ** head, int32_t key)
{
	node_t * current = NULL;
	node_t * prev = NULL;

	current = *head;
	/* If head node itself holds the key to be deleted */
	if((NULL != current) &&(key == current->data)) {
		*head = current->next;
		free(current);
		return 0;
	}
	/* Search for the key to be deleted, keep track of the
	 * previous node as we need to change 'prev->next'
	 */
	while((NULL != current) && (key != current->data)) {
		prev = current;
		current = current->next;
	}
	/* If key was not present in linked list */
	if(NULL == current) {
		return -1;

	} else {
		/* Unlink the node from list and make new link */
		prev->next = current->next;
		free(current);
		return 0;
	}
}

/*---------------------------------------------------------------------------*/

void delete_list(node_t ** head)
{
	node_t * current = NULL;
	node_t * next = NULL;

	current = * head;
	while (NULL != current) {
		next = current->next;
		free(current);
		current = next;
	}
	/* dereference head to affect the real head back in the caller */
	*head = NULL;
}

/*---------------------------------------------------------------------------*/
