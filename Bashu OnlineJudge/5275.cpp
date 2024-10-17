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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N],b[N],A[N],B[N],Ans[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void FMT_OR(int a[],int n,int f){
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);j++){
			if(i&j)a[j]=(a[j]+f*a[j-i])%Mod;
		}
	}
}
void FMT_AND(int a[],int n,int f){
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);j++){
			if(i&j)a[j-i]=(a[j-i]+f*a[j])%Mod;
		}
	}
}
void FWT(int a[],int n,int f){
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);j++){
			if(i&j){
				int x=a[j-i],y=a[j];
				a[j-i]=mod(x+y);
				a[j]=mod(x-y+Mod);
			}
		}
	}
	if(f==-1){
		int Inv=Pow(1<<n,Mod-2);
		for(int i=0;i<(1<<n);i++)a[i]=1ll*a[i]*Inv%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=0;i<(1<<n);i++)a[i]=read();
	for(int i=0;i<(1<<n);i++)b[i]=read();
	
	for(int i=0;i<(1<<n);i++){A[i]=a[i];B[i]=b[i];}
	FMT_OR(A,n,1);FMT_OR(B,n,1);
	for(int i=0;i<(1<<n);i++)Ans[i]=1ll*A[i]*B[i]%Mod;
	FMT_OR(Ans,n,-1);
	for(int i=0;i<(1<<n);i++)printf("%d ",(Ans[i]%Mod+Mod)%Mod);printf("\n");
	
	for(int i=0;i<(1<<n);i++){A[i]=a[i];B[i]=b[i];}
	FMT_AND(A,n,1);FMT_AND(B,n,1);
	for(int i=0;i<(1<<n);i++)Ans[i]=1ll*A[i]*B[i]%Mod;
	FMT_AND(Ans,n,-1);
	for(int i=0;i<(1<<n);i++)printf("%d ",(Ans[i]%Mod+Mod)%Mod);printf("\n");
	
	for(int i=0;i<(1<<n);i++){A[i]=a[i];B[i]=b[i];}
	FWT(A,n,1);FWT(B,n,1);
	for(int i=0;i<(1<<n);i++)Ans[i]=1ll*A[i]*B[i]%Mod;
	FWT(Ans,n,-1);
	for(int i=0;i<(1<<n);i++)printf("%d ",(Ans[i]%Mod+Mod)%Mod);printf("\n");
	return 0;
}