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
#include<set>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=998244353;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
set<int>G[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		if(x>y)swap(x,y);
		G[x].insert(y);
	}
	int Ans=1;
	for(int x=1;x<=n;x++){
		Ans=1ll*Ans*(n-G[x].size())%Mod;
		int y=*G[x].begin();G[x].erase(y);
		if(G[x].size()<G[y].size()){
			for(auto t:G[x])G[y].insert(t);
			G[x].clear();
		}
		else{
			for(auto t:G[y])G[x].insert(t);
			G[y].clear();swap(G[x],G[y]);
		}
	}
	printf("%d",Ans);
	return 0;
}