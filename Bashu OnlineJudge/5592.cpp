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
using namespace std;
const double inf=9e18;
const double eps=1e-12;
const int N=250005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double Ans[N];
int n,tot,pos[N];
struct Line{double k;int x,y;}L[N];
struct Node{double a,b,p,w;int id;}P[N];
bool cmp1(Line A,Line B){return A.k<B.k;}
bool cmp2(Node A,Node B){return A.w<B.w;}
int Sgn(double x){
	if(x>eps)return 1;
	if(x<-eps)return -1;
	return 0;
}
void Update(){
	double Sum1=0,Sum2=1;
	for(int i=1;i<=n;i++){
		Sum1+=P[i].a;
		Sum2*=P[i].b;
		Ans[i]=min(Ans[i],Sum1*Sum2);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)Ans[i]=inf;
	for(int i=1;i<=n;i++)P[i].a=read();
	for(int i=1;i<=n;i++)P[i].b=read()/1e5;
	for(int i=1;i<=n;i++)P[i].p=log(P[i].b);
	for(int i=1;i<=n;i++){
		P[i].id=i;
		for(int j=i+1;j<=n;j++){
			double B=P[i].p-P[j].p;
			double A=P[i].a-P[j].a;
			if(!Sgn(B))L[++tot]=(Line){0,i,j};
			if(!Sgn(A))L[++tot]=(Line){inf,i,j};
			if(Sgn(A)&&Sgn(B))L[++tot]=(Line){B/A,i,j};
		}
	}
	sort(L+1,L+tot+1,cmp1);
	for(int i=1;i<=n;i++)P[i].w=P[i].p-P[i].a*(-inf);
	sort(P+1,P+n+1,cmp2);
	Update();
	for(int i=1;i<=n;i++)pos[P[i].id]=i;
	for(int i=1;i<=tot;i++){
		int x=L[i].x,y=L[i].y;
		swap(P[pos[x]],P[pos[y]]);
		swap(pos[x],pos[y]);
		Update();
	}
	for(int i=1;i<=n;i++)printf("%.10lf ",Ans[i]);
	return 0;
}