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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll K,Ans,dis[N];
int n,t,tot,a[N],b[N],ch[N][2],sum[N];
void Clear(){for(int i=0;i<=tot;i++)sum[i]=ch[i][0]=ch[i][1]=0;tot=0;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=2;i<=n;i++){int x=read();dis[i]=dis[x]^read();}
	for(int i=1;i<=n;i++)a[i]=b[i]=1;tot=1;
	for(int j=62;j>=0;j--){
		ll Sum=0,type=0;t^=1;Clear();
		for(int i=1;i<=n;i++){
			int x=(dis[i]>>j)&1;
			if(!ch[a[i]][x])ch[a[i]][x]=++tot;
			sum[ch[a[i]][x]]++;
		}
		for(int i=1;i<=n;i++)Sum+=sum[ch[b[i]][(dis[i]>>j)&1]];
		if(K>Sum){K-=Sum;Ans|=(1ll<<j);type=1;}
		for(int i=1;i<=n;i++){
			a[i]=ch[a[i]][(dis[i]>>j)&1];
			b[i]=ch[b[i]][((dis[i]>>j)&1)^type];
		}
	}
	printf("%lld\n",Ans);
	return 0;
}
