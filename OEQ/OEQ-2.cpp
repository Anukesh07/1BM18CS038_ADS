#include<bits/stdc++.h>
using namespace std;
void uniqueNumbers(int L,int R)
{
    for(int i=L;i<=R;i++)
    {
        int n=i;
        bool vis[10]={false};
        while(n)
        {
            if(vis[n%10])
                break;
            vis[n%10]=true;
            n=n/10;
        }
        if(n==0)
            cout<<i<<" ";
    }
}
int main()
{
    int L,R;
    cin>>L;
    cin>>R;
    uniqueNumbers(L,R);
    return 0;
}
