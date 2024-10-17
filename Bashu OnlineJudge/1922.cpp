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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double ans;
int fa[205],cnt,sum;
struct Point{
	int x,y;
}p[205],l[105][2];
struct edge{
	int s,t;
	double data;
}d[40005];
bool cmp(edge x,edge y){
	return x.data<y.data;
}
int Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
int Ask(Point A,Point B,Point C,Point D){
	return (Cross(C,D,A)*Cross(C,D,B)<0)&&(Cross(A,B,C)*Cross(A,B,D)<0);
}
int Check(int x,int y){
	for(int i=1;i<=m;i++){
		if(Ask(l[i][0],l[i][1],p[x],p[y]))return 0;
	}
	return 1;
}
double Dist(Point A,Point B){
	return sqrt((A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y));
}
void Make_edge(){
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(!Check(i,j))continue;
			d[++cnt]=(edge){i,j,Dist(p[i],p[j])};
		}
	}
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
int MST(){
	sort(d+1,d+cnt+1,cmp);
	for(int i=1;i<=cnt;i++){
		int x=Find(d[i].s),y=Find(d[i].t);
		if(x==y)continue;
		ans+=d[i].data;
		fa[x]=y;
		sum++;
		if(sum==n-1)return 1;
	}
	return 0;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		fa[i]=i;
		p[i].x=read();
		p[i].y=read();
	}
	m=read();
	for(int i=1;i<=m;i++){
		l[i][0].x=read();
		l[i][0].y=read();
		l[i][1].x=read();
		l[i][1].y=read();
	}
	Make_edge();
	if(MST())printf("%.3lf",ans);
	else printf("-1.000");
	return 0;
}