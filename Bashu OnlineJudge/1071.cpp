#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//stack<_>_;
//queue<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
int main()  
{  
    int n,k,i,j,s,g[105][105],f[105],ans[105]; //f记录0-9每个数字的最多的变换次数  
    char str[105];  
    memset(g,0,sizeof(g));  
    scanf("%s",str);  
    int len=strlen(str); //len=输入的s的位数  
    scanf("%d",&k);  
    for(i=1;i<=k;i++)  
    {  
        int a,b;  
        scanf("%d%d",&a,&b);  
        g[a][b]=1;  
    }  
    for(s=0;s<=9;s++)  
    {  
        for(i=0;i<=9;i++)  
        {  
            if(s!=i)  
                for(j=0;j<=9;j++)  
                    if(i!=j&&s!=j)  
                        g[i][j]=g[i][j]||(g[i][s]&&g[s][j]);  
        }  
    }  
    for(i=0;i<=9;i++)  
    {  
        f[i]=1;  
        for(j=0;j<=9;j++)  
            f[i]+=g[i][j];  
    }  
    memset(ans,0,sizeof(ans));  
    ans[0]=1;  
    ans[1]=1;  
    for(i=0;i<len;i++) //从输入的s的最高位开始循环到个位  
    {  
        for(j=1;j<=ans[0];j++)  
            ans[j]*=f[str[i]-'0'];  
        for(j=1;j<=ans[0];j++)  
        {  
            ans[j+1]+=ans[j]/10;  
            ans[j]%=10;  
        }  
        while(ans[ans[0]+1])  
        {  
            ans[0]++;  
            ans[ans[0]+1]+=ans[ans[0]]/10;  
            ans[ans[0]]%=10;  
        }  
    }  
    for(i=ans[0];i>=1;i--)  
        printf("%d",ans[i]);  
    return 0;  
}  