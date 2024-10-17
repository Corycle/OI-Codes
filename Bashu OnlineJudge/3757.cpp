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
const int N=1e4+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt,Ans,Mod,f[N],vis[N],prime[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(){
	for(int i=2;i<=n;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=n;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Mod=read();Prepare();f[0]=1;
	for(int i=1;i<=cnt;i++){
		for(int j=n;j>=prime[i];j--){
			int tmp=prime[i];
			while(tmp<=j){f[j]=mod(f[j]+1ll*f[j-tmp]*tmp%Mod);tmp*=prime[i];}
		}
	}
	for(int i=0;i<=n;i++)Ans=mod(Ans+f[i]);
	printf("%d\n",Ans);
	return 0;
}
