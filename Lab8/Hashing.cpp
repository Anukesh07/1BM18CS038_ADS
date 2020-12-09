#include<bits/stdc++.h>
using namespace std;
const int Tsize=200;
class HashN
{
   public:
      int k;
      int v;
      HashN(int k,int v)
      {
         this->k=k;
         this->v=v;
      }
};
class HashM
{
   private:
      HashN **t;
   public:
      HashM()
      {
         t=new HashN * [Tsize];
         for(int i=0;i<Tsize;i++)
         {
            t[i]=NULL;
        }
      }
      int HashF(int k)
      {
         return k%Tsize;
      }
      void Ins(int k,int v)
      {
         int h=HashF(k);
         while(t[h]!=NULL&&t[h]->k!=k)
         {
            h=HashF(h+1);
         }
         if(t[h]!=NULL)
            delete t[h];
         t[h]=new HashN(k,v);
      }
      int SearchK(int k)
      {
         int h=HashF(k);
         while(t[h]!=NULL&&t[h]->k!=k)
         {
            h=HashF(h+1);
         }
         if(t[h]==NULL)
            return -1;
         else
            return t[h]->v;
      }
      void Rem(int k)
      {
         int h=HashF(k);
         while(t[h]!=NULL)
         {
            if(t[h]->k==k)
               break;
            h=HashF(h+1);
         }
         if(t[h]==NULL)
         {
            cout<<"No Element found at key "<<k<<endl;
            return;
         }
         else
         {
            delete t[h];
         }
         cout<<"Element Deleted"<<endl;
      }
      ~HashM()
      {
         for(int i=0;i<Tsize;i++)
         {
            if(t[i]!=NULL)
               delete t[i];
               delete[] t;
         }
      }
};
int main()
{
   HashM hash;
   int k,v;
   int c;
   while(1)
   {
      cout<<"1.Insert an element into the table"<<endl;
      cout<<"2.Search an element from a key"<<endl;
      cout<<"3.Delete an element at a key"<<endl;
      cout<<"4.Exit"<<endl;
      cout<<"Enter your choice: ";
      cin>>c;
      switch(c) {
         case 1:
            cout<<"Enter the element to be inserted: ";
            cin>>v;
            cout<<"Enter the key at which the element is to be inserted: ";
            cin>>k;
            hash.Ins(k,v);
         break;
         case 2:
            cout<<"Enter the key of the element to be searched: ";
            cin>>k;
            if(hash.SearchK(k)==-1)
            {
               cout<<"No element found at key "<<k<<endl;
               continue;
            } else {
               cout<<"Element at key "<<k<<" : ";
               cout<<hash.SearchK(k)<<endl;
            }
         break;
         case 3:
            cout<<"Enter the key of the element to be deleted: ";
            cin>>k;
            hash.Rem(k);
         break;
         case 4:
            exit(1);
         default:
            cout<<"\nEnter a correct option\n";
      }
   }
   return 0;
}
