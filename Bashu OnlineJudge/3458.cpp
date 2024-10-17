/*====Corycle====*/
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
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
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
vector<int>G[N];
int n,m,F[N],sum[N];
bool DFS(int x,int fa,int K){
	int num=0;sum[x]=1;
	for(auto y:G[x]){
		if(y==fa)continue;
		if(!DFS(y,x,K))return false;
		sum[x]+=sum[y];
	}
	for(auto y:G[x]){
		if(y==fa)continue;
		if(sum[y]%K){
			if(F[K-sum[y]%K]){F[K-sum[y]%K]--;num--;}
			else{F[sum[y]%K]++;num++;}
		}
	}
	for(auto y:G[x])F[sum[y]%K]=0;
	return (num<=1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);}
	for(int i=1;i<n;i++)printf("%d",((n-1)%i)?0:DFS(1,0,i));
	return 0;
}
