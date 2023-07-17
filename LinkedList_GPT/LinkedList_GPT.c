#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* next;
};

void insert(struct Node** head, int data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	if (*head == NULL) {
		*head = newNode;
	}else {
		struct Node* current = *head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;
		
	}
}

void display(struct Node* head) {
	struct Node* current = head;
	while (current != NULL) {
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

int main()
{
	struct Node* head = NULL;
	insert(&head, 10);
	insert(&head, 20);
	insert(&head, 30);
	
	display(head);

	return 0;
}