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
const int N=2e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Max,Ans;
int n,m,tot,cnt,h[N];
struct edge{int to,next,id;}d[N*2];
void Add(int x,int y,int id){
	d[++cnt]=(edge){y,h[x],id};h[x]=cnt;
}
struct Heap{
	priority_queue<ll>q1,q2;
	void Insert(ll x){q1.push(x);}
	void Delete(ll x){q2.push(x);}
	ll Top(){
		while(!q1.empty()&&!q2.empty()&&q1.top()==q2.top()){q1.pop();q2.pop();}
		return q1.empty()?0:q1.top();
	}
}F1[N],F2[N];
struct Tree{int ch[2],fa,aux,rev;ll val,sum,lmax,rmax,Ans;};
struct Link_Cut_Tree{
	Tree t[N];
	void Pushup(int x){
		int l=t[x].ch[0],r=t[x].ch[1];
		ll p1=F2[x].Top();F2[x].Delete(p1);
		ll p2=F2[x].Top();F2[x].Insert(p1);
		t[x].sum=t[l].sum+t[r].sum+t[x].val;
		t[x].lmax=max(t[l].lmax,t[l].sum+t[x].val+max(t[r].lmax,F2[x].Top()));
		t[x].rmax=max(t[r].rmax,t[r].sum+t[x].val+max(t[l].rmax,F2[x].Top()));
		t[x].Ans=max(t[x].sum,max(F1[x].Top(),max(t[l].Ans,t[r].Ans)));
		t[x].Ans=max(t[x].Ans,t[x].val+max(t[l].rmax+t[r].lmax,p1+max(p2,max(t[l].rmax,t[r].lmax))));
	}
	void Rotate(int x){
		int y=t[x].fa;int z=t[y].fa;
		int l=(x!=t[y].ch[0]),r=l^1;
		if(t[y].aux)t[z].ch[y!=t[z].ch[0]]=x;
		else{t[x].aux=0;t[y].aux=1;}
		t[x].fa=z;t[y].fa=x;
		t[t[x].ch[r]].fa=y;
		t[y].ch[l]=t[x].ch[r];
		t[x].ch[r]=y;
		Pushup(y);Pushup(x);
	}
	void Splay(int x){
		while(t[x].aux){
			int y=t[x].fa,z=t[y].fa;
			if(t[y].aux){
				if((x==t[y].ch[0])^(y==t[z].ch[0]))Rotate(x);
				else Rotate(y);
			}
			Rotate(x);
		}
	}
	void Access(int x){
		int y=0;
		while(x){
			Splay(x);
			if(t[x].ch[1]){
				F1[x].Insert(t[t[x].ch[1]].Ans);
				F2[x].Insert(t[t[x].ch[1]].lmax);
			}
			t[t[x].ch[1]].aux=0;
			t[x].ch[1]=y;
			t[t[x].ch[1]].aux=1;
			if(t[x].ch[1]){
				F1[x].Delete(t[t[x].ch[1]].Ans);
				F2[x].Delete(t[t[x].ch[1]].lmax);
			}
			Pushup(x);y=x;x=t[x].fa;
		}
	}
	ll Change(int x,ll y){Access(x);Splay(x);t[x].val=y;Pushup(x);return t[x].Ans;}
}tree;
void DFS(int x,int fa){
	for(int i=h[x];i;i=d[i].next){
		int y=d[i].to;
		if(y==fa)continue;
		DFS(y,x);
		int p=d[i].id;
		tree.t[y].fa=p;F1[p].Insert(tree.t[y].Ans);F2[p].Insert(tree.t[y].lmax);tree.Pushup(p);
		tree.t[p].fa=x;F1[x].Insert(tree.t[p].Ans);F2[x].Insert(tree.t[p].lmax);tree.Pushup(x);
	}
}
int main(){
//	freopen("diameter.in","r",stdin);
//	freopen("diameter.out","w",stdout);
	n=read();m=read();Max=read();tot=n;
	for(int i=1;i<n;i++){
		ll x=read(),y=read(),z=read();
		tree.t[++tot].val=z;
		tree.Pushup(tot);
		Add(x,y,tot);
		Add(y,x,tot);
	}
	DFS(1,0);
	while(m--){
		ll x=(read()+Ans)%(n-1)+1;
		ll y=(read()+Ans)%Max;
		printf("%lld\n",Ans=tree.Change(x+n,y));
	}
	return 0;
}