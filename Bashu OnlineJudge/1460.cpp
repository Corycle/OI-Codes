#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-8;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
struct Point{
	int x,y;
}p1[N],p2[N];
int visx[N],visy[N],p[N];
double lx[N],ly[N],w[N][N];
double Dist(Point A,Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
bool DFS(int x){
	visx[x]=1;
	for(int y=1;y<=n;y++){
		if(!visy[y]&&(lx[x]+ly[y]-w[x][y]<=eps)){
			visy[y]=1;
			if(!p[y]||DFS(p[y])){
				p[y]=x;
				return true;
			}
		}
	}
	return false;
}
void Adjust(){
	double d=inf;
	for(int i=1;i<=n;i++){
		if(!visx[i])continue;
		for(int j=1;j<=n;j++){
			if(!visy[j])d=min(d,lx[i]+ly[j]-w[i][j]);
		}
	}
	for(int i=1;i<=n;i++){
		if(visx[i])lx[i]-=d;
		if(visy[i])ly[i]+=d;
	}
}
void KM(){
	for(int i=1;i<=n;i++){
		lx[i]=-inf;
		ly[i]=0;
		for(int j=1;j<=n;j++){
			lx[i]=max(lx[i],w[i][j]);
		}
	}
	memset(p,0,sizeof(p));
	for(int i=1;i<=n;i++){
		while(1){
			memset(visx,0,sizeof(visx));
			memset(visy,0,sizeof(visy));
			if(DFS(i))break;
			Adjust();
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){p1[i].x=read();p1[i].y=read();}
	for(int i=1;i<=n;i++){p2[i].x=read();p2[i].y=read();}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			w[i][j]=-Dist(p1[i],p2[j]);
		}
	}
	KM();
	double ans=0;
	for(int i=1;i<=n;i++){
		if(p[i])ans-=w[p[i]][i];
	}
	printf("%.3lf",ans);
	return 0;
}