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
#define uint unsigned int
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e7+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool vis[N];
uint seed,a[N];
int n,m,cnt,prime[N/10];
inline uint getnext(){seed^=seed<<13;seed^=seed>>17;seed^=seed<<5;return seed;}
void Prepare(int maxn){
	for(int i=2;i<=maxn;i++){
		if(!vis[i])prime[++cnt]=i;
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();seed=read();Prepare(2e7);
	for(int i=1;i<=n;i++)a[i]=getnext();
	for(int j=1;j<=cnt;j++){
		for(int i=1;1ll*i*prime[j]<=n;i++){
			a[i*prime[j]]+=a[i];
		}
	}
	uint ans=0;
	for(int i=1;i<=n;i++)ans^=a[i];
	cout<<ans<<endl;
	return 0;
}