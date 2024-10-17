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
int n,m,a[25],sum,f[25],maxx;
void dfs(int x,int s){
	int i,j,k;
	maxx=max(maxx,s);
	if(x==n+1)return;
	if(s+a[x]<=m)dfs(x+1,s+a[x]);
	dfs(x+1,s);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	for(i=1;i<=n;i++){
		a[i]=read();
		sum+=a[i];
	}
	m=sum-m;
	dfs(1,0);
	printf("%d",m-maxx);
	return 0;
}