/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
const int M=350;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
vector<int>G[N];
int n,m,num,tot,cnt,root;
ll s[N],sum[N],tag[N],Ans[M],S[N];
int a[N],b[N],h[N],L[N],R[N],st[N],ed[N],fa[N],Num[N][400];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x){
	L[x]=++tot;
	s[x]=sum[L[x]]=a[x];
	for(int i=1;i<=num;i++){
		Num[x][i]=Num[fa[x]][i]+(b[x]==i);
	}
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa[x])continue;
		fa[y]=x;DFS(y);
		s[x]+=s[y];
	}
	R[x]=tot;
}
inline ll Sum(int x){return sum[x]+tag[b[x]];}
inline ll Ask(int x){return Sum(R[x])-Sum(L[x]-1);}
void Prepare(){
	while(ed[num]<n){num++;st[num]=ed[num-1]+1;ed[num]=min(ed[num-1]+M,n);}
	for(int i=1;i<=num;i++)for(int j=st[i];j<=ed[i];j++)b[j]=i;
}
void Update(int x,ll dlt){
	for(int i=1;i<=num;i++){
		Ans[i]+=Num[x][i]*dlt;
		S[i]=S[i-1]+Ans[i];
	}
	for(int i=L[x];i<=ed[b[L[x]]];i++)sum[i]+=dlt;
	for(int i=b[L[x]]+1;i<=num;i++)tag[i]+=dlt;
}
ll Query(int l,int r){
	ll ans=0;
	int x=b[l],y=b[r];
	if(x==y)for(int i=l;i<=r;i++)ans+=Ask(i);
	else{
		for(int i=l;i<=ed[x];i++)ans+=Ask(i);
		for(int i=st[y];i<=r;i++)ans+=Ask(i);
		ans+=S[y-1]-S[x];
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		int x=read(),y=read();
		if(!x)root=y;
		else{Add(x,y);Add(y,x);}
	}
	Prepare();DFS(root);
	for(int i=1;i<=n;i++){
		s[i]+=s[i-1];//Count by index
		sum[i]+=sum[i-1];//Count by DFS
	}
	for(int i=1;i<=num;i++){
		Ans[i]=s[ed[i]]-s[st[i]-1];
		S[i]=S[i-1]+Ans[i];
	}
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1){Update(l,r-a[l]);a[l]=r;}
		if(op==2)printf("%lld\n",Query(l,r));
	}
	return 0;
}