#include<stdio.h> 
#include<stdlib.h> 
struct Node 
{ 
    int data; 
    struct Node* pxn;
}; 
  
struct Node* XOR(struct Node *m, struct Node *n) 
{ 
    return(struct Node*)((uintptr_t)(m)^(uintptr_t)(n)); 
} 
  
void insert_front(struct Node **headf, int data) 
{  
    struct Node *new=(struct Node*)malloc(sizeof(struct Node)); 
    new->data=data; 
    new->pxn=*headf; 
    if (*headf!=NULL) 
    { 
        (*headf)->pxn=XOR(new,(*headf)->pxn); 
    } 
    *headf=new; 
} 

struct Node insert_end(struct Node *headr, int data){
    struct Node *new=(struct Node *)malloc(sizeof(struct Node));  
    new->data=data; 
    if(headr==NULL){
        new->pxn=NULL;
        return *new;
    }
    if(headr->pxn==NULL)
    {
        headr->pxn=(struct Node*)((uintptr_t)(headr->pxn)^(uintptr_t)(new));
        new->pxn=headr;
        return *headr;
    }
    struct Node* prev=headr;
    struct Node* next=head->pxn;
    struct Node* q;
    while(prev!=next->pxn)
    {
        q=(struct Node*)((uintptr_t)(next->pxn)^(uintptr_t)(prev));
        prev=next;
        next=q;
    }
    next->pxn=(struct Node*)((uintptr_t)(next->pxn)^(uintptr_t)(new));
    new->pxn=next;
    return *headr;
}
  
void display(struct Node *head) 
{ 
    struct Node *curr=head; 
    struct Node *prev=NULL; 
    struct Node *next; 
    printf ("Following are the nodes of Linked List: \n"); 
    while (curr!=NULL) 
    {  
        printf("%d ",curr->data); 
        next=XOR(prev,curr->pxn); 
        prev=curr; 
        curr=next; 
    } 
} 
  
int main () 
{ 
    struct Node *head = NULL; 
    int i,ch,ele;
     
    do
    {printf("Enter 1 to Insert at beginning, 2 to Insert at end and 3 to exit \n");
    scanf("%d",&ch);
    switch(ch)
    {
      case 1 : printf("\n Element to insert:");
                        scanf("%d", &ele);
                        insert_front(&head, ele); 
                        printList (head); 
                        break;
      case 2 : printf("\n Element to insert:");
                        scanf("%d", &ele);
                        insert_end(head, ele);
                         display(head); 
                          break;
      case 3 : exit(0);
      default:printf("Please enter a valid choice\n");
    }
    }while(3);
    return 0; 
}