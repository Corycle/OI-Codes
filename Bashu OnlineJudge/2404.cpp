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
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,cnt,Ans;
int h[N],a[N][N],b[N];
struct edge{int to,next;}d[N*2];
void Add(int x,int y){
	d[++cnt]=(edge){y,h[x]};
	h[x]=cnt;
}
void DFS(int x,int sum){
	if(sum>=Ans)return;
	if(x==0){Ans=min(Ans,sum);return;}
	if(a[x][x]){
		int val=a[x][n+1];
		for(int i=x+1;i<=n;i++){
			if(a[x][i])val^=b[i];
		}
		b[x]=val;DFS(x-1,sum+val);b[x]=0;
	}
	else{
		b[x]=0;DFS(x-1,sum);
		b[x]=1;DFS(x-1,sum+1);b[x]=0;
	}
}
int Gauss(int n){
	for(int i=1;i<=n;i++){
		int t=0;
		for(int j=i;j<=n;j++)if(a[j][i]){t=j;break;}
		if(!t)continue;swap(a[i],a[t]);
		for(int j=i+1;j<=n;j++){
			if(a[j][i])for(int k=i;k<=n+1;k++)a[j][k]^=a[i][k];
		}
	}
	Ans=inf;
	DFS(n,0);
	return Ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(1){
		memset(a,0,sizeof(a));
		n=read();if(!n)break;cnt=0;
		for(int i=1;i<=n;i++)h[i]=0;
		for(int i=1;i<=n;i++)a[i][i]=1;
		for(int i=1;i<=n;i++)a[i][n+1]=1;
		for(int i=2;i<=n;i++){
			int x=read(),y=read();
			a[x][y]=a[y][x]=1;
		}
		printf("%d\n",Gauss(n));
	}
	return 0;
}