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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans;
int vis[N],num[N],prime[N];
int mod(int x){return x>=Mod?x=Mod:x;}
void Prepare(){
	for(int i=2;i<=n;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int Calc(int p){
	int t=n,ans=0;
	while(t){
		ans=mod(ans+t/p);
		t/=p;
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();Ans=1;
	for(int i=1;i<=cnt;i++){
		num[i]=Calc(prime[i])*2;
		Ans=1ll*Ans*(num[i]+1)%Mod;
	}
	printf("%d",Ans);
	return 0;
}