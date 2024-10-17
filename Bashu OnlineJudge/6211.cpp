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
const int N=1e5+5;
const int M=350;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>V[N];
int n,m,Q,tot,Ans;
int a[N],b[N],c[N],g[N],num[N],vis[N],sum[M][M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(int i=1;i<=n;i++){int x=read();if(x!=c[tot])c[++tot]=x;}n=tot;
	for(int i=1;i<=n;i++){V[c[i]].push_back(i);num[c[i]]++;}tot=0;
	for(int i=1;i<=m;i++)if(num[i]>=M)a[b[i]=++tot]=i;
	for(int i=1;i<n;i++){
		if(b[c[i]]&&b[c[i+1]]){
			sum[b[c[i]]][b[c[i+1]]]++;
			sum[b[c[i+1]]][b[c[i]]]++;
		}
	}
	while(Q--){
		int x=read(),op=vis[x]?-1:1;vis[x]^=1;
		Ans+=num[x]*op;
		if(b[x]){
			Ans-=g[b[x]]*op;
			for(int i=1;i<=tot;i++){
				if(vis[a[i]])Ans-=sum[b[x]][i]*op;
			}
		}
		else{
			for(auto pos:V[x]){
				if(vis[c[pos-1]])Ans-=op;g[b[c[pos-1]]]+=op;
				if(vis[c[pos+1]])Ans-=op;g[b[c[pos+1]]]+=op;
			}
		}
		printf("%d\n",Ans);
	}
	return 0;
}