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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
vector<int>G[N];
int n,m,S,tot,tmp,cnt0,cnt1,Ans,Mod,c[N],num[N],Fac[N];
void DFS(int x,int col){
	int Num=0;c[x]=col;
	for(auto y:G[x]){
		if(c[y]==c[x]){puts("0");exit(0);}
		if(!c[y])DFS(y,3-col);Num+=(num[y]>=2);
	}
	if(num[x]>=2)cnt0++;cnt1++;
	if(Num>2){puts("0");exit(0);}
	Ans=1ll*Ans*Fac[num[x]-Num]%Mod;
}
int F(int n,int m){//C(n+m-1,m-1) * n!
	int ans=1;
	for(int i=m;i<=n+m-1;i++)ans=1ll*ans*i%Mod;
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();Mod=read();Ans=Fac[0]=1;S=2;
	for(int i=1;i<=n;i++)Fac[i]=1ll*Fac[i-1]*i%Mod;
	for(int i=1;i<=m;i++){int x=read(),y=read();G[x].push_back(y);G[y].push_back(x);num[x]++;num[y]++;}
	for(int i=1;i<=n;i++){
		if(c[i])continue;
		cnt0=cnt1=0;DFS(i,1);
		if(cnt1>1){
			tot++;Ans=2ll*Ans*tot%Mod;
			if(cnt0>1)Ans=2ll*Ans%Mod;
			S+=cnt1;
		}
		else tmp++;
	}
	Ans=1ll*Ans*F(tmp,S)%Mod;
	printf("%d\n",Ans);
	return 0;
}
