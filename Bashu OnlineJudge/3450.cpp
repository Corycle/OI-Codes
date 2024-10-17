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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,K,Max,Ans,a[N],b[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();K=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)Max=max(Max,a[i]);
	for(int i=1;i<=Max;i++){
		int num=0;
		for(int j=1;j<=n;j++)num+=a[j]/i;
		if(num<K/2)break;
		if(num>=K){Ans=max(Ans,i*K/2);continue;}
		for(int j=1;j<=n;j++)b[j]=a[j]%i;
		sort(b+1,b+n+1);
		int sum=(num-K/2)*i;
		for(int j=1;j<=n&&j+num<=K;j++)sum+=b[n-j+1];
		Ans=max(Ans,sum);
	}
	printf("%d",Ans);
	return 0;
}