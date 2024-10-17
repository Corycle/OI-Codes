#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int P=997;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Ans;
int cnt[N],t[N];
int Inv[N],inv[N],fac[N];
int gcd(int x,int y){
	return y==0?x:gcd(y,x%y);
}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=(ans*tot)%P;
		tot=(tot*tot)%P;
		y>>=1;
	}
	return ans;
}
void Solve(){
	int ans=fac[n];
	int sum=0,tot=0;
	for(int i=1;i<=n;i++){
		ans=(ans*Inv[cnt[i]])%P;
		for(int j=1;j<=cnt[i];j++){
			ans=(ans*inv[i])%P;
			t[++tot]=i;
		}
	}
	for(int i=1;i<=tot;i++){
		sum+=t[i]/2;
		for(int j=i+1;j<=tot;j++){
			sum+=gcd(t[i],t[j]);
		}
	}
	ans=ans*Pow(2,sum)%P;
	Ans=(Ans+ans)%P;
}
void DFS(int x,int sum){
	if(x==1){
		cnt[x]=n-sum;
		Solve();
		return;
	}
	for(int i=0;sum+x*i<=n;i++){
		cnt[x]=i;
		DFS(x-1,sum+x*i);
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	Inv[1]=inv[1]=fac[1]=Inv[0]=inv[0]=fac[0]=1;
	for(int i=2;i<=n;i++)fac[i]=fac[i-1]*i%P;
	for(int i=2;i<=n;i++)inv[i]=inv[P%i]*(P-P/i)%P;
	for(int i=2;i<=n;i++)Inv[i]=Inv[i-1]*inv[i]%P;
	DFS(n,0);
	printf("%d",Ans*Inv[n]%P);
	return 0;
}