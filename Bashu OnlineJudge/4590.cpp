/*====KEKE_046====*/
//O(N^2)->100
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
const long double inf=1e30;
const long double eps=1e-25;
const int maxn=20005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct point{ll x,y;int id;bool operator < (const point &t)const{return x<t.x||(x==t.x&&y<t.y);}};
ll cross(point W,point A,point B){A.x-=W.x;A.y-=W.y;B.x-=W.x;B.y-=W.y;return A.x*B.y-B.x*A.y;}

point dat[maxn],sta[maxn];
int lis[maxn],ln,top,N;

int main(){
	N=read();
	for(int i=1;i<=N;i++)dat[i].id=i;
	for(int i=1;i<=N;i++)dat[i].y=read();
	for(int i=1;i<=N;i++)dat[i].x=read();
	sort(dat+1,dat+N+1);
	for(int i=1;i<=N;i++){
		while(top>1&&cross(sta[top-1],sta[top],dat[i])>0)top--;
		sta[++top]=dat[i];
	}
	sta[top+1].y=-1e18;
	for(int i=1;i<=top;i++){
		if(sta[i].y>=sta[i+1].y)lis[++ln]=sta[i].id;
	}
	sort(lis+1,lis+ln+1);cout<<ln<<'\n';
	for(int i=1;i<=ln;i++)cout<<lis[i]<<' ';
	return 0;
}
/*====Corycle====*/
//O(NlogN)->(90) 
/*
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
const long double inf=1e30;
const long double eps=1e-25;
const int N=20005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,Ans[N];
struct Point{long double x,y;};
struct Line{Point A,B;long double ang;int id;}a[N],Q[N],Deque[N];
long double Cross(Point A,Point B,Point C){
	return (A.x-C.x)*(B.y-C.y)-(A.y-C.y)*(B.x-C.x);
}
bool cmp(Line A,Line B){
	return fabs(A.ang-B.ang)>eps?A.ang<B.ang:Cross(B.A,B.B,A.A)>eps;
}
Point AddCross(Point A,Point B,Point C,Point D){
	Point P;
	long double s1=Cross(D,B,A);
	long double s2=Cross(C,B,A);
	P.x=(s1*C.x-s2*D.x)/(s1-s2);
	P.y=(s1*C.y-s2*D.y)/(s1-s2);
	return P;
}
void AddLine(long double A,long double B,long double C,long double D,int id){
	a[++tot].id=id;
	a[tot].A=(Point){A,B};
	a[tot].B=(Point){C,D};
	a[tot].ang=atan2(D-B,C-A);
}
bool Check(Line A,Line B,Line C){
	Point P=AddCross(B.A,B.B,C.A,C.B);
	return Cross(A.A,A.B,P)<-eps;
}
void Solve(){
	sort(a+1,a+tot+1,cmp);
	Q[++m]=a[1];
	for(int i=2;i<=tot;i++){
		if(a[i].ang-a[i-1].ang>eps)Q[++m]=a[i];
	}
	int l=0,r=1;Deque[0]=Q[1];Deque[1]=Q[2];
	for(int i=3;i<=m;i++){
		while(l<r&&Check(Q[i],Deque[r-1],Deque[r]))r--;
		while(l<r&&Check(Q[i],Deque[l+1],Deque[l]))l++;
		Deque[++r]=Q[i];
	}
	while(l<r&&Check(Deque[l],Deque[r-1],Deque[r]))r--;
	while(l<r&&Check(Deque[r],Deque[l+1],Deque[l]))l++;
	for(int i=l;i<=r;i++)if(Deque[i].id)Ans[++Ans[0]]=Deque[i].id;
}
int k[N],b[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int n=read();
	AddLine(0,0,inf,0,0);
	AddLine(inf,0,inf,inf,0);
	AddLine(inf,inf,0,inf,0);
	AddLine(0,inf,0,0,0);
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++)k[i]=read();
	for(int i=1;i<=n;i++){
		AddLine(0,b[i],1,k[i]+b[i],i);
	}
	Solve();
	sort(Ans+1,Ans+Ans[0]+1);
	printf("%d\n",Ans[0]);
	for(int i=1;i<=Ans[0];i++)printf("%d ",Ans[i]);
	return 0;
}
*/