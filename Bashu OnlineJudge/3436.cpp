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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
set<int>F[N];
vector<int>G[N];
int n,m,tot,L[N],R[N],pos[N];
struct BIT{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]+=y;}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
	int Query(int l,int r){return Ask(r)-Ask(l-1);}
}t1,t2;
void DFS(int x){pos[L[x]=++tot]=x;for(auto y:G[x])if(!L[y])DFS(y);R[x]=tot;}
void Update(int x,int val){t1.Add(L[x],val);t1.Add(R[x]+1,-val);t2.Add(L[x],val*(R[x]-L[x]+1));}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	DFS(1);
	while(m--){
		int op=read(),x=read();
		if(op==1){
			int c=read();
			set_it tmp=F[c].lower_bound(L[x]);
			if(tmp!=F[c].begin()){tmp--;if(R[pos[*tmp]]>=R[x])continue;tmp++;}
			while(tmp!=F[c].end()&&(*tmp)<=R[x]){
				int y=(*tmp);++tmp;
				Update(pos[y],-1);F[c].erase(y);
			}
			F[c].insert(L[x]);Update(x,1);
		}
		if(op==2)printf("%d\n",(R[x]-L[x]+1)*t1.Ask(L[x])+t2.Query(L[x]+1,R[x]));
	}
	return 0;
}
