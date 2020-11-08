#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define SKIPLIST_MAX_LEVEL 6
typedef struct snode
{
    int k;
    int val;
    struct snode **forw;
}snode;
typedef struct skiplist
{
    int lvl;
    int size;
    struct snode *head;
}skiplist;
skiplist *skiplist_init(skiplist *list)
{
    int i;
    snode *head=(snode *)malloc(sizeof(struct snode));
    list->head=head;
    head->k=INT_MAX;
    head->forw=(snode **)malloc(sizeof(snode*)*(SKIPLIST_MAX_LEVEL+1));
    for(i=0;i<=SKIPLIST_MAX_LEVEL;i++)
        {
        head->forw[i]=list->head;
        }
    list->lvl=1;
    list->size=0;
    return list;
}
static int rand_level()
{
    int lvl=1;
    while(rand()<RAND_MAX/2&&lvl<SKIPLIST_MAX_LEVEL)
        lvl++;
    return lvl;
}
int skiplist_insert(skiplist *list,int k,int val)
{
    snode *update[SKIPLIST_MAX_LEVEL+1];
    snode *x=list->head;
    int i,lvl;
    for(i=list->lvl;i>=1;i--)
    {
        while(x->forw[i]->k<k)
            x=x->forw[i];
        update[i]=x;
    }
    x=x->forw[1];
    if(k==x->k)
    {
        x->val=val;
        return 0;
    }
    else
    {
        lvl=rand_level();
        if(lvl>list->lvl)
        {
            for(i=list->lvl+1;i<=lvl;i++)
            {
                update[i]=list->head;
            }
            list->lvl=lvl;
        }
        x=(snode *)malloc(sizeof(snode));
        x->k=k;
        x->val=val;
        x->forw=(snode **)malloc(sizeof(snode*)*(lvl+1));
        for(i=1;i<=lvl;i++)
        {
            x->forw[i]=update[i]->forw[i];
            update[i]->forw[i]=x;
        }
    }
    return 0;
}

snode *skiplist_search(skiplist *list,int k)
{
    snode *x=list->head;
    int i;
    for(i=list->lvl;i>=1;i--)
    {
        while(x->forw[i]->k<k)
            x=x->forw[i];
    }
    if(x->forw[1]->k==k)
    {
        return x->forw[1];
    }
    else
    {
        return NULL;
    }
    return NULL;
}
static void skiplist_node_free(snode *x)
{
    if(x)
    {
        free(x->forw);
        free(x);
    }
}
int skiplist_delete(skiplist *list,int k)
{
    int i;
    snode *update[SKIPLIST_MAX_LEVEL+1];
    snode *x=list->head;
    for(i=list->lvl;i>=1;i--)
    {
        while(x->forw[i]->k<k)
            x=x->forw[i];
        update[i]=x;
    }
    x=x->forw[1];
    if(x->k==k)
    {
        for(i=1;i<=list->lvl;i++)
        {
            if(update[i]->forw[i]!=x)
                break;
            update[i]->forw[1]=x->forw[i];
        }
        skiplist_node_free(x);
        while(list->lvl>1&&list->head->forw[list->lvl]==list->head)
            list->lvl--;
        return 0;
    }
    return 1;
}

static void skiplist_dump(skiplist *list)
{
    snode *x=list->head;
    while(x&&x->forw[1]!=list->head)
    {
        printf("%d[%d]->",x->forw[1]->k,x->forw[1]->val);
        x=x->forw[1];
    }
    printf("NILL\n");
}
int main()
{
    int a[]={5,9,13,3,21,1,7},i;
    skiplist list;
    skiplist_init(&list);
    printf("Insert:--------------------\n");
    for(i=0;i<sizeof(a)/sizeof(a[0]);i++)
    {
        skiplist_insert(&list,a[i],a[i]);
    }
    skiplist_dump(&list);
    printf("Search:--------------------\n");
    int keys[]={6,5,12,21,7};
    for(i=0;i<sizeof(keys)/sizeof(keys[0]);i++)
    {
        snode *x=skiplist_search(&list,keys[i]);
        if(x)
        {
            printf("key = %d, value = %d\n",keys[i],x->val);
        }
        else
        {
            printf("key = %d, key not found\n",keys[i]);
        }
    }
    printf("Delete:--------------------\n");
    skiplist_delete(&list,3);
    skiplist_delete(&list,1);
    skiplist_dump(&list);
    return 0;
}
