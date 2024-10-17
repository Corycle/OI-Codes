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
const int Mod=1000000007;
const int Inv2=500000004;
const int Inv4=250000002;
const int M=65537;
const int N=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int sta[N];
int n,m,tot,Sta;
map<int,int>F[M];
struct edge{int x,y,val;}e[M];
int lowbit(int x){return x&(-x);}
bool Check(int x,int y){return (x|y)==y;}
int DFS(int S,int T){
	if(!S||!T)return 1;
	if(F[S][T])return F[S][T];
	int ans=0;
	for(int i=1;i<=tot;i++){
		if(Check(e[i].x,S)&&Check(e[i].y,T)&&(e[i].x&lowbit(S))){
			ans=(ans+1ll*e[i].val*DFS(S^e[i].x,T^e[i].y)%Mod)%Mod;
		}
	}
	return F[S][T]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Sta=(1<<n)-1;
	for(int i=1;i<=n;i++)sta[i]=1<<(i-1);
	for(int i=1;i<=m;i++){
		int op=read();
		int sx=read(),sy=read();
		e[++tot]=(edge){sta[sx],sta[sy],Inv2};
		if(op!=0){
			int tx=read(),ty=read();
			e[++tot]=(edge){sta[tx],sta[ty],Inv2};
			if(sx==tx||sy==ty)continue;
			if(op==1)e[++tot]=(edge){sta[sx]|sta[tx],sta[sy]|sta[ty],Inv4};
			if(op==2)e[++tot]=(edge){sta[sx]|sta[tx],sta[sy]|sta[ty],Mod-Inv4};
		}
	}
	printf("%lld",1ll*(1<<n)*DFS(Sta,Sta)%Mod);
	return 0;
}