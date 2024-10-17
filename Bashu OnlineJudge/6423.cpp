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
const int Mod=1e7+19;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Q,val,Add,Mul,Sum,Ans,Tim;
int a[N],b[N],p[N],t[N],v[N],inv[N*100];
struct Ques{int op,x,y;}P[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Prepare(int maxn){
	inv[0]=inv[1]=1;
	for(int i=2;i<maxn;i++)inv[i]=1ll*inv[Mod%i]*(Mod-Mod/i)%Mod;
}
void Update(int i,int num){
	if(P[i].op==1){
		int x=t[P[i].x]<=Tim?0:P[i].x;
		Sum=mod(mod(Sum-mod(1ll*v[x]*Mul%Mod+Add)+Mod)+P[i].y);
		v[P[i].x]=1ll*mod(P[i].y-Add+Mod)*inv[Mul]%Mod;
		t[P[i].x]=num;
	}
	if(P[i].op==2){Sum=mod(Sum+1ll*n*P[i].x%Mod);Add=mod(Add+P[i].x);}
	if(P[i].op==3){Sum=1ll*Sum*P[i].x%Mod;Add=1ll*Add*P[i].x%Mod;Mul=1ll*Mul*P[i].x%Mod;}
	if(P[i].op==4){Sum=1ll*n*P[i].x%Mod;Add=0;Mul=1;Tim=num;v[0]=P[i].x;}
	if(P[i].op==5){
		int x=t[P[i].x]<=Tim?0:P[i].x;
		Ans=mod(Ans+mod(1ll*v[x]*Mul%Mod+Add));
	}
	if(P[i].op==6)Ans=mod(Ans+Sum);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Q=read();Prepare(Mod);
	for(int i=1;i<=Q;i++){
		P[i].op=read();
		if(P[i].op!=6)P[i].x=read();
		if(P[i].op==1)P[i].y=(read()%Mod+Mod)%Mod;
		else if(P[i].op<=4)P[i].x=(P[i].x%Mod+Mod)%Mod;
		if(P[i].op==1||P[i].op==5)p[++p[0]]=P[i].x;
		if(P[i].op==3&&P[i].x==0)P[i].op=4;
	}
	sort(p+1,p+p[0]+1);p[0]=unique(p+1,p+p[0]+1)-p-1;
	for(int i=1;i<=Q;i++){
		if(P[i].op==1||P[i].op==5)P[i].x=lower_bound(p+1,p+p[0]+1,P[i].x)-p;
	}
	m=read();Add=0;Mul=1;
	for(int i=1;i<=m;i++){a[i]=read();b[i]=read();}
	for(int i=1;i<=m*Q;i++){
		int x=(i-1)/Q+1,y=(i-1)%Q+1;
		Update((a[x]+1ll*y*b[x])%Q+1,i);
	}
	printf("%d",(Ans%Mod+Mod)%Mod);
	return 0;
}