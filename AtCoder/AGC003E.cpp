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
const ll INF=9e18;
const int N=1e5+5;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
ll a[N],num[N],Ans[N];
void Solve(int pos,ll x,ll t){
	num[pos]+=t*(x/a[pos]);x%=a[pos];
	pos=lower_bound(a+1,a+n+1,x)-a;
	if(pos==1){Ans[1]+=t;Ans[x+1]-=t;}
	else Solve(pos-1,x,t);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=a[1]=read();n=read()+1;
	for(int i=2;i<=n;i++){
		a[i]=read();
		while(a[i]<=a[i-1]){a[i-1]=a[i];i--;n--;}
	}
	num[n]=1;
	for(int i=n;i>1;i--)Solve(i-1,a[i],num[i]);
	for(int i=1;i<=a[1];i++){
		Ans[i]+=Ans[i-1];
		printf("%lld\n",Ans[i]+num[1]);
	}
	for(int i=a[1]+1;i<=m;i++)puts("0");
	return 0;
}
