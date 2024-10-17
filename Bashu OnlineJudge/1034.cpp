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
struct Point{
	int x,y;
}p[1005];  
int n,sum,ans=0;  
int main(){  
    cin>>n; 
    int i,j,k;  
    for(i=1;i<=n;i++)cin>>p[i].x>>p[i].y;  
    for(i=1;i<=n;i++){  
        for(j=i+1;j<=n;j++){sum=2;  
            for(k=j+1;k<=n;k++)  
                if((p[i].x-p[k].x)*(p[j].y-p[k].y)==(p[j].x-p[k].x)*(p[i].y-p[k].y))sum++;  
            ans=max(ans,sum);  
        }  
    }  
    cout<<ans;  
    return 0;  
}