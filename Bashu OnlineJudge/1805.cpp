#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const double eps=1e-12;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,st,ed;
int flag[N];
double cl[N],cr[N];
struct Circle{double x,y,r;}c[N],t[N];
struct Line{double l,r;}p[N];
bool cmp1(Circle A,Circle B){
	return A.r<B.r;
}
bool cmp2(Circle A,Circle B){
	return A.x-A.r<B.x-B.r;
}
bool cmp3(Line A,Line B){
	return A.l<B.l;
}
double Sqr(double x){return x*x;}
double Dist(Circle A,Circle B){
	return sqrt(Sqr(A.x-B.x)+Sqr(A.y-B.y));
}
double Ask(double x){
	int tot=0;
	double len=0,dis=0;
	for(int i=st;i<=ed;i++){
		if(x<=cl[i]||x>=cr[i])continue;
		dis=sqrt(Sqr(c[i].r)-Sqr(x-c[i].x));
		p[++tot]=(Line){c[i].y-dis,c[i].y+dis};
	}
	sort(p+1,p+tot+1,cmp3);
	for(int i=1;i<=tot;i++){
		int j;double R=p[i].r;
		for(j=i+1;j<=tot;j++){
			if(p[j].l>R)break;
			if(p[j].r>R)R=p[j].r;
		}
		len+=R-p[i].l;i=j-1;
	}
	return len;
}
double F(double L,double fl,double fmid,double fr){
	return (fl+fmid*4+fr)*L/6;
}
double Simpson(double L,double mid,double R,double fl,double fmid,double fr,double s){
	double m1=(L+mid)/2,m2=(R+mid)/2;
	double f1=Ask(m1),f2=Ask(m2);
	double s1=F(mid-L,fl,f1,fmid);
	double s2=F(R-mid,fmid,f2,fr);
	if(fabs(s1+s2-s)<eps)return s1+s2;
	return Simpson(L,m1,mid,fl,f1,fmid,s1)+Simpson(mid,m2,R,fmid,f2,fr,s2);
}
double Solve(){
	double ans=0;
	for(int i=1;i<=n;i++){
		cl[i]=c[i].x-c[i].r;
		cr[i]=c[i].x+c[i].r;
	}
	for(int i=1;i<=n;i++){
		int j;st=i;ed=i;
		double L=cl[i],R=cr[i];
		for(j=i+1;j<=n;j++){
			if(cl[j]>R)break;
			if(cr[j]>R)R=cr[j];
		}
		double mid=(L+R)/2;ed=i=j-1;
		double fl=Ask(L),fr=Ask(R),fmid=Ask(mid);
		ans+=Simpson(L,mid,R,fl,fmid,fr,F(R-L,fl,fmid,fr));
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",&t[i].x,&t[i].y,&t[i].r);
	}
	sort(t+1,t+n+1,cmp1);
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(Dist(t[i],t[j])<=t[j].r-t[i].r){//内含 
				flag[i]=1;break;
			}
		}
	}
	int num=0;
	for(int i=1;i<=n;i++){
		if(!flag[i])c[++num]=t[i];
	}
	n=num;
	sort(c+1,c+n+1,cmp2);
	printf("%.3lf",Solve());
	return 0;
}