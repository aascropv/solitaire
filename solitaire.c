#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char value[3];
	struct node *next;
} node_t;

node_t *putCard(node_t *head, char newValue[])
{
	node_t *new_node = malloc(sizeof(node_t));
	strcpy(new_node->value, newValue);
	new_node->next = NULL;
	node_t *current = head;
	if (current != NULL) {
		while(current->next) {
			current = current->next;
		}
		current->next = new_node;
	}
	else
		head = new_node;
	return head;
}

node_t *shift(node_t *head)
{
	node_t *tmp = head;
	head = head->next;
	tmp->next = NULL;
	node_t *current = head;
	while(current->next)
		current = current->next;
	current->next = tmp;
	return head;
}

node_t *remove_card(node_t *head)
{
	node_t *tmp = head;
	head = head->next;
	tmp->next = NULL;
	free(tmp);
	return head;
}

void printList(node_t *head)
{
	for (node_t *current = head; current; current = current->next) {
		printf("%s", current->value);
		if (current->next != NULL)
			printf(" ");
	}
}

int main()
{
	char input[2];
	char order[13][3] ={"K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2", "A"};
	node_t *cardList = NULL;
	while(scanf("%s", input) != EOF) {
		cardList = putCard(cardList, input);
		strcpy(input, "");
	}
	printList(cardList);
	for (int i = 0; i <= 12; i++) {
		while(1) {
			if (cardList->next != NULL)
				printf("\r\n");
			if (strcmp(cardList->value, order[i]) == 0) {
				cardList = remove_card(cardList);
				if (cardList == NULL)
					break;
				printList(cardList);
				break;
			}
			else
				cardList = shift(cardList);
			printList(cardList);
		}
		if (cardList == NULL)
			break;
	}
	return 0;
}