#include <bits/stdc++.h>
using namespace std;
int main()
{
    int T,N,A[100],i,j,tem;
    cin>>T;
    while(T!=0)
    {
        cin>>N;
        for(i=0;i<N;i++)
        {
            cin>>A[i];
        }
         tem=0;
        for(i=0;i<N-1;i++)
        {
            for(j=i+1;j<N;j++)
            {
                if(A[i]>A[j])
                {
                    tem=A[j];
                    A[j]=A[i];
                    A[i]=tem;
                }
            }
        }
        for(i=0;i<N-2;i++)
        {
            cout<<A[i];
            cout<<" ";
        }
        cout<<endl;
    T--;
    }
	return 0;
}
