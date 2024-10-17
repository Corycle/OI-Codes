/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll f[N];
char s[N];
int n,m,cnt;
int h[N],fa[N],sum[N*2],lst[N*2];
int p[N][M],g[N][M],num[N],dep[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void ST(){
	memset(g,0x3f,sizeof(g));
	int k=(int)(log(n)/log(2));
	for(int i=1;i<=n;i++)p[i][0]=fa[i];
	for(int i=1;i<=n;i++)g[i][0]=min(num[i],num[fa[i]]);
	for(int j=1;j<=k;j++){
		for(int i=1;i<=n;i++){
			if(p[i][j-1]){
				p[i][j]=p[p[i][j-1]][j-1];
				g[i][j]=min(g[i][j-1],g[p[i][j-1]][j-1]);
			}
		}
	}
}
int Ask(int x,int y){
	int ans=num[x];
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y]){
			ans=min(ans,g[x][k]);
			x=p[x][k];
		}
	}
	return ans;
}
void Solve(int x){
	f[x]=f[fa[x]];
	if(Ask(x,lst[num[x]])>=num[x]){
		f[x]+=sum[num[x]];
		sum[num[x]]++;
	}
	else sum[num[x]]=1;
	lst[num[x]]=x;
}
void DFS1(int x,int depth){
	dep[x]=depth;
	num[x]=num[fa[x]];
	if(s[x]=='(')num[x]++;
	if(s[x]==')')num[x]--;
	int Sum=sum[num[x]];
	int Lst=lst[num[x]];
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS1(y,depth+1);
	}
	sum[num[x]]=Sum;
	lst[num[x]]=Lst;
}
void DFS2(int x){
	int Sum=sum[num[x]];
	int Lst=lst[num[x]];
	Solve(x);
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		DFS2(y);
	}
	sum[num[x]]=Sum;
	lst[num[x]]=Lst;
}
int main(){
//	freopen("brackets.in","r",stdin);
//	freopen("brackets.out","w",stdout);
	n=read();
	scanf("%s",s+1);
	for(int i=2;i<=n;i++){
		fa[i]=read();
		Add(fa[i],i);
	}
	ll ans=0;
	num[0]=N;sum[N]=1;
	DFS1(1,1);ST();DFS2(1);
	for(ll i=1;i<=n;i++)ans^=(i*f[i]);
	printf("%lld",ans);
	return 0;
}