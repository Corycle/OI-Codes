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
const int N=1e6+5;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int n,m,G,Mod,Phi,cnt,prime[N];
int a[N],b[N],c[N],R[N],P[N],tmp[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Divide(int n){for(int i=2;i<=7;i++)while(n%i==0){n/=i;prime[++cnt]=i;}}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
int GetG(int n){for(int g=2;;g++){bool flag=true;for(int i=1;i<=cnt;i++)if(Pow(g,n/prime[i])==1)flag=false;if(flag)return g;}}
void NTT(int a[],int n,int f){
	for(int i=0;i<n;i++)tmp[R[i]]=a[i];
	for(int i=0;i<n;i++)a[i]=tmp[i];
	for(int i=1,len=1;i<=cnt;len*=prime[i],i++){
		int x=len*prime[i];
		for(int j=0;j<n;j+=x){
			for(int k=0;k<x;k++){
				tmp[j+k]=0;
				for(int l=k%len;l<x;l+=len){
					tmp[j+k]=mod(tmp[j+k]+1ll*a[j+l]*P[Phi+f*(Phi/x)*(k*(l/len)%x)]%Mod);// (Wx)^(k*(l/len))
				}
			}
		}
		for(int j=0;j<n;j++)a[j]=tmp[j];
	}
	if(f==-1){
		int Inv=Pow(n,Mod-2);
		for(int i=0;i<n;i++)a[i]=1ll*a[i]*Inv%Mod;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Mod=n+1;Phi=n;Divide(Phi);G=GetG(Mod);
	for(int i=0;i<n;i++)a[i]=read();
	for(int i=0;i<n;i++)b[i]=read();
	P[0]=1;for(int i=1;i<N;i++)P[i]=1ll*P[i-1]*G%Mod;
	for(int i=0;i<n;i++){
		int pos=i,x=n;
		for(int j=cnt;j>=1;j--){
			R[i]+=(x/prime[j])*(pos%prime[j]);
			pos/=prime[j];x/=prime[j];
		}
	}
	NTT(a,n,1);NTT(b,n,1);
	for(int i=0;i<n;i++)c[i]=1ll*a[i]*Pow(b[i],m)%Mod;
	NTT(c,n,-1);
	for(int i=0;i<n;i++)printf("%d\n",c[i]);
	return 0;
}