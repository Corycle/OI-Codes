#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Ans,topa,topb,suma,sumb;
int a[N],b[N],t[N],sa[N],sb[N],flag[N];
bool cmpa(int x,int y){
	return b[x]==b[y]?a[x]<a[y]:b[x]>b[y];
}
bool cmpb(int x,int y){
	return a[x]==a[y]?b[x]<b[y]:a[x]>a[y];
}
int Rand(int maxx){
	return rand()%maxx+1;
}
int Ask(){
	int ans=0;
	suma=sumb=0;
	for(int i=1;i<=topa;i++)suma+=a[sa[i]];
	for(int i=1;i<=topb;i++){
		sumb+=b[sb[i]];
		if(suma>sumb)suma+=a[sb[i]];
		else suma=sumb+a[sb[i]];
	}
	ans=max(suma,sumb);
	suma=sumb=0;
	for(int i=1;i<=topb;i++)sumb+=b[sb[i]];
	for(int i=1;i<=topa;i++){
		suma+=a[sa[i]];
		if(sumb>suma)sumb+=b[sa[i]];
		else sumb=suma+b[sa[i]];
	}
	return max(ans,max(suma,sumb));
}
void Solve(){
	topa=topb=0;
	for(int i=1;i<=n;i++){
		if(flag[i]==1)sa[++topa]=i;
		if(flag[i]==2)sb[++topb]=i;
	}
	sort(sa+1,sa+topa+1,cmpa);
	sort(sb+1,sb+topb+1,cmpb);
	int res=Ask();
	for(int i=1;i<=N;i++){
		int a1=0,a2=0,b1=0,b2=0;
		if(topa)swap(sa[a1=Rand(topa)],sa[a2=Rand(topa)]);
		if(topb)swap(sb[b1=Rand(topb)],sb[b2=Rand(topb)]);
		int now=Ask();
		if(now<res)res=min(res,now);
		else{
			if(a1&&a2)swap(sa[a1],sa[a2]);
			if(b1&&b2)swap(sb[b1],sb[b2]);
		}
	}
	Ans=min(Ans,res);
}
void DFS(int depth){
	if(depth==n+1)Solve();
	else{
		if(t[depth]==1){flag[depth]=1;DFS(depth+1);}
		if(t[depth]==2){flag[depth]=2;DFS(depth+1);}
		if(t[depth]==3){
			flag[depth]=1;DFS(depth+1);
			flag[depth]=2;DFS(depth+1);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();Ans=inf;
	srand(time(NULL));
	for(int i=1;i<=n;i++){
		t[i]=read();
		a[i]=read();
		b[i]=read();
	}
	DFS(1);
	printf("%d",Ans);
	return 0;
}