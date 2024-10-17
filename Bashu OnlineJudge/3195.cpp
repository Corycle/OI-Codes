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
const int Mod=16777216;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N],L[N],R[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Cn2(int x){return (1ll*x*(x-1)/2)%Mod;}
int Cn3(int x){return (1ll*x*(x-1)/2*(x-2)/3)%Mod;}
struct Tree{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Clear(){for(int i=1;i<=n;i++)c[i]=0;}
	void Add(int x,int y){for(;x<=n;x+=lowbit(x))c[x]=mod(c[x]+y);}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans=mod(ans+c[x]);return ans;}
	int Query(int l,int r){return mod(Ask(r)-Ask(l-1)+Mod);}
}tree;
int Solve_1x2x(){
	int ans=0;
	tree.Clear();
	for(int i=1;i<=n;i++){
		ans=mod(ans+1ll*(n-i-R[i])*mod(1ll*L[i]*(i-1)%Mod-mod(Cn2(L[i])+tree.Ask(a[i]-1))+Mod)%Mod);
		tree.Add(a[i],i);
	}
	return ans;
}
int Solve_1xxx(){
	int ans=0;
	for(int i=1;i<=n;i++)ans=mod(ans+Cn3(n-i-R[i]));
	return ans;
}
int Solve_13xx(){
	int ans=0;
	tree.Clear();
	for(int i=1;i<=n;i++){
		ans=mod(ans+1ll*(n-i-R[i])*mod(1ll*L[i]*(a[i]-1)%Mod-mod(Cn2(L[i])+tree.Ask(a[i]-1))+Mod)%Mod);
		tree.Add(a[i],a[i]);
	}
	return ans;
}
int Solve_1234(){
	int ans=0;
	tree.Clear();
	for(int i=1;i<=n;i++){
		ans=mod(ans+1ll*(n-i-R[i])*tree.Ask(a[i]-1)%Mod);
		tree.Add(a[i],L[i]);
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){a[i]=read();tree.Add(a[i],1);L[i]=tree.Ask(a[i]-1);R[i]=a[i]-1-L[i];}
	printf("%d\n",mod(mod(Solve_1x2x()-Solve_1xxx()+Mod)+mod(Solve_13xx()+Solve_1234())));
	return 0;
}