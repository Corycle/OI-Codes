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
const ll inf=0x3f3f3f3f;
const ll Mod=998244353;
const ll N=500005;
const ll M=10;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char s1[N],s2[N];
int num1,num2,Max;
int c[N],c1[N],c2[N];
ll F[N],P[N],g[N][M],s[N][M],num[M];
ll MOD(ll x){return x>=Mod?x-Mod:x;}
void Dp(int len,int flag,ll sum){
	if(!len){Ans=MOD(Ans+sum);return;}
	if(!flag){
		Ans=(Ans+sum*F[len]%Mod+P[len-1])%Mod;
		for(int i=1;i<=9;i++)Ans=MOD(Ans+num[i]*s[len-1][i-1]%Mod);
	}
	else{
		int up=c[len];ll Sum[11]={};
		for(int i=9;i>=0;i--)Sum[i]=MOD(Sum[i+1]+num[i]);
		for(int i=0;i<=up;i++){
			num[i]++;Dp(len-1,flag&&i==up,MOD(sum+Sum[i+1]));num[i]--;
		}
	}
}
ll Solve(int type){
	if(type==0)for(int i=0;i<=Max;i++)c[i]=c1[i];
	if(type==1)for(int i=0;i<=Max;i++)c[i]=c2[i];
	Ans=0;Dp(Max,1,0);
	return Ans;
}
void dec(){
	c1[1]--;
	for(int i=1;i<=num1;i++){
		if(c1[i]<0){
			c1[i+1]--;
			c1[i]+=10;
		}
	}
}
int main(){
//	freopen("pair.in","r",stdin);
//	freopen("pair.out","w",stdout);
	ll T=read();read();
	int Ln=5e5;P[1]=0;F[0]=1;
	for(int i=0;i<=9;i++)g[0][i]=1;s[0][0]=g[0][0];
	for(int i=1;i<=9;i++)s[0][i]=s[0][i-1]+g[0][i];
	for(int i=1;i<=Ln;i++){
		P[i]=P[i-1]*10%Mod;
		F[i]=F[i-1]*10%Mod;
		for(int j=0;j<=9;j++){
			g[i][j]=MOD(g[i-1][j]*10%Mod+F[i]);
			if(j>0){
				s[i][j]=MOD(s[i][j-1]+g[i][j]);
				P[i]=MOD(P[i]+s[i-1][j-1]);
			}
			else s[i][j]=g[i][j];
		}
	}
	for(int i=1;i<=T;i++){
		scanf("%s%s",s1+1,s2+1);
		num1=strlen(s1+1);num2=strlen(s2+1);
		for(int j=1;j<=num1;j++)c1[num1-j+1]=s1[j]-'0';
		for(int j=1;j<=num2;j++)c2[num2-j+1]=s2[j]-'0';
		dec();Max=max(num1,num2);
		for(int j=num1+1;j<=Max;j++)c1[j]=0;
		for(int j=num2+1;j<=Max;j++)c2[j]=0;
		printf("%lld\n",MOD(Solve(1)-Solve(0)+Mod));
	}
	return 0;
}