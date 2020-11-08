#include<bits/stdc++.h>
using namespace std;
class Node
{
    public:
    int key;
    Node *left;
    Node *right;
    int depth;
};
int max(int a,int b)
{
    return(a>b)?a:b;
}
int depth(Node *n)
{
    if (n == NULL)
        return 0;
    return n->depth;
}
Node* newNode(int key)
{
    Node* node=new Node();
    node->key=key;
    node->left=NULL;
    node->right=NULL;
    node->depth=1;
    return(node);
}
Node *rightRotate(Node *y)
{
    Node *x=y->left;
    Node *T2=x->right;
    x->right=y;
    y->left=T2;
    y->depth=max(depth(y->left),depth(y->right))+1;
    x->depth=max(depth(x->left),depth(x->right))+1;
    return x;
}
Node *leftRotate(Node *x)
{
    Node *y=x->right;
    Node *T2=y->left;
    y->left=x;
    x->right=T2;
    x->depth=max(depth(x->left),depth(x->right))+1;
    y->depth=max(depth(y->left),depth(y->right))+1;
    return y;
}
int getBalance(Node *N)
{
    if(N==NULL)
        return 0;
    return depth(N->left)-depth(N->right);
}
Node* insert(Node* node,int key)
{
    if(node==NULL)
        return(newNode(key));
    if(key<node->key)
        node->left=insert(node->left,key);
    else if(key>node->key)
        node->right=insert(node->right,key);
    else
        return node;
    node->depth=1+max(depth(node->left),depth(node->right));
    int balance=getBalance(node);
    if(balance>1&&key<node->left->key)
        return rightRotate(node);
    if(balance<-1&&key>node->right->key)
        return leftRotate(node);
    if(balance>1&&key>node->left->key)
    {
        node->left=leftRotate(node->left);
        return rightRotate(node);
    }
    if(balance<-1&&key<node->right->key)
    {
        node->right=rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
Node * minValueNode(Node* node)
{
    Node* current=node;
    while(current->left!=NULL)
        current=current->left;
    return current;
}
Node* deleteNode(Node* root,int key)
{
    if(root==NULL)
        return root;
    if(key<root->key)
        root->left=deleteNode(root->left,key);
    else if(key>root->key)
        root->right=deleteNode(root->right,key);
else
    {
        if((root->left==NULL)||(root->right==NULL))
        {
            Node *temp=root->left?root->left:root->right;
            if(temp==NULL)
            {
                temp=root;
                root=NULL;
            }
            else
                *root=*temp;
            free(temp);
        }
   else
        {
            Node* temp=minValueNode(root->right);
            root->key=temp->key;
            root->right=deleteNode(root->right,temp->key);
        }
    }
    if (root == NULL)
    return root;
    root->depth=1+max(depth(root->left),depth(root->right));
    int balance = getBalance(root);
    if(balance>1&&getBalance(root->left)>=0)
        return rightRotate(root);
    if(balance>1&&getBalance(root->left)<0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if(balance<-1&&getBalance(root->right)<=0)
        return leftRotate(root);
    if(balance<-1&&getBalance(root->right)>0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
void postorder(Node *root)
{
    if(root!=NULL)
    {
        postorder(root->left);
        postorder(root->right);
        cout<<root->key<<" ";
    }
}
int main()
{
    Node *root=NULL;
    int val;
    cout<<"Enter the values to be inserted or -99 to exit\n";
    while(1)
    {
	    cin>>val;
	    if(val== -99)
	    {
	    	break;
		}
	    root=insert(root,val);
    }
    cout<<"Postorder traversal for the AVL tree is\n";
    postorder(root);
	cout<<"\nEnter the node to deleted\n";
	cin>>val;
    root=deleteNode(root,val);
    cout<<"Postorder traversal after deletion is\n";
    postorder(root);
    return 0;
}
