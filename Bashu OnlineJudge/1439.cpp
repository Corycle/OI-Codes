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
#include<unordered_map>
#define ll long long
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const int Mul=1313131;
const int N=2e5+5;
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
map<ull,bool>vis;
ull P[N],Hash1[N],Hash2[N];
int n,m,tot,Max,a[N],Ans[N];
ull GetHash1(int l,int r){return Hash1[r]-Hash1[l-1]*P[r-l+1];}
ull GetHash2(int l,int r){return Hash2[l]-Hash2[r+1]*P[r-l+1];}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	P[0]=1;for(int i=1;i<=n;i++)P[i]=P[i-1]*Mul;
	for(int i=1;i<=n;i++)Hash1[i]=Hash1[i-1]*Mul+a[i];
	for(int i=n;i>=1;i--)Hash2[i]=Hash2[i+1]*Mul+a[i];
	for(int k=1;k<=n;k++){
		int num=0;vis.clear();
		for(int i=k;i<=n;i+=k){
			ull tmp=max(GetHash1(i-k+1,i),GetHash2(i-k+1,i));
			if(!vis[tmp]){vis[tmp]=1;num++;}
		}
		if(num>Max){Max=num;Ans[tot=1]=k;}
		else if(num==Max)Ans[++tot]=k;
	}
	printf("%d %d\n",Max,tot);
	for(int i=1;i<=tot;i++)printf("%d ",Ans[i]);
	return 0;
}