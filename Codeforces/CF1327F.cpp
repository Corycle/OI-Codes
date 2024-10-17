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
const int Mod=998244353;
const int N=5e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K,Sum,Ans;
int f[N],sum[N],pos[N];
struct Node{int l,r,val;}P[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();m=read();Ans=1;
	for(int i=1;i<=m;i++){P[i].l=read();P[i].r=read();P[i].val=read();}
	for(int k=0;k<K;k++){
		for(int i=1;i<=n+1;i++)f[i]=sum[i]=pos[i]=0;
		for(int i=1;i<=m;i++){
			if((P[i].val>>k)&1){sum[P[i].l]++;sum[P[i].r+1]--;}
			else pos[P[i].r+1]=max(pos[P[i].r+1],P[i].l);
		}
		for(int i=1;i<=n+1;i++){sum[i]+=sum[i-1];pos[i]=max(pos[i],pos[i-1]);}
		f[0]=1;Sum=1;
		for(int l=0,r=1;r<=n+1;r++){
			while(l<pos[r]){Sum=mod(Sum-f[l]+Mod);l++;}
			f[r]=(sum[r]?0:Sum);Sum=mod(Sum+f[r]);
		}
//		cout<<endl;
//		for(int i=1;i<=n+1;i++)cout<<sum[i]<<" ";cout<<endl;
//		for(int i=1;i<=n+1;i++)cout<<pos[i]<<" ";cout<<endl;
//		for(int i=1;i<=n+1;i++)cout<<f[i]<<" ";cout<<endl;
		Ans=1ll*Ans*f[n+1]%Mod;
	}
	printf("%d\n",Ans);
	return 0;
}
