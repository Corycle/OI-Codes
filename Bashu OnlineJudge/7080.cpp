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
const int N=2022;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,W,H,A,B,Mod;
struct Point{int h,x,y;}P[N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Pow(int x,int y){int ans=1;while(y){if(y&1)ans=1ll*ans*x%Mod;x=1ll*x*x%Mod;y>>=1;}return ans;}
namespace Task1{
	void Main(){
		while(m--){
			int x=read(),y=read(),Ans=0;
			for(int i=1;i<=n;i++)Ans=mod(Ans+1ll*P[i].h*Pow(A,abs(P[i].x-x))%Mod*Pow(B,abs(P[i].y-y))%Mod);
			cout<<Ans<<'\n';
		}
	}
}
namespace Task2{
	int num1,num2,P1[N],P2[N],tmp[N];
	int Ans1[N][N],Ans2[N][N],Ans3[N][N],Ans4[N][N];
	void Main(){
		P1[++num1]=0;P1[++num1]=1;P1[++num1]=W;P1[++num1]=W+1;
		P2[++num2]=0;P2[++num2]=1;P2[++num2]=H;P2[++num2]=H+1;
		for(int i=1;i<=n;i++){P1[++num1]=P[i].x;P2[++num2]=P[i].y;}
		sort(P1+1,P1+num1+1);num1=unique(P1+1,P1+num1+1)-P1-1;
		sort(P2+1,P2+num2+1);num2=unique(P2+1,P2+num2+1)-P2-1;
		for(int i=1;i<=n;i++){
			P[i].x=lower_bound(P1+1,P1+num1+1,P[i].x)-P1;
			P[i].y=lower_bound(P2+1,P2+num2+1,P[i].y)-P2;
			Ans1[P[i].x][P[i].y]=mod(Ans1[P[i].x][P[i].y]+P[i].h);
			Ans2[P[i].x][P[i].y]=mod(Ans2[P[i].x][P[i].y]+P[i].h);
			Ans3[P[i].x][P[i].y]=mod(Ans3[P[i].x][P[i].y]+P[i].h);
			Ans4[P[i].x][P[i].y]=mod(Ans4[P[i].x][P[i].y]+P[i].h);
		}
		for(int j=1;j<num2;j++)tmp[j]=Pow(B,P2[j+1]-P2[j]);
		for(int i=1;i<=num1;i++){
			for(int j=2;j<=num2;j++){
				Ans1[i][j]=mod(Ans1[i][j]+1ll*Ans1[i][j-1]*tmp[j-1]%Mod);
				Ans4[i][j]=mod(Ans4[i][j]+1ll*Ans4[i][j-1]*tmp[j-1]%Mod);
			}
			for(int j=num2-1;j>=1;j--){
				Ans2[i][j]=mod(Ans2[i][j]+1ll*Ans2[i][j+1]*tmp[j]%Mod);
				Ans3[i][j]=mod(Ans3[i][j]+1ll*Ans3[i][j+1]*tmp[j]%Mod);
			}
		}
		for(int i=1;i<num1;i++)tmp[i]=Pow(A,P1[i+1]-P1[i]);
		for(int j=1;j<=num2;j++){
			for(int i=2;i<=num1;i++){
				Ans1[i][j]=mod(Ans1[i][j]+1ll*Ans1[i-1][j]*tmp[i-1]%Mod);
				Ans2[i][j]=mod(Ans2[i][j]+1ll*Ans2[i-1][j]*tmp[i-1]%Mod);
			}
			for(int i=num1-1;i>=1;i--){
				Ans3[i][j]=mod(Ans3[i][j]+1ll*Ans3[i+1][j]*tmp[i]%Mod);
				Ans4[i][j]=mod(Ans4[i][j]+1ll*Ans4[i+1][j]*tmp[i]%Mod);
			}
		}
		while(m--){
			int x=read(),y=read(),Ans=0;
			int px=upper_bound(P1+1,P1+num1+1,x)-P1-1;
			int py=upper_bound(P2+1,P2+num2+1,y)-P2-1;
			Ans=mod(Ans+1ll*Ans1[px][py]*Pow(A,x-P1[px])%Mod*Pow(B,y-P2[py])%Mod);
			Ans=mod(Ans+1ll*Ans2[px][py+1]*Pow(A,x-P1[px])%Mod*Pow(B,P2[py+1]-y)%Mod);
			Ans=mod(Ans+1ll*Ans4[px+1][py]*Pow(A,P1[px+1]-x)%Mod*Pow(B,y-P2[py])%Mod);
			Ans=mod(Ans+1ll*Ans3[px+1][py+1]*Pow(A,P1[px+1]-x)%Mod*Pow(B,P2[py+1]-y)%Mod);
			cout<<Ans<<'\n';
		}
	}
}
int main(){
//	freopen("satellite.in","r",stdin);
//	freopen("satellite.out","w",stdout);
	n=read();m=read();W=read();H=read();Mod=read();A=read();B=read();
	for(int i=1;i<=n;i++){P[i].h=read();P[i].x=read();P[i].y=read();}
	if(1ll*n*m<=100000){Task1::Main();return 0;}
	Task2::Main();
	return 0;
}