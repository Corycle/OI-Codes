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
const int N=3e5+5;
const int M=500;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,top,tot,num,Max;
ll A,B,C,Sum,total,sum[N],Ans[N];
int a[N],b[N],g[N],L[N],R[N],St[N],st[N],ed[N],pos[N],val[N],len[N],dep[N],cnt[N];
struct Trie{
	int num=1;
	int ch[N][26];
	void Insert(int id){
		int p=1;
		for(int i=1;i<=len[id];i++){
			int x=s[i]-'a';
			if(!ch[p][x]){ch[p][x]=++num;dep[num]=i;}
			p=ch[p][x];tot++;a[tot]=val[id];b[tot]=p;
		}
	}
}trie;
struct Node{int l,r,id;}P[N];
ll F(int n){return 1ll*n*(n+1)/2;}
ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
bool Check(ll f,int len){return f?(A*len+B*f>=C):0;}
bool cmp(Node A,Node B){return pos[A.l]!=pos[B.l]?pos[A.l]<pos[B.l]:A.r>B.r;}
void Prepare(){
	while(ed[num]!=tot){num++;st[num]=ed[num-1]+1;ed[num]=min(ed[num-1]+M,tot);}
	for(int i=1;i<=num;i++)for(int j=st[i];j<=ed[i];j++)pos[j]=i;
	St[++top]=0;
	for(int i=1;i<=tot;i++){
		int x=b[i];
		if(!Check(sum[x],dep[x])&&Check(sum[x]+a[i],dep[x])){
			if(!cnt[g[dep[x]]])St[++top]=g[dep[x]];
			cnt[g[dep[x]]]++;
		}
		sum[x]+=a[i];
	}
	St[++top]=Max+1;
	sort(St+1,St+top+1);
	for(int i=1;i<=top;i++){L[St[i]]=St[i-1];R[St[i]]=St[i+1];}
	for(int i=2;i<=top;i++)Sum+=F(St[i]-St[i-1]-1);
}
void Add(int x){int l=L[x],r=R[x];R[l]=x;L[r]=x;Sum=Sum-F(r-l-1)+F(x-l-1)+F(r-x-1);}
void Del(int x){int l=L[x],r=R[x];R[l]=r;L[r]=l;Sum=Sum+F(r-l-1)-F(x-l-1)-F(r-x-1);}
void Update(int i,int addv){
	int x=b[i];
	if(addv>0)if(!Check(sum[x],dep[x])&&Check(sum[x]+a[i],dep[x])){if(!cnt[g[dep[x]]])Add(g[dep[x]]);cnt[g[dep[x]]]++;}
	if(addv<0)if(Check(sum[x],dep[x])&&!Check(sum[x]-a[i],dep[x])){cnt[g[dep[x]]]--;if(!cnt[g[dep[x]]])Del(g[dep[x]]);}
	sum[x]+=a[i]*addv;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();A=read();B=read();C=read();
	for(int i=1;i<=n;i++)val[i]=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		len[i]=strlen(s+1);trie.Insert(i);
		Max=max(Max,len[i]);len[i]+=len[i-1];
	}
	for(int i=1;i<=Max;i++)g[i]=read();
	total=F(Max);Prepare();m=read();
	for(int i=1;i<=m;i++){
		P[i].l=len[read()-1]+1;
		P[i].r=len[read()];
		P[i].id=i;
	}
	sort(P+1,P+m+1,cmp);
	for(int i=1,p=1,l=1,r=tot;i<=num;i++){
		while(p<=m&&pos[P[p].l]==i){
			while(r>P[p].r)Update(r--,-1);
			while(l<P[p].l)Update(l++,-1);
			Ans[P[p].id]=total-Sum;
			while(l>st[i])Update(--l,1);
			p++;
		}
		while(r<tot)Update(++r,1);
		while(l<=ed[i])Update(l++,-1);
	}
	for(int i=1;i<=m;i++){
		ll d=gcd(total,Ans[i]);
		printf("%lld/%lld\n",Ans[i]/d,total/d);
	}
	return 0;
}