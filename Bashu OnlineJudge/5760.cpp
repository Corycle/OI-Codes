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
const int N=105;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a,b,c,tot,p[N];
bool Check(ll x,ll y){
	while(y%x==0)y/=x;
	return y==1;
}
void GetP(ll b,ll n){
	tot=-1;
	while(n){
		p[++tot]=n%b;
		n/=b;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	while(scanf("%lld%lld%lld",&a,&b,&c)!=EOF){
		if(a==1){
			if(b==1&&c==1){puts("infinity");continue;}
			if(b==1&&c!=1){puts("0");continue;}
			if(Check(b,c)){puts("1");continue;}
		}
		if(b==c){
			if(a==b){puts("2");continue;}
			if(a!=b){puts("1");continue;}
		}
		if(a>b||b>c){puts("0");continue;}
		GetP(b,c);
		ll sum=0,tmp=1;
		for(int i=0;i<=tot;i++){
			sum+=tmp*p[i];
			tmp*=a;
		}
		printf("%d\n",(sum==b));
	}
	return 0;
}