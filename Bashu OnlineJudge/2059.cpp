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
#define lson t[p].l,l,mid
#define rson t[p].r,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=4e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans;
int fa[N],g[N],sum[N];
int Find(int x,int t){
	return x==fa[x]?x:(g[x]<=t?Find(fa[x],t):x);
}
const int mod=998244353;
ll a,b,c,d,Answer;
void deciphering(){
	a=(Ans+a+b*c+c*d+d*b)%mod;
	b=(Ans+b+b*b%mod*b%mod*c%mod+a*b%mod*c%mod*d%mod)%mod;
	c=(Ans+1+a+b+c+d+a*b+b*d+c*a)%mod;
	d=(Ans+d*114514+a*123456+c*654321+b*10007)%mod;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	a=read();b=read();c=read();d=read();
	for(int i=1;i<=n;i++){fa[i]=i;sum[i]=1;}
	for(int i=1;i<=m;i++){
		deciphering();
		int op=(a%2+2)%2;
		if(op==0){
			int x=Find((b%n+n)%n+1,i);
			int y=Find((c%n+n)%n+1,i);
			if(fa[x]!=fa[y]){
				Ans=1;
				if(sum[x]>sum[y])swap(x,y);
				fa[x]=y;sum[y]+=sum[x];g[x]=i;
			}
			else Ans=0;
		}
		if(op==1){
			int t=(d%i+i)%i;
			int x=Find((b%n+n)%n+1,t);
			int y=Find((c%n+n)%n+1,t);
			Ans=(x==y);
		}
		if(Ans)Answer^=i;
	}
	printf("%lld",Answer);
	return 0;
}