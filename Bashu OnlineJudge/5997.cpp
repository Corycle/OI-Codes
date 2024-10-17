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
const int Mod=1e9+9;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[5];
int n,m,T,Ans,a[N],fac[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void DFS(int depth,int sum,int num){
	if(depth==n+1){
		if(sum==T)Ans=mod(Ans+fac[num]);
		return;
	}
	DFS(depth+1,sum,num);
	if(s[0]=='&')DFS(depth+1,a[depth]&sum,num+1);
	else if(s[0]=='|')DFS(depth+1,a[depth]|sum,num+1);
	else if(s[0]=='^')DFS(depth+1,a[depth]^sum,num+1);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			a[i]|=(read()<<(j-1));
		}
	}
	fac[1]=1;
	for(int i=2;i<=n;i++)fac[i]=1ll*fac[i-1]*i%Mod;
	for(int i=1;i<=m;i++)T|=(read()<<(i-1));
	if(s[0]=='&')DFS(1,(1<<m)-1,0);
	else if(s[0]=='|')DFS(1,0,0);
	else if(s[0]=='^')DFS(1,0,0);
	printf("%d",Ans);
	return 0;
}