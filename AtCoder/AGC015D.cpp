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
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll L,R,Lim,cnt,Ans,dlt;
struct Line{ll l,r;}P[10];
bool cmp(Line A,Line B){return A.l!=B.l?A.l<B.l:A.r<B.r;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	L=read();R=read();Lim=-1;
	for(int i=60;i>=0;i--){
		int x=(L>>i)&1,y=(R>>i)&1;
		if(x==y&&Lim==-1){if(x)dlt+=(1ll<<i);continue;}
		if(Lim==-1){Lim=i;P[++cnt]=(Line){L-dlt+(1ll<<Lim),(1ll<<(Lim+1))-1};}
		else if(y==1){P[++cnt]=(Line){1ll<<Lim,(1ll<<Lim)+(1ll<<(i+1))-1};break;}
	}
	P[++cnt]=(Line){L-dlt,R-dlt};
	sort(P+1,P+cnt+1,cmp);
	ll l=P[1].l,r=P[1].r;
	for(int i=2;i<=cnt;i++){
		if(P[i-1].r>=P[i].l)r=max(r,P[i].r);
		else{Ans+=r-l+1;l=P[i].l;r=P[i].r;}
	}
	Ans+=r-l+1;
	printf("%lld\n",Ans);
	return 0;
}
