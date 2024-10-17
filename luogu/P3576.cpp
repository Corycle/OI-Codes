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
const int Lim=1e9+5;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
vector<int>G[N];
int n,m,K,Sx,Sy,a[N],deg[N];
void Solve(int x,int fa,int Sum){
	if(deg[x]>1)Sum=min((ll)Lim,1ll*Sum*(deg[x]-1));
	if(deg[x]==1){
		int L=lower_bound(a+1,a+m+1,min((ll)Lim,1ll*Sum*K))-a;
		int R=lower_bound(a+1,a+m+1,min((ll)Lim,1ll*Sum*(K+1)))-a-1;
		if(L<=R)Ans+=R-L+1;
		return;
	}
	for(auto y:G[x]){if(y==fa)continue;Solve(y,x,Sum);}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();K=read();
	for(int i=1;i<=m;i++)a[i]=read();sort(a+1,a+m+1);
	int Sx=read(),Sy=read();deg[Sx]++;deg[Sy]++;
	for(int i=2;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);deg[x]++;deg[y]++;}
	Solve(Sx,0,1);Solve(Sy,0,1);
	printf("%lld\n",Ans*K);
	return 0;
}
