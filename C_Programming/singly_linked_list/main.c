/*
 * main.c
 *
 * Description: The application function to use the node.c node.h library APIs
 *
 *  Created on: Jun 25, 2018
 *      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 */

#include "node.h"

int main(int argc, char* argv[])
{
	printf("\n---- Linked List ----\n");
	printf("\n");
	node_t *head = NULL;
	int32_t status = 0;
	uint32_t pos = 0;
	uint32_t index = 0;

	printf("Initial list print\n");
	print_list(head);
	printf("\n");

	status = length_of_list(head);
	printf("Before List creation length: %u\n", status);
	printf("\n");

	/* create a list using insert_node_at_beginning() API */
	for (index = 0; index < 5; index++) {
		insert_node_at_beginning(&head, index);
	}
	printf("insert_node_at_beginning() list print\n");
	print_list(head);
	printf("\n");

	/* add nodes using insert_node_at_end() API */
	for (index = 10; index < 15; index++) {
		insert_node_at_end(&head, index);
	}
	printf("insert_node_at_end() list print\n");
	print_list(head);
	printf("\n");

	status = length_of_list(head);
	printf("After List creation length: %u\n", status);
	printf("\n");

	/* check the data in the list which are divisible by 3 */
	for (index = 0; index < 15; index++) {
		if (index % 3 == 0) {
			pos = find_element_in_list(head, index);
			if (0 == pos) {
				printf("%d not present in the given list\n", index);
			} else {
				printf("%d present in position %u\n", index, pos);
			}
		}
	}
	printf("\n");

	for (index = 0; index < 15; index++) {
		if (index % 4 == 0) {
			status = delete_node_in_list(&head, index);
			if(0 == status) {
				printf("%d first occurrence node deleted\n", index);
			} else {
				printf("%d key not there in the given list\n", index);
			}
		}
	}
	printf("\n");

	status = length_of_list(head);
	printf("After Deleting (index mod 4 == 0) length: %u\n", status);
	printf("\n");

	printf("After Deleting (index mod 4 == 0) list print\n");
	print_list(head);
	printf("\n");

	reverse_list(&head);
	printf("After reversing list print\n");
	print_list(head);
	printf("\n");

	recursive_reverse_list(&head);
	printf("After reversing recursively\n");
	print_list(head);
	printf("\n");

	/* delete the complete list */
	delete_list(&head);

	status = length_of_list(head);
	printf("After Deleting list length %u\n", status);
	printf("\n");

	printf("After Deleting list print\n");
	print_list(head);
	printf("\n");

	return 0;
}
