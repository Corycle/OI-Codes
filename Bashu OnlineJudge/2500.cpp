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
int n,m,t[10005],x[10005],y[10005],ans,f[10005],maxx[10005];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=m;i++){
		t[i]=read();x[i]=read();y[i]=read();
	}
	f[1]=1;maxx[1]=1;
	for(i=2;i<=m;i++){
		f[i]=1;
		for(j=i-1;j>=1;j--){
			if(maxx[j]+1<=f[i])break;
			else if(f[j]+1>f[i]&&(abs(x[i]-x[j])+abs(y[i]-y[j]))<=t[i]-t[j])f[i]=f[j]+1;
		}
		maxx[i]=max(f[i],maxx[i-1]);
		ans=max(f[i],ans);
	}
	printf("%d",ans);
	return 0;
}