#include<iostream>  
#include<iomanip>  
#include<cstring>  
#include<cmath>  
#include<cstdio>  
using namespace std;  
int n,m,k;  
int mat[505][505]={0};  
//嫌麻烦后面都用的cin  cout输出..   
int main(){  
    scanf("%d%d",&n,&m);  
    for(int i=1;i<=n;i++)  
      for(int j=1;j<=m;j++)  
      {  
        char ch;  
        cin>>ch;  
        if(ch=='X')mat[i][j]=-2;  
        if(ch=='.')mat[i][j]=-1;//一定要把为'.'的mat[][] 设为-1，因为要从mat[][]为0的点开始走  
          //这样处理，有且仅有为'*'的点值为0，即起点。   
       }       
         
         
    scanf("%d",&k);  
    string s;  
    for(int p=1;p<=k;p++)  
      {  
      cin>>s;  
        for(int i=1;i<=n;i++)  
            for(int j=1;j<=m;j++)  
            {  
                if(mat[i][j]==p-1)//满足时间的有序，从上一步开始走。   
                {  
                //每个点横向或纵向更新mat[][]为当前步数p,遇到X就停止   
                if(s=="EAST")  
                {  
                    for(int q=j+1;q<=m;q++){if(mat[i][q]==-2)break;mat[i][q]=p;}  
                }  
                else if(s=="SOUTH")  
                {  
                    for(int q=i+1;q<=n;q++){if(mat[q][j]==-2)break;mat[q][j]=p;}  
                }  
                else if(s=="WEST")  
                {  
                    for(int q=j-1;q>=1;q--){if(mat[i][q]==-2)break;mat[i][q]=p;}  
                }  
                else if(s=="NORTH")  
                {  
                    for(int q=i-1;q>=1;q--){if(mat[q][j]==-2)break;mat[q][j]=p;}  
                }  
                  
                }  
            }  
      }  
        
      for(int i=1;i<=n;i++)  
        {  
            for(int j=1;j<=m;j++)  
            {  
                if(mat[i][j]==-2)cout<<"X";  
                else if(mat[i][j]==k)cout<<"*";//这个点是最终走到的点之一，即可能点。   
                else cout<<".";  
            }  
            cout<<endl;  
        }  
    return 0;  
}