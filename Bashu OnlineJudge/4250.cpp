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
const int N=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll n,a[N],f[N],g[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]-'0';
	for(int i=0;i<=9;i++)for(int j=0;j<=9;j++)g[i+j]++;
	f[n+1]=1;
	for(int i=n;i>=1;i--){
		f[i]=f[i+1]*g[a[i]];
		if(a[i]==1&&i<n)f[i]+=f[i+2]*g[a[i]*10+a[i+1]];
	}
	printf("%lld\n",f[1]);
	return 0;
}