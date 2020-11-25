#include <bits/stdc++.h>
using namespace std;
enum Color{Red,Black};
struct Node
{
    int data;
    bool color;
    Node *l,*r,*par;
    Node(int data)
    {
       this->data=data;
       l=r=par=NULL;
       this->color=Red;
    }
};
class RBTree
{
private:
    Node *root;
protected:
    void rotateL(Node *&,Node *&);
    void rotateR(Node *&,Node *&);
    void fixVio(Node *&,Node *&);
public:
    RBTree()
    {
        root=NULL;
    }
    void insert(const int &n);
    void inorder();
    void levelOrder();
};
void inorderHelp(Node *root)
{
    if (root == NULL)
        return;
    inorderHelp(root->l);
    cout<<root->data<<"  ";
    inorderHelp(root->r);
}
Node* BSTInsert(Node* root,Node *pt)
{
    if(root==NULL)
       return pt;
    if(pt->data<root->data)
    {
        root->l=BSTInsert(root->l,pt);
        root->l->par=root;
    }
    else if(pt->data>root->data)
    {
        root->r=BSTInsert(root->r,pt);
        root->r->par=root;
    }
    return root;
}
void levelOrderHelp(Node *root)
{
    if(root==NULL)
        return;
    std::queue<Node *> q;
    q.push(root);
    while(!q.empty())
    {
        Node *temp=q.front();
        cout<<temp->data<<"  ";
        q.pop();
        if(temp->l!=NULL)
            q.push(temp->l);
        if(temp->r!=NULL)
            q.push(temp->r);
    }
}
void RBTree::rotateL(Node *&root,Node *&pt)
{
    Node *pt_r=pt->r;
    pt->r=pt_r->l;
    if(pt->r!=NULL)
        pt->r->par=pt;
    pt_r->par=pt->par;
    if(pt->par==NULL)
        root=pt_r;
    else if(pt==pt->par->l)
        pt->par->l=pt_r;
    else
        pt->par->r=pt_r;
    pt_r->l=pt;
    pt->par=pt_r;
}
void RBTree::rotateR(Node *&root,Node *&pt)
{
    Node *pt_l=pt->l;
    pt->l=pt_l->r;
    if(pt->l!=NULL)
        pt->l->par=pt;
    pt_l->par=pt->par;
    if(pt->par==NULL)
        root=pt_l;
    else if(pt==pt->par->l)
        pt->par->l=pt_l;
    else
        pt->par->r=pt_l;
    pt_l->r=pt;
    pt->par=pt_l;
}
void RBTree::fixVio(Node *&root,Node *&pt)
{
    Node *par_pt=NULL;
    Node *grand_par_pt=NULL;
    while((pt!=root)&&(pt->color!=Black)&&(pt->par->color==Red))
    {
        par_pt=pt->par;
        grand_par_pt=pt->par->par;
        if(par_pt==grand_par_pt->l)
        {
            Node *uncle_pt=grand_par_pt->r;
            if(uncle_pt!=NULL&&uncle_pt->color==Red)
            {
                grand_par_pt->color=Red;
                par_pt->color=Black;
                uncle_pt->color=Black;
                pt=grand_par_pt;
            }
            else
            {
                if(pt==par_pt->r)
                {
                    rotateL(root,par_pt);
                    pt=par_pt;
                    par_pt=pt->par;
                }
                rotateR(root,grand_par_pt);
                swap(par_pt->color,
                           grand_par_pt->color);
                pt=par_pt;
            }
        }
        else
        {
            Node *uncle_pt=grand_par_pt->l;
            if((uncle_pt!=NULL)&&(uncle_pt->color==Red))
            {
                grand_par_pt->color=Red;
                par_pt->color=Black;
                uncle_pt->color=Black;
                pt=grand_par_pt;
            }
            else
            {
                if(pt==par_pt->l)
                {
                    rotateR(root,par_pt);
                    pt=par_pt;
                    par_pt=pt->par;
                }
                rotateL(root,grand_par_pt);
                swap(par_pt->color,grand_par_pt->color);
                pt=par_pt;
            }
        }
    }
    root->color=Black;
}
void RBTree::insert(const int &data)
{
    Node *pt=new Node(data);
    root=BSTInsert(root,pt);
    fixVio(root,pt);
}
void RBTree::inorder()
{
    inorderHelp(root);
}
void RBTree::levelOrder()
{
    levelOrderHelp(root);
}
int main()
{
    RBTree tree;
    int val;
    cout<<"Enter the values to be inserted or -99 to exit\n";
    while(1)
    {
        cin>>val;
        if(val== -99)
        {
            break;
        }
        tree.insert(val);
    }
    cout << "Inoder Traversal of the created tree\n";
    tree.inorder();
    cout << "\n\nLevel Order Traversal of the created tree\n";
    tree.levelOrder();
    return 0;
}
