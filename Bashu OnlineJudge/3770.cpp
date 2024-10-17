#include<iostream>
#include<iomanip>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<queue>
using namespace std;
int maxx,map[105][105],dx[4]={0,1,-1,0},dy[4]={1,0,0,-1};
int bj[10005],vst[105][105],n,m;
int ryl(){
	char c=getchar();
	int r=0,z=1;
	while(c<'0'||c>'9'){if(c=='-')z=-1;c=getchar();}
	while(c>='0'&&c<='9')r=r*10+c-'0',c=getchar();
	return r*z;
}
bool dfs(int x,int y,int maxv,int dist){
//	if(maxv==17)cout<<x<<' '<<y<<" "<<maxv<<' '<<dist<<' '<<map[x][y]<<endl;
	vst[x][y]=maxv;
	if(x==n&&y==m)return 1;
	for(int i=0;i<4;i++){
		int X=x+dx[i],Y=y+dy[i];
		if(X<1||X>n||Y<1||Y>m||vst[X][Y]==maxv||map[X][Y]<maxv-dist||map[X][Y]>maxv)continue;
		if(dfs(X,Y,maxv,dist))return 1;
	}
	return 0;
}
bool get(int x){
	memset(vst,0,sizeof(vst));
	for(int i=0;i<=maxx;i++)if(bj[i]&&map[1][1]>=i&&map[1][1]<=i+x)if(dfs(1,1,i+x,x)){return 1;}
	return 0;
}
int main(){
	n=ryl();m=ryl();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)map[i][j]=ryl(),maxx=max(map[i][j],maxx),bj[map[i][j]]=1;
	int l=0,r=maxx,mid;
	//cout<<get(16)<<endl;
	while(l<r){
		mid=(l+r)/2;
		if(get(mid))r=mid;
		else l=mid+1;
	}
	cout<<l;
	return 0;
}
