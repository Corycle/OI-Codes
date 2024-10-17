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
const int N=5000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,k,Ans,num[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void FMT(int a[],int n,int f){
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);j++){
			if(i&j)a[j-i]=(a[j-i]+1ll*f*a[j]%Mod+Mod)%Mod;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();k=read();
	for(int i=1;i<=m;i++)num[read()]++;
	FMT(num,n,1);
	for(int i=0;i<(1<<n);i++)num[i]=Pow(num[i],k);
	FMT(num,n,-1);
	for(int i=1;i<(1<<n);i++)Ans=(Ans+num[i])%Mod;
	printf("%d",Ans);
	return 0;
}