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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,top,Ans,a[N],L[N],R[N],st[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Sum(int x){return (1ll*x*(x+1)/2)%Mod;}
int Calc(int len){
	int p=len/(m-1);
	return mod(1ll*len*p%Mod-1ll*Sum(p)*(m-1)%Mod+Mod);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	a[st[top=0]=0]=inf;
	for(int i=1;i<=n;i++){while(top&&a[st[top]]<a[i])top--;L[i]=st[top]+1;st[++top]=i;}
	a[st[top=0]=n+1]=inf;
	for(int i=n;i>=1;i--){while(top&&a[st[top]]<=a[i])top--;R[i]=st[top]-1;st[++top]=i;}
	for(int i=1;i<=n;i++){
		Ans=mod(Ans+1ll*a[i]*Calc(R[i]-L[i]+1)%Mod);
		if(L[i]+m-1<i)Ans=mod(Ans-1ll*a[i]*Calc(i-L[i])%Mod+Mod);
		if(R[i]-m+1>i)Ans=mod(Ans-1ll*a[i]*Calc(R[i]-i)%Mod+Mod);
	}
	printf("%d\n",Ans);
	return 0;
}
