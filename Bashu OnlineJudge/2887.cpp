#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,fa[N];
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=0;
	while(1){
		int ans=0;
		n=read();m=read();
		if(!n||!m)break;
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1;i<=m;i++){
			int x=read(),y=read();
			fa[Find(x)]=fa[Find(y)];
		}
		for(int i=1;i<=n;i++){
			if(fa[i]==i)ans++;
		}
		printf("Case %d: %d\n",++T,ans);
	}
	return 0;
}
