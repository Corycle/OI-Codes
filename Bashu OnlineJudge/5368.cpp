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
const ll inf=1e18;
const int N=200005;
const int K=2;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
priority_queue<ll>q;
int n,m,D,P,type,Root,Q[K];
ll Pow(ll x,ll y){return y==1?x:x*x;}
struct Tree{int ch[2],d[K],Max[K],Min[K];};
bool cmp(Tree A,Tree B){return A.d[D]<B.d[D];}
struct KD_Tree{
	int tot;
	Tree t[N];
	void Pushup(int p){
		for(int i=0;i<K;i++){
			if(t[p].ch[0]){
				t[p].Max[i]=max(t[p].Max[i],t[t[p].ch[0]].Max[i]);
				t[p].Min[i]=min(t[p].Min[i],t[t[p].ch[0]].Min[i]);
			}
			if(t[p].ch[1]){
				t[p].Max[i]=max(t[p].Max[i],t[t[p].ch[1]].Max[i]);
				t[p].Min[i]=min(t[p].Min[i],t[t[p].ch[1]].Min[i]);
			}
		}
	}
	void Build(int &p,int l,int r,int d){
		int mid=(l+r)>>1;p=mid;D=d;
		nth_element(t+l,t+mid,t+r+1,cmp);
		if(l<mid)Build(t[p].ch[0],l,mid-1,d^1);
		if(r>mid)Build(t[p].ch[1],mid+1,r,d^1);
		Pushup(p);
	}
	void Insert(int &p,Tree New,int d){
		if(!p){p=++tot;t[p]=New;return;}
		if(New.d[d]<=t[p].d[d])Insert(t[p].ch[0],New,d^1);
		if(New.d[d]>t[p].d[d]) Insert(t[p].ch[1],New,d^1);
		Pushup(p);
	}
	ll Guess(int p){
		ll ans=0;
		for(int i=0;i<K;i++){
			if(Q[i]<t[p].Min[i])ans+=Pow(abs(Q[i]-t[p].Min[i]),type);
			if(Q[i]>t[p].Max[i])ans+=Pow(abs(Q[i]-t[p].Max[i]),type);
		}
		return ans;
	}
	ll Dist(int p){
		ll ans=0;
		for(int i=0;i<K;i++){
			ans+=pow(abs(Q[i]-t[p].d[i]),type);
		}
		return ans;
	}
	void Query(int p){
		if(!p)return;
		ll dis=Dist(p);
		ll dl=Guess(t[p].ch[0]);
		ll dr=Guess(t[p].ch[1]);
		if(dis<q.top()){q.pop();q.push(dis);}
		if(dl<dr){
			if(dl<q.top())Query(t[p].ch[0]);
			if(dr<q.top())Query(t[p].ch[1]);
		}
		else{
			if(dr<q.top())Query(t[p].ch[1]);
			if(dl<q.top())Query(t[p].ch[0]);
		}
	}
}tree;
char op[5];
void Read(Tree &p){
	p.ch[0]=p.ch[1]=0;
	for(int i=0;i<K;i++){
		p.d[i]=p.Max[i]=p.Min[i]=read();
	}
}
void Print(){
	ll x=q.top();q.pop();
	if(q.size())Print();
	printf("%.4lf ",pow(x,1.0/type));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();type=read();P=read();
	for(int i=1;i<=n;i++)Read(tree.t[i]);
	tree.tot=n;tree.Build(Root,1,n,0);
	while(m--){
		scanf("%s",op);
		if(op[0]=='A'){
			Tree New;Read(New);
			tree.Insert(Root,New,0);
		}
		if(op[0]=='Q'){
			while(q.size())q.pop();
			for(int i=1;i<=P;i++)q.push(inf);
			Q[0]=read();Q[1]=read();
			tree.Query(Root);
			Print();puts("");
		}
	}
	return 0;
}