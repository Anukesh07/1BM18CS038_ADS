#include <iostream>
using namespace std;
class Node
{
  int *key;
  int t;
  Node **C;
  int n;
  bool l;
   public:
  Node(int t1,bool l1);
  void insertNonFull(int k);
  void splitChild(int i,Node *y);
  void traverse();
  friend class BTree;
};
class BTree
{
  Node *root;
  int t;
   public:
  BTree(int t1)
  {
    root=NULL;
    t=t1;
  }
  void traverse()
  {
    if(root!=NULL)
      root->traverse();
  }
  void insert(int k);
};
Node::Node(int t2, bool l2)
{
  t=t2;
  l=l2;
  key=new int[2*t-1];
  C=new Node *[2*t];
  n=0;
}
void Node::traverse()
{
  int i;
  for(i=0;i<n;i++)
  {
    if(l==false)
      C[i]->traverse();
    cout<<" "<<key[i];
  }
  if(l==false)
    C[i]->traverse();
}
void BTree::insert(int k)
{
  if(root==NULL)
  {
    root=new Node(t,true);
    root->key[0]=k;
    root->n=1;
  }
  else
  {
    if(root->n==2*t-1)
    {
      Node *s=new Node(t,false);
      s->C[0]=root;
      s->splitChild(0,root);
      int i=0;
      if(s->key[0]<k)
        i++;
      s->C[i]->insertNonFull(k);
      root=s;
    }
    else
      root->insertNonFull(k);
  }
}
void Node::insertNonFull(int k)
{
  int i=n-1;
  if(l==true)
  {
    while(i>=0&&key[i]>k)
    {
      key[i+1]=key[i];
      i--;
    }
    key[i+1]=k;
    n=n+1;
  }
  else
  {
    while(i>=0&&key[i]>k)
      i--;
    if(C[i+1]->n==2*t-1)
    {
      splitChild(i+1,C[i+1]);
      if(key[i+1]<k)
        i++;
    }
    C[i+1]->insertNonFull(k);
  }
}
void Node::splitChild(int i,Node *y)
{
  Node *z=new Node(y->t,y->l);
  z->n=t-1;
  for(int j=0;j<t-1;j++)
    z->key[j]=y->key[j+t];
  if(y->l==false)
  {
    for(int j=0;j<t;j++)
      z->C[j]=y->C[j+t];
  }
  y->n=t-1;
  for(int j=n;j>=i+1;j--)
    C[j+1]=C[j];
  C[i+1]=z;
  for(int j=n-1;j>=i;j--)
    key[j+1]=key[j];
  key[i]=y->key[t-1];
  n=n+1;
}
int main()
{
  BTree t(3);
  int val;
  cout<<"Enter the values to be inserted or -99 to exit\n";
  while(1)
  {
    cin>>val;
    if(val== -99)
    {
        break;
    }
    t.insert(val);
  }
  cout<<"The B-tree is: ";
  t.traverse();
}
