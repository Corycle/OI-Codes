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
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a,b,m;
ll tot,cnt,ans;
ll s[N],f[N];
ll gcd(ll x,ll y){
	return y==0?x:gcd(y,x%y);
}
ll lcm(ll x,ll y){
	return x/gcd(x,y)*y;
}
void DFS(ll x){
	if(x>b)return;
	if(x)s[++tot]=x;
	DFS(x*10+6);
	DFS(x*10+8);
}
void Search(ll x,ll y,ll z){
	//x幸运数字个数，y容斥，z最小公倍数 
	for(ll i=x;i>=1;i--){
		ll p=lcm(z,f[i]);
		if(p>0&&p<=m){
			ans+=y*m/p;
			Search(i-1,-y,p);
		}
	}
}
ll Solve(ll n){
	ans=0;m=n;
	Search(cnt,1,1);
	return ans;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	a=read();b=read();
	DFS(0);
	sort(s+1,s+tot+1);
	for(ll i=1;i<=tot;i++){
		if(!s[i])continue;
		for(ll j=i+1;j<=tot;j++){
			if(s[j]%s[i]==0)s[j]=0;
		}
		f[++cnt]=s[i];
	}
	ll Ans=Solve(b)-Solve(a-1);
	printf("%lld",Ans);
	return 0;
}