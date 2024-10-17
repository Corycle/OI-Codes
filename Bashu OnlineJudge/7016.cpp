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
#define fst first
#define scd second
#define mp make_pair
#define pii pair<ll,int>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=8e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,fa[N];
vector<int>G[N];
vector<pii>F[N];
ll Ans,Num,ans[N],num[N];
void DFS1(int x){for(auto y:G[x])if(y!=fa[x]){fa[y]=x;DFS1(y);}}
void DFS2(int x,int dist){
	Ans-=Num;Num-=num[dist];
	for(auto tmp:F[x]){Ans+=tmp.fst*tmp.scd;Num+=tmp.scd;num[tmp.fst+dist]+=tmp.scd;}
	ans[x]=Ans;for(auto y:G[x])if(y!=fa[x])DFS2(y,dist+1);
	for(auto tmp:F[x]){Ans-=tmp.fst*tmp.scd;Num-=tmp.scd;num[tmp.fst+dist]-=tmp.scd;}
	Num+=num[dist];Ans+=Num;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();
		for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
		DFS1(1);
		while(m--){
			int x=read(),val=read();
			while(x&&val){
				F[x].push_back(mp(val,1));
				if(val>2&&fa[x])F[x].push_back(mp(val-2,-1));
				val--;x=fa[x];
			}
		}
		DFS2(1,0);
		for(int i=1;i<=n;i++)printf("%lld ",ans[i]);puts("");
		for(int i=1;i<=n;i++){G[i].clear();F[i].clear();}
	}
	return 0;
}