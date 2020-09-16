#include <stdio.h>
#include <stdlib.h>
struct Node
{
	int data;
	struct Node* next;
};
void display(struct Node* head)
{
	struct Node* ptr=head;
	while(ptr)
	{
		printf("%d ", ptr->data);
		ptr=ptr->next;
	}
}
void push(struct Node** head,int data)
{
	struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->data=data;
	newNode->next=*head;
	*head=newNode;
}
struct Node* reversed(struct Node** curr,int k)
{
	struct Node* prev=NULL;
	int count=0;
	while(*curr&&count++<k)
	{
		struct Node* next=(*curr)->next;
		(*curr)->next=prev;
		prev=*curr;
		*curr=next;
	}
	return prev;
}
struct Node *greversed(struct Node *head,int k)
{
	if(head==NULL)
		return NULL;
	struct Node* curr=head;
	struct Node* prev=reversed(&curr,k);
	head->next=greversed(curr,k);
	return prev;
}
int main(void)
{
	int keys[10],n;
	printf("Enter the size of the linked list\n");
    scanf("%d",&n);
	printf("Enter the nodes\n");
	for(int i=0;i<n;i++)
    {
        scanf("%d",&keys[i]);
    }
	struct Node *head=NULL;
	for(int i=n-1;i>=0;i--)
		push(&head,keys[i]);
    int k;
    printf("Enter the value of k\n");
    scanf("%d",&k);
	head=greversed(head,k);
	display(head);
	return 0;
}
