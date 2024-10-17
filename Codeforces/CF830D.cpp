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
const int N=405;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,f[N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int F(int n,int k){
	if(!k)return 1;
	if(n==1)return (k==1);
	if(f[n][k]>=0)return f[n][k];
	int ans=0;
	for(int i=0;i<=k;i++)ans=mod(ans+1ll*F(n-1,i)*F(n-1,k-i)%Mod);
	for(int i=0;i<=k-1;i++)ans=mod(ans+1ll*F(n-1,i)*F(n-1,k-1-i)%Mod);
	for(int i=0;i<=k;i++)ans=mod(ans+1ll*F(n-1,i)*F(n-1,k-i)%Mod*k%Mod*2%Mod);
	for(int i=0;i<=k+1;i++)ans=mod(ans+1ll*F(n-1,i)*F(n-1,k+1-i)%Mod*(k+1)%Mod*k%Mod);
	return f[n][k]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	memset(f,-1,sizeof(f));
	printf("%d\n",F(n,1));
	return 0;
}
