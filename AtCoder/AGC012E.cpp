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
#define pii pair<int,int>
#define fst first
#define scd second
#define mp make_pair
using namespace std;
const int inf=0x3f3f3f3f;
const int Maxn=(1<<19)+5;
const int N=2e5+5;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
pii P[N];
int n,V,cnt,tot,Sta,a[N],L[M][N],R[M][N],Ans[N],FL[Maxn],FR[Maxn];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();V=read();
	for(int i=1;i<=n;i++)a[i]=read();a[0]=-inf;a[n+1]=inf;
	for(int v=V;;v>>=1){
		tot++;L[tot][0]=0;R[tot][n+1]=n+1;
		for(int i=1;i<=n;i++)L[tot][i]=(a[i]-a[i-1]<=v?L[tot][i-1]:i);
		for(int i=n;i>=1;i--)R[tot][i]=(a[i+1]-a[i]<=v?R[tot][i+1]:i);
		if(v==0)break;
	}
	Sta=(1<<tot)-1;
	for(int i=1;i<=n;i++)P[i]=mp(L[1][i],R[1][i]);
	sort(P+1,P+n+1);cnt=unique(P+1,P+n+1)-P-1;
	for(int S=0;S<=Sta;S++){FL[S]=0;FR[S]=n+1;}
	for(int S=0;S<=Sta;S+=2){
		for(int i=1;i<=tot;i++){
			if(!((S>>(i-1))&1))continue;
			FL[S]=max(FL[S],R[i][FL[S^(1<<(i-1))]+1]);
			FR[S]=min(FR[S],L[i][FR[S^(1<<(i-1))]-1]);
		}
	}
	if(cnt>tot){for(int i=1;i<=tot;i++)puts("Impossible");return 0;}
	for(int i=1;i<=cnt;i++){
		for(int S=0;S<=Sta;S+=2){
			if(FL[S]>=P[i].fst-1&&FR[Sta^S^1]<=P[i].scd+1){
				for(int j=P[i].fst;j<=P[i].scd;j++)Ans[j]=1;
				break;
			}
		}
	}
	for(int i=1;i<=n;i++)puts(Ans[i]?"Possible":"Impossible");
	return 0;
}
