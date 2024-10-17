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
const int Mod=9901;
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,num,Ans;
int p[N],cnt[N];
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Divide(int x){
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			p[++num]=i;
			while(x%i==0){
				x/=i;
				cnt[num]++;
			}
		}
	}
	if(x!=1){
		p[++num]=x;
		cnt[num]++;
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Divide(n);Ans=1;
	for(int i=1;i<=num;i++){
		if((p[i]-1)%Mod==0)Ans=(1ll*m*cnt[i]+1)%Mod*Ans%Mod;
		else{
			int x=(Pow(p[i],1ll*m*cnt[i]+1)-1+Mod)%Mod;
			int y=(Pow(p[i]-1,Mod-2));
			Ans=1ll*Ans*x%Mod*y%Mod;
		}
	}
	printf("%d",Ans);
	return 0;
}