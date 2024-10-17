#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
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
int n,m,a[15],q[1005],t,sum[15][1005],ans;
int mod=100000000;
bool f[1005][1005];
void dfs(int num,int x){
	if(num==m+1){
		q[++t]=x;
		return;
	}
	dfs(num+1,x<<1);
	if(!(x&1))dfs(num+1,x<<1|1);
}
bool pd(int x,int y){
	while(x&&y){
		if((x&1)&&(y&1))return false;
		x=x>>1;y=y>>1;
	}
	return true;
}
bool ppdd(int x,int y){
	while(x&&y){
		if(!(x&1)&&(y&1))return false;
		x=x>>1;y=y>>1;
	}
	if(!x&&y)return false;
	return true;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	int maxn=(1<<m)-1;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			a[i]=a[i]<<1|read();
		}
	}
	dfs(1,0);
	a[0]=maxn;
	for(i=1;i<=t;i++){
		if(!ppdd(a[1],q[i]))continue;
		sum[1][i]=1;
	}
	for(i=2;i<=n;i++){
		for(j=1;j<=t;j++){
			if(!ppdd(a[i],q[j]))continue;
			for(k=1;k<=t;k++){
				if(!ppdd(a[i-1],q[k]))continue;
				if(!pd(q[j],q[k]))continue;
				sum[i][j]=(sum[i][j]+sum[i-1][k])%mod;
			}
		}
	}
	for(i=1;i<=t;i++){
		ans=(ans+sum[n][i])%mod;
	}
	printf("%d",ans);
	return 0;
}