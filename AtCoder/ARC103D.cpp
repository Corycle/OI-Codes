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
const ll inf=0x3f3f3f3f;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char Ans[N][40];
ll n,m,a[N],flag[2];
struct Node{ll x,y;}P[N];
void Solve(ll d){
	a[++m]=d;
	for(ll i=1;i<=n;i++){
		if(abs(P[i].x)>abs(P[i].y)){
			Ans[i][m]=(P[i].x<0?'L':'R');
			P[i].x=(P[i].x<0?P[i].x+d:P[i].x-d);
		}
		else{
			Ans[i][m]=(P[i].y<0?'D':'U');
			P[i].y=(P[i].y<0?P[i].y+d:P[i].y-d);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(ll i=1;i<=n;i++){
		P[i].x=read();P[i].y=read();
		flag[(abs(P[i].x)+abs(P[i].y))&1]=1;
	}
	if(flag[0]&&flag[1]){puts("-1");return 0;}
	for(ll i=30;i>=0;i--)Solve(1<<i);
	if(flag[0])Solve(1);
	printf("%lld\n",m);
	for(ll i=1;i<=m;i++)printf("%lld ",a[i]);puts("");
	for(ll i=1;i<=n;i++)printf("%s\n",Ans[i]+1);
	return 0;
}
