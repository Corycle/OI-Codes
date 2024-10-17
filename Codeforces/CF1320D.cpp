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
const int Mul=13131;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,num[N],P[N],Hash[2][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int GetHash(int l,int r,int h[]){return mod(h[r]-1ll*h[l-1]*P[num[r]-num[l-1]]%Mod+Mod);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();scanf("%s",s+1);
	P[0]=1;for(int i=1;i<=n;i++)P[i]=1ll*P[i-1]*Mul%Mod;
	for(int i=1;i<=n;i++){
		num[i]=num[i-1]+(s[i]=='0');
		if(s[i]=='1')for(int t=0;t<2;t++)Hash[t][i]=Hash[t][i-1];
		if(s[i]=='0')for(int t=0;t<2;t++)Hash[t][i]=mod(1ll*Hash[t][i-1]*Mul%Mod+((i&1)^t)+1);
	}
	m=read();
	while(m--){
		int l1=read(),l2=read(),len=read();
		puts(GetHash(l1,l1+len-1,Hash[l1&1])==GetHash(l2,l2+len-1,Hash[l2&1])?"Yes":"No");
	}
	return 0;
}
