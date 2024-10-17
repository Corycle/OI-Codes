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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,vis[N],num[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();vis[1]=1;
	for(int i=1;i<=n;i++)num[i]=1;
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		if(vis[x])vis[y]=1;
		num[x]--;num[y]++;
		if(!num[x])vis[x]=0;
	}
	for(int i=1;i<=n;i++)Ans+=vis[i];
	printf("%d\n",Ans);
	return 0;
}
