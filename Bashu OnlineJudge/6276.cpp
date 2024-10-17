/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const double INF=1e30;
const double eps=1e-6;
const ll N=40005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,tot;
double Ans[N],K[N];
struct Line{double k;ll x,y;}L[N];
struct Node{double a,b,w;ll c;}P[N];
ll fcmp(double x){return (x>eps)?1:((x<-eps)?-1:0);}
bool operator==(Line A,Line B){return fcmp(A.k-B.k)==0;}
bool cmp1(Line A,Line B){
	if(fcmp(A.k-B.k)!=0)return A.k<B.k;
	return A.x==B.x?A.y<B.y:A.x<B.x;
}
bool cmp2(Node A,Node B){return A.w<B.w;}
struct Line_Chicken{//线性基 
	ll p[64];
	void Init(){memset(p,0,sizeof(p));}
	bool Insert(ll x){
		for(ll i=60;i>=0;i--){
			if((x>>i)&1){
				if(!p[i]){p[i]=x;break;}
				x^=p[i];if(!x)return false;
			}
		}
		return true;
	}
}Chicken;
void Update(){
	Chicken.Init();
	ll num=0;double sum1=0,sum2=1;
	for(ll i=1;i<=n;i++){
		if(Chicken.Insert(P[i].c)){
			sum1+=P[i].a;sum2*=exp(P[i].b);num++;
			Ans[num]=min(Ans[num],sum2*log(sum1)/log(2));
		}
	}
}
int main(){
//	freopen("minimization.in","r",stdin);
//	freopen("minimization.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<=n;i++)scanf("%lf",&P[i].a);
	for(ll i=1;i<=n;i++)scanf("%lf",&P[i].b);
	for(ll i=1;i<=n;i++)scanf("%lld",&P[i].c);
	for(ll i=1;i<=n;i++)P[i].b=log(P[i].b);
	for(ll i=1;i<=n;i++)Ans[i]=INF;
	for(ll i=1;i<=n;i++){
		for(ll j=i+1;j<=n;j++){
			double A=P[i].a-P[j].a;
			double B=P[i].b-P[j].b;
			if(fcmp(A)==0)L[++tot]=(Line){0,i,j};
			if(fcmp(B)==0)L[++tot]=(Line){inf,i,j};
			if(fcmp(A)&&fcmp(B))L[++tot]=(Line){A/B,i,j};
		}
	}
	L[++tot]=(Line){inf,0,0};
	L[++tot]=(Line){-inf,0,0};
	sort(L+1,L+tot+1,cmp1);
	tot=unique(L+1,L+tot+1)-L-1;
	for(ll i=2;i<=tot;i++){
		double k=(L[i-1].k+L[i].k)/2;
		for(ll j=1;j<=n;j++)P[j].w=P[j].a-k*P[j].b;
		sort(P+1,P+n+1,cmp2);Update();
	}
	while(m--){
		double ans=Ans[read()];
		if(fcmp(ans-INF)==0)printf("-1\n");
		else printf("%.5lf\n",ans);
	}
	return 0;
}