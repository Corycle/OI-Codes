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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,id[N],Ans[N];
struct Edge{int x,y,w,id;}E[N];
bool cmp(Edge A,Edge B){return A.w<B.w;}
struct Union_Basis{
	int st[N],fa[N],sum[N],num,top;
	int Find(int x){return x==fa[x]?x:Find(fa[x]);}
	void Init(){for(int i=1;i<=n;i++){fa[i]=i;sum[i]=1;}num=n;}
	void Merge(int x,int y){
		x=Find(x);y=Find(y);
		if(x!=y){
			if(sum[x]>sum[y])swap(x,y);
			num+=((sum[x]+sum[y])&1)-(sum[x]&1)-(sum[y]&1);
			fa[x]=y;sum[y]+=sum[x];st[++top]=x;
		}
	}
	void Reset(int tmp){
		while(top>tmp){
			int x=st[top--],y=fa[x];fa[x]=x;sum[y]-=sum[x];
			num-=((sum[x]+sum[y])&1)-(sum[x]&1)-(sum[y]&1);
		}
	}
}F;
void Divide(int l,int r,int ql,int qr){
	int tmp1=F.top;
	int mid=(l+r)>>1,pos=0;
	for(int i=l;i<=mid;i++)if(id[i]<ql)F.Merge(E[id[i]].x,E[id[i]].y);
	int tmp2=F.top;
	for(int i=ql;i<=qr;i++){
		if(E[i].id<=mid)F.Merge(E[i].x,E[i].y);
		if(!F.num){Ans[mid]=E[i].w;pos=i;break;}
	}
	F.Reset(tmp2);
	if(!pos){
		if(mid<r)Divide(mid+1,r,ql,qr);F.Reset(tmp1);
		return;
	}
	if(r>mid)Divide(mid+1,r,ql,pos);F.Reset(tmp1);
	for(int i=ql;i<pos;i++)if(E[i].id<l)F.Merge(E[i].x,E[i].y);
	if(l<mid)Divide(l,mid-1,pos,qr);F.Reset(tmp1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();F.Init();
	memset(Ans,-1,sizeof(Ans));
	for(int i=1;i<=m;i++){E[i].x=read();E[i].y=read();E[i].w=read();E[i].id=i;}
	sort(E+1,E+m+1,cmp);
	for(int i=1;i<=m;i++)id[E[i].id]=i;
	Divide(1,m,1,m);
	for(int i=1;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}
