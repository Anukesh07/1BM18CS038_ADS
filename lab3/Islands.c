#include<stdbool.h>
#include<stdio.h>
#include<string.h>
#define ROW 5
#define COL 5
int isSafe(int M[][COL],int r,int c,bool vis[][COL])
{
    return(r>=0)&&(r<ROW)&&(c>=0)&&(c<COL)&&(M[r][c]&&!vis[r][c]);
}
void DFS(int M[][COL],int r,int c,bool vis[][COL])
{
    static int rNo[]={-1,-1,-1,0,0,1,1,1};
    static int cNo[]={-1,0,1,-1,1,-1,0,1 };
    vis[r][c]=true;
    for(int k=0;k<8;k++)
        if(isSafe(M,r+rNo[k],c+cNo[k],vis))
            DFS(M,r+rNo[k],c+cNo[k],vis);
}
int countIsl(int M[][COL])
{
    bool vis[ROW][COL];
    memset(vis,0,sizeof(vis));
    int count=0;
    for(int i=0;i<ROW;i++)
        for(int j=0;j<COL;j++)
            if(M[i][j]&&!vis[i][j])
            {
                DFS(M,i,j,vis);
                count++;
            }
    return count;
}
int main()
{
    printf("Enter the dimensions\n");
    int d;
    scanf("%d",&d);
    int M[d][d];
    printf("Enter the elements(1/0)\n");
    for(int i=0;i<d;i++)
    {
        for(int j=0;j<d;j++)
        {
            scanf("%d",&M[i][j]) ;
        }
    }
    printf("Number of islands is: %d\n", countIsl(M));
    return 0;
}
