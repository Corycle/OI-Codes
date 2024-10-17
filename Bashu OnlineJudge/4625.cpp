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
const int N=2e4+5;
const int M=62;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N];
vector<int>G[N];
int n,m,cnt,fa[N],p[N][20],dep[N];
struct Line_Basis{
	ll p[M],num;
	void Init(){memset(p,0,sizeof(p));num=0;}
	void Insert(ll x){for(int i=M-1;i>=0;i--)if((x>>i)&1){if(!p[i]){p[i]=x;num++;return;}x^=p[i];}}
	friend Line_Basis operator+(Line_Basis A,Line_Basis B){
		if(A.num<B.num)swap(A,B);
		for(int i=M-1;i>=0;i--)if(B.p[i])A.Insert(B.p[i]);
		return A;
	}
}F[N][20];
void DFS(int x,int depth){
	dep[x]=depth;p[x][0]=fa[x];F[x][0].Insert(a[x]);
	for(int i=1;i<20;i++){
		if(p[x][i-1]){
			p[x][i]=p[p[x][i-1]][i-1];
			F[x][i]=F[x][i-1]+F[p[x][i-1]][i-1];
		}
	}
	for(auto y:G[x])if(y!=fa[x]){fa[y]=x;DFS(y,depth+1);}
}
Line_Basis Get_Line_Basis(int x,int y){
	Line_Basis ans;ans.Init();
	if(dep[x]<dep[y])swap(x,y);
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(dep[x]-(1<<k)>=dep[y]){ans=ans+F[x][k];x=p[x][k];}
	}
	if(x==y){ans.Insert(a[x]);return ans;}
	for(int k=(int)(log(dep[x])/log(2));k>=0;k--){
		if(p[x][k]!=p[y][k]){ans=ans+F[x][k]+F[y][k];x=p[x][k];y=p[y][k];}
	}
	ans.Insert(a[x]);ans.Insert(a[y]);ans.Insert(a[fa[x]]);
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	DFS(1,1);
	while(m--){
		ll ans=0;
		int x=read(),y=read();
		Line_Basis Ans=Get_Line_Basis(x,y);
		for(int i=M-1;i>=0;i--)ans=max(ans,ans^Ans.p[i]);
		printf("%lld\n",ans);
	}
	return 0;
}