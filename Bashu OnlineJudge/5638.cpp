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
const ll inf=0x3f3f3f3f;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,Q,tot,top,st[N];
struct Vector{
	ll x,y;
	friend Vector operator+(Vector A,Vector B){return (Vector){A.x+B.x,A.y+B.y};}
	friend Vector operator-(Vector A,Vector B){return (Vector){A.x-B.x,A.y-B.y};}
	friend Vector operator*(Vector A,ll B){return (Vector){A.x*B,A.y*B};}
	friend Vector operator/(Vector A,ll B){return (Vector){A.x/B,A.y/B};}
	friend ll operator*(Vector A,Vector B){return A.x*B.x+A.y*B.y;}
	friend ll operator^(Vector A,Vector B){return A.x*B.y-A.y*B.x;}
}a[N],b[N],c[N],s1[N],s2[N],S;
ll Sqr(ll x){return x*x;}
ll len(Vector A){return sqrt(Sqr(A.x)+Sqr(A.y));}
ll Cross(Point A,Point B,Point C){return (A-C)^(B-C);}
bool cmp(Point A,Point B){
	return Cross(A,B,S)!=0?Cross(A,B,S)>0:len(A-S)<len(B-S);
}
void Convex(Vector a[],ll &n){
	ll id=0,Minx=inf,Miny=inf;
	for(ll i=1;i<=n;i++){
		if(a[i].y<Miny||(a[i].y==Miny&&a[i].x<Minx)){
			Minx=a[i].x;Miny=a[i].y;id=i;
		}
	}
	S=a[id];
	swap(a[1],a[id]);
	sort(a+2,a+n+1,cmp);
	top=2;st[1]=1;st[2]=2;
	for(ll i=3;i<=n;i++){
		while(top>=2&&Cross(a[i],a[st[top]],a[st[top-1]])>=0)top--;
		st[++top]=i;
	}
	for(ll i=1;i<=top;i++)a[i]=a[st[i]];
	n=top;
}
void Minkowski(){
	a[n+1]=a[1];b[m+1]=b[1];
	for(ll i=1;i<=n;i++)s1[i]=a[i+1]-a[i];
	for(ll i=1;i<=m;i++)s2[i]=b[i+1]-b[i];
	ll p1=1,p2=1;c[tot=1]=a[1]+b[1];
	while(p1<=n&&p2<=m){tot++;c[tot]=c[tot-1]+((s1[p1]^s2[p2])>=0?s1[p1++]:s2[p2++]);}
	while(p1<=n){tot++;c[tot]=c[tot-1]+s1[p1++];}
	while(p2<=m){tot++;c[tot]=c[tot-1]+s2[p2++];}
}
int Query(Point A){
	S.x=S.y=0;
	if((A^c[1])>0||(c[tot]^A)>0)return 0;
	ll pos=lower_bound(c+1,c+tot+1,A,cmp)-c-1;
	return ((A-c[pos])^(c[pos%tot+1]-c[pos]))<=0;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Q=read();
	for(ll i=1;i<=n;i++){a[i].x=read();a[i].y=read();}
	for(ll i=1;i<=m;i++){b[i].x=-read();b[i].y=-read();}
	Convex(a,n);Convex(b,m);
	Minkowski();Convex(c,tot);
	Vector St=c[1];
	for(ll i=tot;i>=1;i--)c[i]=c[i]-c[1];
	while(Q--){ll x=read(),y=read();printf("%d\n",Query((Point){x,y}-St));}
	return 0;
}