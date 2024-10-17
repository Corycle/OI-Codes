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
int n,T,Mod,num1,num2;
int a[N],b[N],c[N],p1[N],p2[N],Ans[N];
int Query1(ll x){
	ll pos=(x%Mod+Mod)%Mod,k=(x-pos)/Mod;
	return upper_bound(p1+1,p1+num1+1,pos)-p1-1+k*num1;
}
int Query2(ll x){
	ll pos=(x%Mod+Mod)%Mod,k=(x-pos)/Mod;
	return upper_bound(p2+1,p2+num2+1,pos)-p2-1+k*num2;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Mod=read();T=read();
	for(int i=1;i<=n;i++){
		a[i]=read();b[i]=read();
		if(b[i]==1)p1[++num1]=a[i];
		if(b[i]==2)p2[++num2]=a[i];
	}
	for(int i=1;i<=n;i++){
		int id=0;
		if(b[i]==1){
			c[i]=(a[i]+T)%Mod;
			id=(i+(Query2(a[i]+2ll*T)-Query2(a[i])))%n;
		}
		if(b[i]==2){
			c[i]=(a[i]-T%Mod+Mod)%Mod;
			id=(i-(Query1(a[i]-1)-Query1(a[i]-2ll*T-1))%n+n)%n;
		}
		if(!id)id=n;
		Ans[id]=c[i];
	}
	for(int i=1;i<=n;i++)printf("%d\n",Ans[i]);
	return 0;
}
