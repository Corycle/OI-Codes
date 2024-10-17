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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,h[N],a[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)h[i]=read();
	for(int i=1;i<=n;i++){
		h[i]=max(0,h[i]);
		int t1=min(h[i]/3,a[i]);
		h[i]-=t1*3;
		int t2=h[i]/2;
		h[i]-=t2*2;
		int t3=h[i];
		h[i]-=t3;
		Ans+=t1+t2+t3;
		a[i+1]+=t1*2+t2;
		h[i+1]-=t2+t3*2;
	}
	printf("%lld",Ans);
	return 0;
}