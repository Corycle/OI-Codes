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
const int Mod=1e8;
const int N=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll a[N],b[N],c[N];
void Multi(ll a[],ll b[]){
	c[0]=a[0]+b[0];
	for(int i=1;i<=a[0];i++){
		for(int j=1;j<=b[0];j++){
			c[i+j-1]+=a[i]*b[j];
		}
	}
	for(int i=1;i<=c[0];i++){
		c[i+1]+=c[i]/Mod;
		c[i]%=Mod;
	}
	while(!c[c[0]])c[0]--;
	memcpy(a,c,sizeof(c));
	memset(c,0,sizeof(c));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		int n=read();
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		a[0]=1;a[1]=1;b[0]=1;b[1]=2;
		int t=n+1;
		while(t){
			if(t&1)Multi(a,b);
			Multi(b,b);
			t>>=1;
		}
		a[1]--;
		if(!(n&1))a[1]--;
		if(a[1]<0){a[1]+=Mod;a[2]--;}
		for(int i=a[0];i>=1;i--){
			if(i!=1)a[i-1]+=Mod*(a[i]%3);
			a[i]/=3;
		}
		while(a[0]&&!a[a[0]])a[0]--;
		printf("%lld",a[a[0]]);
		for(int i=a[0]-1;i>=1;i--){
			printf("%08lld",a[i]);
		}
		printf("\n");
	}
	return 0;
}