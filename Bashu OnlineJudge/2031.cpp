/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll Mod=1e9;
const ll N=305;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll n,f[N][N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(ll i=1;i<=n;i++)f[i][i]=1;
	for(ll len=2;len<=n;len+=2){
		for(ll i=1;i+len<=n;i++){
			ll j=i+len;
			if(s[i]!=s[j])continue;
			for(ll k=i+2;k<=j;k++){
				if(s[i]==s[k])f[i][j]=(f[i][j]+f[i+1][k-1]*f[k][j]%Mod)%Mod;
			}
		}
	}
	printf("%lld\n",f[1][n]);
	return 0;
}