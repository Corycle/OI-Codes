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
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int a[N],fa[N];
struct Node{int Max,Min;}F[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
struct Tree{int ch[2],Max,Min;};
struct Trie{
	Tree t[N*10];
	int tot,root;
	int NewNode(){tot++;t[tot].ch[0]=t[tot].ch[1]=0;t[tot].Max=0;t[tot].Min=n;return tot;}
	void Init(){tot=0;root=NewNode();}
	void Insert(int x,int id){
		int p=root;
		for(int i=m-1;i>=0;i--){
			int c=(x>>i)&1;
			if(!t[p].ch[c])t[p].ch[c]=NewNode();
			p=t[p].ch[c];
			t[p].Min=min(t[p].Min,id);
			t[p].Max=max(t[p].Max,id);
			//Max and Min : record any two ids 
		}
	}
	Node Query(int x,int id){
		int p=root,ans=0;
		for(int i=m-1;i>=0;i--){
			int c=(x>>i)&1;
			if(c){
				if(t[p].ch[1]&&!(id==t[t[p].ch[1]].Min&&id==t[t[p].ch[1]].Max)){p=t[p].ch[1];ans+=(1<<i);}
				else p=t[p].ch[0];
			}
			else p=t[p].ch[0];
		}
		return (Node){ans,t[p].Min==id?t[p].Max:t[p].Min};
	}
	int Merge(int x,int y){
		if(!y)return x;
		if(!x)x=NewNode();
		t[x].Max=max(t[x].Max,t[y].Max);
		t[x].Min=min(t[x].Min,t[y].Min);
		t[x].ch[0]=Merge(t[x].ch[0],t[y].ch[0]);
		t[x].ch[1]=Merge(t[x].ch[1],t[y].ch[1]);
		return x;
	}
	void DFS(int x){
		if(t[x].ch[0])DFS(t[x].ch[0]);
		if(t[x].ch[1])DFS(t[x].ch[1]);
		t[x].ch[0]=Merge(t[x].ch[0],t[x].ch[1]);
	}
}tree;
void Build(){
	tree.Init();
	for(int i=1;i<=n;i++)tree.Insert(a[i],Find(i));
	tree.DFS(1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)a[i]=read();
	int num=n;ll Ans=0;
	while(num>1){
		Build();
		for(int i=1;i<=n;i++)F[i]=(Node){-1,0};
		for(int i=1;i<=n;i++){
			Node tmp=tree.Query(a[i],Find(i));
			if(tmp.Max>F[Find(i)].Max)F[Find(i)]=tmp;
		}
		for(int i=1;i<=n;i++){
			if(i==Find(i)){
				int x=Find(F[i].Min);
				if(x!=i){
					Ans+=F[i].Max;num--;
					fa[Find(x)]=Find(i);
				}
			}
		}
	}
	printf("%lld",Ans);
	return 0;
}