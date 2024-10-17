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
const int N=405;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,s,t,a[N][N];
struct Edge{int x,y;}E[N*N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();s=read();t=read();
	memset(a,0x3f,sizeof(a));
	for(int i=1;i<=n;i++)a[i][i]=0;
	for(int i=1;i<=m;i++){int x=read(),y=read();E[i]=(Edge){x,y};a[x][y]=a[y][x]=1;}
	for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
	cout<<a[s][t]<<'\n';
	for(int i=1;i<=m;i++)cout<<min(a[s][t],max(a[s][E[i].x],a[s][E[i].y]))<<'\n';
	return 0;
}