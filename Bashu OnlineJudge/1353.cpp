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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int a,b,p,cnt,Ans;
int fa[N],vis[N],prime[N];
int Find(int x){return x==fa[x]?x:fa[x]=Find(fa[x]);}
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
	a=read();b=read();p=read();
	Prepare(b);
	for(int i=1;i<=b;i++)fa[i]=i;
	for(int i=1;i<=cnt;i++){
		if(prime[i]>=p){
			for(int j=prime[i];j<=b;j+=prime[i]){
				fa[Find(prime[i])]=Find(j);
			}
		}
	}
	for(int i=a;i<=b;i++)if(fa[i]==i)Ans++;
	printf("%d",Ans);
	return 0;
}