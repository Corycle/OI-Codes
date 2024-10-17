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
int n,m,tp;
struct Point{
	double x,y;
}p1[105],p2[105],st[105];
double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
void Add(Point A,Point B,Point C,Point D){
	double s1=Cross(D,B,A);
	double s2=Cross(C,B,A);
	tp++;
	st[tp].x=(s1*C.x-s2*D.x)/(s1-s2);
	st[tp].y=(s1*C.y-s2*D.y)/(s1-s2);
}
void Cut(Point A,Point B){
	tp=0;
	p1[n+1]=p1[1];
	for(int i=1;i<=n;i++){
		if(Cross(p1[i],B,A)<=0){
			st[++tp]=p1[i];
			if(Cross(p1[i+1],B,A)>0)Add(p1[i],p1[i+1],A,B);
		}
		else if(Cross(p1[i+1],B,A)<0){
			Add(p1[i],p1[i+1],A,B);
		}
	}
	for(int i=1;i<=tp;i++)p1[i]=st[i];
	n=tp;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=0;
	while(1){
		T++;
		n=m=read();
		if(n==0)break;
		printf("Floor #%d\n",T);
		for(int i=n;i>=1;i--){
			p1[i].x=p2[i].x=read();
			p1[i].y=p2[i].y=read();
		}
		p2[m+1]=p2[1];
		for(int i=1;i<=m;i++){
			Cut(p2[i],p2[i+1]);
		}
		if(n)printf("Surveillance is possible.\n\n");
		else printf("Surveillance is impossible.\n\n");
	}
	return 0;
}