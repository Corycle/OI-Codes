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
const int Maxn=1e6;
const int M=1e6+5;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,tot;
int nxt[N],lst[M],Ans[N],Answer[N];
int a[N],b[N],vis[M],num[M],prime[N];
void Prepare(){
	for(int i=2;i<=Maxn;i++){
		if(!vis[i]){num[i]=1;prime[++cnt]=i;}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=Maxn;j++){
			vis[i*prime[j]]=1;
			num[i*prime[j]]=num[i]+1;
			if(i%prime[j]==0)break;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Prepare();
	for(int i=1;i<=n;i++){a[i]=read();Ans[i]=Maxn;}
	for(int i=1;i<=n;i++){nxt[i]=lst[a[i]];lst[a[i]]=i;}
	for(int x=1;x<=Maxn;x++){
		tot=0;
		for(int i=1;i<=Maxn/x;i++){
			for(int j=lst[x*i];j;j=nxt[j])b[++tot]=j;
		}
		int B=b[1];
		for(int i=2;i<=tot;i++){
			if(num[a[b[i]]]<num[a[B]]||(num[a[b[i]]]==num[a[B]]&&b[i]<B))swap(B,b[i]);
		}
		for(int i=2;i<=tot;i++){
			int A=b[i],val=num[a[A]]+num[a[B]]-(num[x]<<1);
			if(val<Ans[A]||(val==Ans[A]&&B<Answer[A])){Ans[A]=val;Answer[A]=B;}
			if(val<Ans[B]||(val==Ans[B]&&A<Answer[B])){Ans[B]=val;Answer[B]=A;}
		}
	}
	for(int i=1;i<=n;i++)printf("%d\n",Answer[i]);
	return 0;
}
