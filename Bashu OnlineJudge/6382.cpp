/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char Ans[N];
int n,m,tot,cnt;
int a[N],b[N],h[N],vis[N],vst[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
bool Check(){
	queue<int>q;q.push(n);vis[n]=1;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=h[x];i;i=d[i].next){
			int y=d[i].to;
			if(!vis[y]){
				vis[y]=1;
				q.push(y);
			}
		}
	}
	return vis[1];
}
int main(){
//	freopen("grid.in","r",stdin);
//	freopen("grid.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++){
		if(1<=i+a[i]&&i+a[i]<=n)Add(i+a[i],i);
		if(1<=i+b[i]&&i+b[i]<=n)Add(i+b[i],i);
	}
	if(!Check()){printf("No solution!");return 0;}
	int x=1;
	while(1){
		if(x==n)break;
		vst[x]=1;
		if(1<=x+a[x]&&x+a[x]<=n&&vis[x+a[x]]){
			Ans[++tot]='a';x=x+a[x];
		}
		else if(1<=x+b[x]&&x+b[x]<=n){
			Ans[++tot]='b';x=x+b[x];
		}
		if(vst[x]){printf("Infinity!");return 0;}
	}
	printf("%s",Ans+1);
	return 0;
}