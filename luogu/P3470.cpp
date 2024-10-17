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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,A,B,m1,m2,a[N],b[N],sum[N],Min[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();A=read();B=read();m1=read();m2=read();scanf("%s",s+1);
	for(int i=1;i<=n;i++){a[i]=(s[i]=='+'?1:-1);sum[i]=sum[i-1]+a[i];Min[i]=min(Min[i-1],sum[i]);}
	int d=(B-A-sum[n])/2,ans=inf;
	for(int i=1;i<=n;i++){
		int tmp=min(sum[n]-sum[n-i+1]+Min[n-i+1],b[i-1]);
		int t=(A+tmp>=0?0:(-(A+tmp)+1)/2);
		ans=min(ans,m1*(t+abs(t-d))+m2*(i-1));
		b[i]=min(b[i-1]+a[n-i+1],0);
	}
	printf("%d\n",ans);
	return 0;
}
