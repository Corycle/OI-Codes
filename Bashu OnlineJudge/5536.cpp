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
const ll inf=0x3f3f3f3f;
const ll N=1005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll L,R,Ans,a[N];
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
void DFS(ll x){
	if(x>R)return;
	a[++a[0]]=x;
	DFS(x*10+2);
	DFS(x*10+9);
}
void Solve(ll x,ll lst,ll num){
	if(x>R)return;
	if(x!=1)Ans+=(R/x-(L-1)/x)*((num&1)?1:-1);
	for(ll i=lst+1;i<=a[0];i++){
		Solve(x/gcd(x,a[i])*a[i],i,num+1);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	L=read();R=read();
	DFS(2);DFS(9);
	sort(a+1,a+a[0]+1);
	for(ll i=1;i<=a[0];i++){
		for(ll j=i+1;j<=a[0];j++){
			if(a[j]%a[i]==0)a[j]=a[i];
		}
	}
	sort(a+1,a+a[0]+1);
	a[0]=unique(a+1,a+a[0]+1)-a-1;
	Solve(1,0,0);
	printf("%lld",Ans);
	return 0;
}