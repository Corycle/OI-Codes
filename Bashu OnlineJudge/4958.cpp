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
#define Point Vector
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,l0,l1,r0,r1;
int b[N],t[N],d[N],q0[N],q1[N],pre[N];
struct Vector{
	ll x,y;
	friend Vector operator+(Vector A,Vector B){return (Vector){A.x+B.x,A.y+B.y};}
	friend Vector operator-(Vector A,Vector B){return (Vector){A.x-B.x,A.y-B.y};}
	friend ll operator*(Vector A,Vector B){return A.x*B.x+A.y*B.y;}
	friend ll operator^(Vector A,Vector B){return A.x*B.y-A.y*B.x;}
}S,T,a[N],P[N];
ll Cross(Point A,Point B,Point C){return (A-C)^(B-C);}
bool cmp(int x,int y){return a[x].x<a[y].x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();T.x=read();T.y=read();
	for(int i=1;i<=n;i++){
		double alpha;b[i]=i;
		scanf("%lld%lld%lf",&a[i].x,&a[i].y,&alpha);
		double a1=atan2(S.y-a[i].y,S.x-a[i].x);
		double a2=atan2(T.y-a[i].y,T.x-a[i].x);
		t[i]=(a1<a2?(a1<alpha&&alpha<a2):(!(a2<alpha&&alpha<a1)));
	}
	sort(b+1,b+n+1,cmp);
	P[++tot]=S;
	for(int i=1;i<=n;i++){
		if(a[b[i]].x<S.x||a[b[i]].x>T.x)continue;
		P[++tot]=a[b[i]];d[tot]=t[b[i]];
	}
	P[++tot]=T;
	for(int i=1;i<=tot;i++){
		if(d[i]==0){
			if(l1<r1&&Cross(P[q1[l1]],P[q1[l1+1]],P[i])<=0){
				while(l1<r1&&Cross(P[q1[l1]],P[q1[l1+1]],P[i])<=0)l1++;
				q0[l0=r0=r0+1]=q1[l1];
				pre[i]=q1[l1];
			}
			else{
				while(l0<r0&&Cross(P[q0[r0]],P[q0[r0-1]],P[i])>=0)r0--;
				pre[i]=q0[r0];
			}
			q0[++r0]=i;
		}
		if(d[i]==1){
			if(l0<r0&&Cross(P[q0[l0]],P[q0[l0+1]],P[i])>=0){
				while(l0<r0&&Cross(P[q0[l0]],P[q0[l0+1]],P[i])>=0)l0++;
				q1[l1=r1=r1+1]=q0[l0];
				pre[i]=q0[l0];
			}
			else{
				while(l1<r1&&Cross(P[q1[r1]],P[q1[r1-1]],P[i])<=0)r1--;
				pre[i]=q1[r1];
			}
			q1[++r1]=i;
		}
	}
	double Ans=0;
	for(int i=tot;i>1;i=pre[i]){
		ll x=P[i].x-P[pre[i]].x;
		ll y=P[i].y-P[pre[i]].y;
		Ans+=sqrt(x*x+y*y);
	}
	printf("%.10lf",Ans);
	return 0;
}