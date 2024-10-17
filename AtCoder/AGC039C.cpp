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
const int Mod=998244353;
const int N=4e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,Ans,a[N],b[N],f[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Solve(int T){
	int L=T/2,ans=0,flag=1;
	for(int i=1;i<=L;i++){ans=mod(ans*2+a[i]);b[i]=a[i];}
	for(int i=L+1;i<=n;i++)b[i]=a[i-L]^1;
	for(int i=1;i<=n;i++){
		if(b[i]<a[i])break;
		if(b[i]>a[i]){flag=0;break;}
	}
	ans=mod(ans+flag);
	return f[T]=ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();scanf("%s",s+1);
	for(int i=1;i<=n;i++)a[i]=s[i]-'0';
	for(int i=1;i<=n*2;i++)if(n%i!=0&&n*2%i==0)Solve(i);
	for(int i=1;i<=n*2;i++){
		if(!(n%i!=0&&n*2%i==0))continue;
		for(int j=i*2;j<=n*2;j+=i){
			if(!(n%j!=0&&n*2%j==0))continue;
			f[j]=mod(f[j]-f[i]+Mod);
		}
	}
	for(int i=1;i<=n*2;i++)Ans=mod(Ans+1ll*f[i]*i%Mod);
	printf("%d\n",Ans);
	return 0;
}
