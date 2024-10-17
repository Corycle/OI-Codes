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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const double Pi=acos(-1);
const double eps=1e-8;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
struct Point{double x,y;}P[N];
struct Matrix{
	double a[3][3];
	void Init(){memset(a,0,sizeof(a));}
	friend Matrix operator*(Matrix A,Matrix B){
		Matrix C;C.Init();
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				for(int k=0;k<3;k++){
					C.a[i][j]+=A.a[i][k]*B.a[k][j];
				}
			}
		}
		return C;
	}
	void Print(){
		cout<<"========"<<endl;
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				cout<<a[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<"========"<<endl;
	}
}E,Delta,A[N];
struct Segment_Tree{
	Matrix t[N*4];
	void Pushdown(int p){
		t[p<<1]=t[p<<1]*t[p];
		t[p<<1|1]=t[p<<1|1]*t[p];
		t[p]=E;
	}
	void Build(int p,int l,int r){
		t[p]=E;
		if(l==r)return;
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
	}
	void Update(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){t[p]=t[p]*Delta;return;}
		int mid=(l+r)>>1;Pushdown(p);
		Update(x,y,lson);Update(x,y,rson);
	}
	void Query(int p,int l,int r){
		if(l==r){A[l]=t[p];return;}
		int mid=(l+r)>>1;Pushdown(p);
		Query(lson);Query(rson);
	}
}tree;
void GetMatrix_M(){
	double p=0,q=0;scanf("%lf%lf",&p,&q);
	Delta.a[0][0]=1;Delta.a[1][1]=1;
	Delta.a[2][0]=p;Delta.a[2][1]=q;
}
void GetMatrix_X(){Delta.a[0][0]=1;Delta.a[1][1]=-1;}
void GetMatrix_Y(){Delta.a[0][0]=-1;Delta.a[1][1]=1;}
void GetMatrix_O(){Delta.a[0][1]=1;Delta.a[1][0]=1;}
void GetMatrix_R(){
	double a=0;scanf("%lf",&a);a=a/180*Pi;
	Delta.a[0][0]=cos(a);Delta.a[0][1]=sin(a);
	Delta.a[1][0]=-sin(a);Delta.a[1][1]=cos(a);
}
int main(){
//	freopen("madrid.in","r",stdin);
//	freopen("madrid.out","w",stdout);
	n=read();
	E.a[0][0]=E.a[1][1]=E.a[2][2]=1;
	for(int i=1;i<=n;i++){
		scanf("%lf%lf",&P[i].x,&P[i].y);
	}
	tree.Build(1,1,n);
	char op[5];m=read();
	while(m--){
		scanf("%s",op);
		Delta.Init();
		Delta.a[2][2]=1;
		int l=read(),r=read();
		if(op[0]=='M')GetMatrix_M();
		if(op[0]=='X')GetMatrix_X();
		if(op[0]=='Y')GetMatrix_Y();
		if(op[0]=='O')GetMatrix_O();
		if(op[0]=='R')GetMatrix_R();
		tree.Update(l,r,1,1,n);
//		Delta.Print();
	}
	tree.Query(1,1,n);
	for(int i=1;i<=n;i++){
		double x=P[i].x*A[i].a[0][0]+P[i].y*A[i].a[1][0]+A[i].a[2][0];
		double y=P[i].x*A[i].a[0][1]+P[i].y*A[i].a[1][1]+A[i].a[2][1];
		printf("%.2lf %.2lf\n",x,y);
	}
	return 0;
}