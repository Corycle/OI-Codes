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
const int Inv2=5e8+4;
const int Mod=1e9+7;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K,Ans;
int a[N],b[N];
vector<int>F[N];
ll mod(ll x){return x>=Mod?x-Mod:x;}
ll Sum(int x){return 1ll*(1+x)%Mod*x%Mod*Inv2%Mod;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<=n;i++)b[i]=a[i]=read();
	sort(b+1,b+n+1);b[0]=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+b[0]+1,a[i])-b;
		F[a[i]].push_back(i);
	}
	for(int i=1;i<=b[0];i++){
		int num=F[i].size();
		int fst=F[i][0],lst=F[i][num-1];
		Ans=mod(Ans+Sum(1ll*n*K%Mod));
		Ans=mod(Ans-Sum(fst-1)-Sum(n-lst)+Mod);
		Ans=mod(Ans-Sum((fst-1)+(n-lst))*(K-1)%Mod+Mod);
		for(int j=1;j<num;j++){
			int x=F[i][j-1],y=F[i][j];
			Ans=(Ans-Sum(y-x-1)*K%Mod+Mod)%Mod;
		}
		Ans=(Ans%Mod+Mod)%Mod;
	}
	printf("%d\n",Ans);
	return 0;
}