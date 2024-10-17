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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n;
ld a[N],s[N],t[N];
ld Calc(int l,int r){
	return s[r]-s[l-1]+log(t[r]-t[l-1]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=1.0*read()/1e6;
		s[i]=s[i-1]+log(1-a[i]);
		t[i]=t[i-1]+a[i]/(1-a[i]);
	}
	ld ans=-inf;
	for(int i=1,j=1;i<=n;i++){
		while(j<i&&Calc(j,i)<Calc(j+1,i))j++;
		ans=max(ans,Calc(j,i));
	}
	printf("%d",(int)(exp(ans)*1e6));
	return 0;
}