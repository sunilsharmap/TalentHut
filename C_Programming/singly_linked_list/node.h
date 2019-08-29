/*
 * node.h
 *
 * Description: Interface file for node.c library
 *
 *  Created on: Jun 25, 2018
 *      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 */

#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* Ref: https://www.geeksforgeeks.org/linked-list-set-1-introduction/ */

/**
 * @brief linked list node with one int data and one node pointer
 */
typedef struct Node {
	/** integer data of the node */
	int32_t data;
	/** node pointer to make the link */
	struct Node * next;
}node_t;

/**
 * @brief Insert a node at the beginning of the list.
 * If head == NULL, then new node will be head
 * else new node will be added first to list
 *
 * @param head head of the list
 * @param data new node data
 *
 * @return void
 */
void insert_node_at_beginning(node_t ** head, int32_t data);

/**
 * @brief Insert a node at the end of the list
 * If head == NULL, then new node will be head
 * else new node will be added end of list
 *
 * @param head head of the list
 * @param data new node data
 *
 * @return void
 */
void insert_node_at_end(node_t ** head, int32_t data);

/**
 * @brief length of list i.e number of nodes in the list
 *
 * @parma head head to list
 *
 * @return Number of nodes in the list
 */
uint32_t length_of_list(node_t * head);

/**
 * @brief print the data in the list from start to end
 *
 * @param head head of the list
 *
 * @retrun void
 */
void print_list(node_t * head);

/**
 * @brief find the element in the list
 *
 * @param head head of the list
 * @param data data to be searched in the list
 *
 * @return the position of the data in the list, 0 if not present
 */
uint32_t find_element_in_list(node_t * head, int32_t data);

/**
 * @brief reverse the list
 *
 * @param head head of the pointer
 *
 * @retrun void
 */
void reverse_list(node_t ** head);

/**
 * @brief delete the complete list
 *
 * @param head head of the list
 *
 * @return void
 */
void recursive_reverse_list(node_t ** head);

/**
 * @brief delete a given node from the list
 *
 * @param head head of the list
 * @param key the data of the node to be deleted
 *
 * @retrun 0 on success, -1 on key not in list
 */
int32_t delete_node_in_list(node_t ** head, int32_t key);

/**
 * @brief delete the complete list
 *
 * @param head head of the list
 *
 * @return void
 */
void delete_list(node_t ** head);

#endif /* NODE_H_ */
