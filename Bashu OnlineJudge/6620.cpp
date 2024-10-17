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
const int inf=0x3f3f3f3f;
const double eps=1e-10;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,top,st[N];
double L,R,X[N],Y[N],Ans[N];
struct Node{double l,r;int id;};
int Sgn(double x){return x>eps?1:(x<-eps?-1:0);}
double Slope(int i,int j){return (double)(Y[i]-Y[j])/(X[i]-X[j]);}
double Calc(double M,int i){
	if(!i)return -inf;
	if(!Sgn(X[i]-M))return (R-L)+Y[i];
	return M<X[i]?(double)(R-X[i])*(R-L)/(R-M)+Y[i]:(double)(X[i]-L)*(R-L)/(M-L)+Y[i];
}
vector<Node>L1,L2;
void PrepareL(){
	double pos=X[1];st[top=1]=1;L1.push_back((Node){L,pos,0});
	for(int i=2;i<=n+1;i++){
		while(top>1&&Slope(st[top-1],st[top])<=(double)(R-L)/(L-X[i])){
			double tmp=L-(R-L)/Slope(st[top-1],st[top]);
			L1.push_back((Node){pos,tmp,st[top]});
			pos=tmp;top--;
		}
		L1.push_back((Node){pos,X[i],st[top]});
		pos=X[i];
		while(top>1&&Slope(st[top-1],st[top])<Slope(st[top],i))top--;
		if(!top||Slope(st[top],i)>(double)(R-L)/(L-X[i]))st[++top]=i;
	}
}
void PrepareR(){
	double pos=X[n];st[top=1]=n;L2.push_back((Node){pos,R,0});
	for(int i=n-1;i>=0;i--){
		while(top>1&&Slope(st[top-1],st[top])>=(double)(R-L)/(R-X[i])){
			double tmp=R-(R-L)/Slope(st[top-1],st[top]);
			L2.push_back((Node){tmp,pos,st[top]});
			pos=tmp;top--;
		}
		L2.push_back((Node){X[i],pos,st[top]});
		pos=X[i];
		while(top>1&&Slope(st[top-1],st[top])>Slope(st[top],i))top--;
		if(!top||Slope(st[top],i)<(double)(R-L)/(R-X[i]))st[++top]=i;
	}
	reverse(L2.begin(),L2.end());
}
void Update(double ql,double qr,int i,int j){
	double l=ql,r=qr;
	for(int T=60;T>=1;T--){
		double mid=(l+r)/2;
		if(Calc(mid,i)>Calc(mid,j))l=mid;
		else r=mid;
	}
	Ans[i]+=l-ql;Ans[j]+=qr-r;
}
void Solve(){
	double pos=L;
	int p1=0,p2=0;
	int num1=L1.size(),num2=L2.size();
	while(p1<num1&&p2<num2){
		if(L1[p1].r<L2[p2].r){
			Update(pos,L1[p1].r,L1[p1].id,L2[p2].id);
			pos=L1[p1++].r;
		}
		else{
			Update(pos,L2[p2].r,L1[p1].id,L2[p2].id);
			pos=L2[p2++].r;
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	read();n=read();L=read();R=read();
	for(int i=1;i<=n;i++)X[i]=read();
	for(int i=1;i<=n;i++)Y[i]=read();
	X[0]=L;X[n+1]=R;
	PrepareL();PrepareR();Solve();
	for(int i=1;i<=n;i++)printf("%.12lf\n",Ans[i]/(R-L));
	return 0;
}