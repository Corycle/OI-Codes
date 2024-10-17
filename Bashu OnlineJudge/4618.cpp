#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,cnt;
ll tot,num,root;
ll h[N],dfn[N*2];
struct edge{ll to,next;}d[N*2];
struct Tree{
	ll ch[2],fa,sum,val;
	ll kind,size,tag;
}t[N];
void Add(ll x,ll y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(ll x){
	dfn[++num]=x;
	for(ll i=h[x];i;i=d[i].next){
		ll y=d[i].to;DFS(y);
	}
	dfn[++num]=x+n;
}
void Pushup(ll x){
	t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].val;
	t[x].size=t[t[x].ch[0]].size+t[t[x].ch[1]].size+t[x].kind;
}
void Pushdown(ll x){
	if(t[x].tag){
		t[t[x].ch[0]].tag+=t[x].tag;
		t[t[x].ch[1]].tag+=t[x].tag;
		t[t[x].ch[0]].val+=t[x].tag*t[t[x].ch[0]].kind;
		t[t[x].ch[1]].val+=t[x].tag*t[t[x].ch[1]].kind;
		t[t[x].ch[0]].sum+=t[x].tag*t[t[x].ch[0]].size;
		t[t[x].ch[1]].sum+=t[x].tag*t[t[x].ch[1]].size;
		t[x].tag=0;
	}
}
void Rotate(ll x,ll &f){
	ll y=t[x].fa;ll z=t[y].fa;
	ll l=(x!=t[y].ch[0]);ll r=l^1;
	if(y==f)f=x;
	else{
		if(y==t[z].ch[0])t[z].ch[0]=x;
		else t[z].ch[1]=x;
	}
	Pushdown(y);Pushdown(x);
	t[x].fa=z;t[y].fa=x;
	t[t[x].ch[r]].fa=y;
	t[y].ch[l]=t[x].ch[r];
	t[x].ch[r]=y;
	Pushup(y);Pushup(x);
}
void Splay(ll x,ll &f){
	while(x!=f){
		ll y=t[x].fa;ll z=t[y].fa;
		if(y!=f){
			if(t[y].ch[0]==x^t[z].ch[0]==y)Rotate(x,f);
			else Rotate(y,f);
		}
		Rotate(x,f);
	}
}
void Insert(ll x){
	if(!tot){
		tot++;
		root=x;
		return;
	}
	t[root].ch[1]=x;
	t[x].fa=root;
	Splay(x,root);
}
void Build(){
	dfn[0]=n*2+1;
	dfn[num+1]=n*2+2;
	for(ll i=0;i<=num+1;i++){
		Insert(dfn[i]);
	}
}
ll Pred(ll x){
	Splay(x,root);
	x=t[x].ch[0];
	while(t[x].ch[1])x=t[x].ch[1];
	return x;
}
ll Succ(ll x){
	Splay(x,root);
	x=t[x].ch[1];
	while(t[x].ch[0])x=t[x].ch[0];
	return x;
}
ll Ask(ll x){
	Splay(x,root);
	return t[x].sum-t[t[x].ch[1]].sum;
}
void Change(ll x,ll y){
	ll t1=Pred(x),t2=Succ(x+n);
	Splay(t1,root);
	Splay(t2,t[t1].ch[1]);
	ll z=t[t2].ch[0];
	t[z].fa=t[t2].ch[0]=0;
	Pushup(t2);Pushup(t1);
	ll t3=Succ(y);
	Splay(t3,t[y].ch[1]);
	t[z].fa=t3;t[t3].ch[0]=z;
	Pushup(t3);Pushup(t1);
}
void Update(ll x,ll addv){
	ll t1=Pred(x),t2=Succ(x+n);
	Splay(t1,root);
	Splay(t2,t[t1].ch[1]);
	ll y=t[t2].ch[0];
	t[y].tag+=addv;
	t[y].val+=addv*t[y].kind;
	t[y].sum+=addv*t[y].size;
	Pushup(t2);Pushup(t1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=2;i<=n;i++)Add(read(),i);
	for(ll i=1;i<=n;i++){
		t[i].val=read();
		t[i].sum=t[i].val;
		t[i+n].sum=-t[i].val;
		t[i+n].val=-t[i].val;
		t[i].size=t[i].kind=1;
		t[i+n].size=t[i+n].kind=-1;
	}
	DFS(1);
	Build();
	m=read();
	while(m--){
		char op[1];
		scanf("%s",op);
		if(op[0]=='Q'){ll x=read();printf("%lld\n",Ask(x));}
		if(op[0]=='C'){ll x=read(),y=read();Change(x,y);}
		if(op[0]=='F'){ll x=read(),y=read();Update(x,y);}
	}
	return 0;
}