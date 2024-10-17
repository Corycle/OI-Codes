/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=55;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double Ans;
char a[N][N];
int dx[4]={0,1,0,-1};
int dy[4]={1,0,-1,0};
int n,m,p,vis[N][N][N];
double Dis(int x,int y){
	return sqrt(x*x+y*y);
}
void Update(int sx,int sy){
	queue<int>q1,q2,q3;
	memset(vis,0,sizeof(vis));
	q1.push(sx);q2.push(sy);q3.push(a[sx][sy]-'0');
	while(q1.size()){
		int x=q1.front(),y=q2.front(),t=q3.front();
		q1.pop();q2.pop();q3.pop();
		for(int i=0;i<4;i++){
			int fx=x+dx[i],fy=y+dy[i],ft=t+a[fx][fy]-'0';
			if(fx<1||fx>n||fy<1||fy>m||ft>p)continue;
			if(!vis[fx][fy][ft]){
				vis[fx][fy][ft]=1;
				q1.push(fx);q2.push(fy);q3.push(ft);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<=p;k++){
				if(!vis[i][j][k])continue;
				Ans=max(Ans,Dis(abs(i-sx),abs(j-sy)));
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();p=read();
	for(int i=1;i<=n;i++)scanf("%s",a[i]+1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			Update(i,j);
		}
	}
	printf("%.6lf",Ans);
	return 0;
}