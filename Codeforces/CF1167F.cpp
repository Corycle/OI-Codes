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
const int Mod=1e9+7;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,a[N],b[N];
int mod(int x){return x>=Mod?x-Mod:x;}
bool cmp(int x,int y){return a[x]<a[y];}
struct Tree{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<N;x+=lowbit(x))c[x]=mod(c[x]+y);}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans=mod(ans+c[x]);return ans;}
	int Query(int l,int r){return mod(Ask(r)-Ask(l-1)+Mod);}
}t1,t2;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){a[i]=read();b[i]=i;}
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++){
		int x=b[i];
		int sum=1ll*x*(n-x+1)%Mod;
		sum=mod(sum+1ll*t2.Query(x,n)*x%Mod);
		sum=mod(sum+1ll*t1.Query(1,x)*(n-x+1)%Mod);
		Ans=mod(Ans+1ll*a[x]*sum%Mod);
		t1.Add(x,x);t2.Add(x,n-x+1);
	}
	printf("%d\n",Ans);
	return 0;
}
