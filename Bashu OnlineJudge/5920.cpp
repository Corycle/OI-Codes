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
#define ld long double
#define top st[c].size()-1
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>st[N];
ll n,a[N],l[N],r[N],f[N],num[N],sum[N];
ll Sqr(ll x){return x*x;}
ll X(int i){return sum[i];}
ll Y(int i){return f[i-1]+a[i]*sum[i]*sum[i]-2*a[i]*sum[i];}
ld Slope(int i,int j){return (ld)(Y(i)-Y(j))/(X(i)-X(j));}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)sum[i]=++num[a[i]=read()];
	for(int i=1;i<=n;i++){
		int c=a[i];
		if(sum[i]==1)f[i]=f[i-1]+c;
		else{
			while(st[c].size()>1&&Slope(st[c][top-1],st[c][top])<=2*c*sum[i])st[c].pop_back();
			int j=st[c][top];f[i]=max(f[i-1]+c,f[j-1]+c*Sqr(sum[i]-sum[j]+1));
			while(st[c].size()>1&&Slope(st[c][top-1],st[c][top])<=Slope(st[c][top],i))st[c].pop_back();
		}
		st[c].push_back(i);
	}
	printf("%lld",f[n]);
	return 0;
}