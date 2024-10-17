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
const int Dlt=19940105;
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,fa[N],sum[N],num[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=2;i<=n;i++)fa[i]=read();
	for(int Case=1;Case<=10;Case++){
		for(int i=1;i<=n;i++)sum[i]=1;
		for(int i=1;i<=n;i++)num[i]=0;
		for(int i=n;i>=1;i--)sum[fa[i]]+=sum[i];
		for(int i=1;i<=n;i++)num[sum[i]]++;
		printf("Case #%d:\n1\n",Case);
		for(int i=2;i<=n;i++){
			if(n%i)continue;int ans=0;
			for(int j=1;i*j<=n;j++)ans+=num[i*j];
			if(ans*i==n)printf("%d\n",i);
		}
		for(int i=2;i<=n;i++){
			fa[i]=(fa[i]+Dlt)%(i-1)+1;
		}
	}
	return 0;
}