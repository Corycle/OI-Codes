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
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,water,x,y,z,last,ans;
int a[10005],b[10005],ok[10005],l[10005],r[10005],f[2][1001],g[1001];
int main(){
	int i,j,k;
	n=read();m=read();water=read();
    for(i=0;i<n;i++)scanf("%d%d",&a[i],&b[i]);
    for(i=0;i<=n;i++)l[i]=1,r[i]=m;
    for(i=1;i<=water;i++){
        scanf("%d%d%d",&x,&y,&z);
        ok[x]=1;
        l[x]=y+1;
        r[x]=z-1;
    }
    for(j=0;j<=m;j++)f[1][j]=1e9;
    for(i=0;i<n;i++){
        for(j=1;j<=m;j++) g[j]=f[0][j]; //如果不是上升上来的，那么肯定在原位置
        for(j=1;j<=m;j++){
            x=min(m,j+a[i]); 
            g[x]=min(g[x],g[j]+1); //x由j上升而来
        }
        for(j=1;j<=m;j++){
            x=j-b[i];
            if(x>=l[i+1]&&x<=r[i+1])f[1][x]=min(f[1][x],f[0][j]);
            x=min(m,j+a[i]);
            if(x>=l[i+1]&&x<=r[i+1])f[1][x]=min(f[1][x],g[j]+1);
        }
        for(j=1;j<=m;j++){
            if(f[1][j]!=1e9)last=max(last,i+1);
            f[0][j]=f[1][j];
            f[1][j]=1e9;
        }
    }
    if(last==n) {
        cout<<'1'<<endl;
        ans=1e9;
        for(j=1;j<=m;j++)ans=min(ans,f[0][j]);
        cout<<ans;
    }
    else{
        cout<<'0'<<endl;
        z=0;
        for(i=0;i<=last;i++) 
        if(ok[i]==1) z++;
        cout<<z<<endl; 
    }
    return 0;
}