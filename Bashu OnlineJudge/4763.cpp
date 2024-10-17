#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=10007;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=(s*10+c-'0')%Mod;c=getchar();}
	return s*f;
}
int n;
int Pow(int x,int y,int mod){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=ans*tot%mod;
		tot=tot*tot%mod;
		y/=2;
	}
	return ans;
}
int Inv(int x,int mod){
	return Pow(x,mod-2,mod);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	printf("%d\n",n*(n+1)%Mod*(n+2)%Mod*Inv(6,Mod)%Mod);
	return 0;
}