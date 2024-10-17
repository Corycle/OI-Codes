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
//#define eps 1e-9
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
const double eps=1e-9;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,top,st[N];
double f[N];
struct Point{
	double x,y,a,b,k,rate;
	int id;
}p[N],t[N];
bool cmp(Point x,Point y){
	return x.k>y.k;
}
double K(int x,int y){
	if(!y)return -1e20;
	if(fabs(p[x].x-p[y].x)<eps)return 1e20;
	return (p[y].y-p[x].y)/(p[y].x-p[x].x);
}
void CDQ(int l,int r){
	if(l==r){
		f[l]=max(f[l],f[l-1]);
		p[l].y=f[l]/(p[l].a*p[l].rate+p[l].b);
		p[l].x=p[l].rate*p[l].y;
		return;
	}
	int mid=(l+r)>>1;
	int i=l,j=mid+1,tp=1;
	for(int k=l;k<=r;k++){
		if(p[k].id<=mid)t[i++]=p[k];
		else t[j++]=p[k];
	}
	for(int k=l;k<=r;k++)p[k]=t[k];
	CDQ(l,mid);
	top=0;
	for(int k=l;k<=mid;k++){
		while(top>1&&K(st[top-1],st[top])<K(st[top],k)+eps)top--;
		st[++top]=k;
	}
	st[++top]=0;
	for(int k=mid+1;k<=r;k++){
		while(tp<top&&K(st[tp],st[tp+1])+eps>p[k].k)tp++;
		f[p[k].id]=max(f[p[k].id],p[st[tp]].x*p[k].a+p[st[tp]].y*p[k].b);
	}
	CDQ(mid+1,r);
	i=l;j=mid+1;
	int len=l;
	while(i<=mid&&j<=r){
		if(p[i].x<p[j].x||(fabs(p[i].x-p[j].x)<eps&&p[i].y<p[j].y))t[len++]=p[i++];
		else t[len++]=p[j++];
	}
	while(i<=mid)t[len++]=p[i++];
	while(j<=r)t[len++]=p[j++];
	for(int k=l;k<=r;k++)p[k]=t[k];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%d%lf",&n,&f[0]);
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",&p[i].a,&p[i].b,&p[i].rate);
		p[i].k=-p[i].a/p[i].b;
		p[i].id=i;
	}
	sort(p+1,p+n+1,cmp);
	CDQ(1,n);
	printf("%.3lf",f[n]);
	return 0;
}
/*
3 100       
1 1 1
1 2 2 
2 2 3
*/