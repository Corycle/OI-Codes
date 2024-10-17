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
const int Mod=1e8+7;
const int N=5000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool vis[N];
int prime[N];
int n,m,cnt,Ans;
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(){
	for(int i=2;i<=n;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=n;j++){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)break;
		}
	}
}
int main(){
//	freopen("launch.in","r",stdin);
//	freopen("launch.out","w",stdout);
	n=read();Prepare();Ans=1;
	for(int i=1;i<=cnt;i++){
		ll p=prime[i],num=0;
		while(p<=n){
			num+=n/p;
			p*=prime[i];
		}
		if(num&1)num--;
		Ans=1ll*Ans*Pow(prime[i],num)%Mod;
	}
	printf("%d",Ans);
	return 0;
}