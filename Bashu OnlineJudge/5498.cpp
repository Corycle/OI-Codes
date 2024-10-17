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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int M=50000005;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[10];
int n,m,cnt,Ans,Root,a[N],b[N],sum[N];
struct Node{int op,x,y,Ans;}P[N*3];
struct Tree{int l,r,sum;};
struct Segment_Tree{
	int tot;
	Tree t[N*100];
	int NewNode(){
		t[++tot]=(Tree){0,0,0};
		return tot;
	}
	void Add(int x,int y,int z,int &p,int l,int r){
		if(!p)p=NewNode();
		if(x<=l&&r<=y){t[p].sum+=z;return;}
		int mid=(l+r)>>1;
		if(x<=mid)Add(x,y,z,lson);
		if(y>mid) Add(x,y,z,rson);
	}
	int Ask(int x,int p,int l,int r){
		if(x<l||x>r||!p)return 0;
		if(l==r)return t[p].sum;
		int mid=(l+r)>>1;
		return Ask(x,lson)+Ask(x,rson)+t[p].sum;
	}
}tree;
void Solve(){
	tree.tot=0;	Root=0;Ans=0;
	int now=1,tag=0;sum[0]=1;
	for(int i=1;i<=n;i++){
		sum[i]=sum[i-1]+a[i];
		Ans+=(1ll*sum[i]*sum[i-1]<0);
	}
	for(int i=1;i<n;i++){
		int l=min(sum[i],sum[i+1]);
		int r=max(sum[i],sum[i+1]);
		tree.Add(l+M,r+M,1,Root,1,M*2);
	}
	for(int i=1;i<=m;i++){
		if(P[i].op==1){
			if(now==1)continue;
			now--;sum[now]-=tag;
			int l=min(sum[now],sum[now+1]);
			int r=max(sum[now],sum[now+1]);
			tree.Add(l+M,r+M,1,Root,1,M*2);
		}
		if(P[i].op==2){
			if(now==n)continue;
			int l=min(sum[now],sum[now+1]);
			int r=max(sum[now],sum[now+1]);
			tree.Add(l+M,r+M,-1,Root,1,M*2);
			sum[now]+=tag;now++;
		}
		if(P[i].op==3){
			int tmp=tag+P[i].x-a[now];
			Ans-=tree.Ask(M-tag,Root,1,M*2);
			Ans+=tree.Ask(M-tmp,Root,1,M*2);
			Ans-=(1ll*sum[now-1]*(sum[now]+tag)<0);
			Ans+=(1ll*sum[now-1]*(sum[now]+tmp)<0);
			tag=tmp;a[now]=P[i].x;
		}
		if(P[i].op==4)P[i].Ans+=Ans;
//		cout<<"Solve: "<<i<<" "<<Ans<<endl;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){a[i]=read();b[i]=read();}
	m=read();
	for(int i=1;i<=m;i++){
		scanf("%s",s);
		if(s[0]=='B')P[i].op=1;
		if(s[0]=='F')P[i].op=2;
		if(s[0]=='C'){P[i].op=3;P[i].x=read();P[i].y=read();}
		if(s[0]=='Q')P[i].op=4;
	}
	Solve();
	for(int i=1;i<=n;i++)swap(a[i],b[i]);
	for(int i=1;i<=m;i++)swap(P[i].x,P[i].y);
	Solve();
	for(int i=1;i<=m;i++){
		if(P[i].op==4)printf("%d\n",P[i].Ans);
	}
	return 0;
}