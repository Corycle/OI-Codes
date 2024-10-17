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
#include<set>
#define ll long long
#define set_it set<int>::iterator
#define fst first
#define scd second
using namespace std;
const int inf=0x3f3f3f3f;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Sum;
int n,m,a[N];
struct Node{
	ll val;
	set<int>S;
	void Insert(int x){
		S.insert(x);
		int l=x,r=n-x+1;
		set_it p=S.find(x);
		if(p!=S.begin()){--p;l=x-(*p);++p;}
		if(p!=--S.end()){++p;r=(*p)-x;--p;}
		val+=1ll*l*r;
		Sum+=1ll*l*r;
	}
}F[N];
struct Trie{
	int Root=1,tot=1;
	map<int,int>ch[N];
	void Insert(int id){
		int p=Root;
		for(int i=1;i<=m;i++){
			if(!ch[p][a[i]])ch[p][a[i]]=++tot;
			p=ch[p][a[i]];F[p].Insert(id);
		}
	}
	int Merge(int x,int y){
		if(!x||!y)return x|y;
		if(ch[x].size()<ch[y].size())swap(x,y);
		for(auto t:ch[y])ch[x][t.fst]=Merge(ch[x][t.fst],ch[y][t.fst]);
		if(F[x].S.size()<F[y].S.size())swap(F[x],F[y]);
		for(auto t:F[y].S)F[x].Insert(t);
		Sum-=F[y].val;
		return x;
	}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)a[j]=read();
		tree.Insert(i);
	}
	ll Ans=Sum;
	for(int j=1;j<m;j++){
		int p=0;
		for(auto x:tree.ch[tree.Root]){
			if(!p)p=x.scd;
			else p=tree.Merge(p,x.scd);
		}
		tree.Root=p;
		Sum-=F[p].val;
		Ans+=Sum;
	}
	printf("%lld",Ans);
	return 0;
}