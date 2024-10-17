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
    int n,b=0,c,ans=0,t=0;  
    int a[102]; 
    int i; 
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        b=b+a[i];
    }  
    b=b/n;
    for (i=1;i<=n-1;i++)  
    {     
        if(a[i]==b)
        {
            continue;
        }        
        c=a[i]-b;
        a[i+1]=a[i+1]+c;
        a[i]=a[i]-c;
        ans++;
    }  
    printf("%d\n",ans);  
    return 0;  
}