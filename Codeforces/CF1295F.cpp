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
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,Sum;
int a[N],b[N],t[N],C[N],F[N][N],G[N],inv[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){
	int ans=1;
	while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Sum=1;
	inv[0]=inv[1]=1;
	for(int i=2;i<N;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
	for(int i=n;i>=1;i--){
		t[++t[0]]=a[i]=read();
		t[++t[0]]=b[i]=read()+1;
		Sum=1ll*Sum*(b[i]-a[i])%Mod;
	}
	sort(t+1,t+t[0]+1);t[0]=unique(t+1,t+t[0]+1)-t-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(t+1,t+t[0]+1,a[i])-t;
		b[i]=lower_bound(t+1,t+t[0]+1,b[i])-t;
	}
	C[0]=G[0]=F[0][0]=1;
	for(int j=1;j<t[0];j++){
		int L=t[j+1]-t[j];
		for(int i=1;i<=n;i++)C[i]=1ll*C[i-1]*(L+i-1)%Mod*inv[i]%Mod;
		for(int i=n;i>=1;i--){
			if(a[i]<=j&&j<b[i]){
				for(int k=i-1,m=1;k>=0;k--){
					F[i][j]=mod(F[i][j]+1ll*C[m]*G[k]%Mod);
					if(a[k]<=j&&j<b[k])m++;
					else break;
				}
				G[i]=mod(G[i]+F[i][j]);
			}
		}
	}
	printf("%lld\n",1ll*G[n]*Pow(Sum,Mod-2)%Mod);
	return 0;
}
