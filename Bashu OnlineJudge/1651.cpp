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
const int Mod=10086;
const int N=1e5+5;
const int M=31;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],b[N],P[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct Line_Basis{
	int p[M];
	void Insert(int x){
		for(int i=M-1;i>=0;i--){
			if((x>>i)&1){
				if(!p[i]){p[i]=x;break;}
				x^=p[i];
			}
		}
	}
	void Build(){
		for(int i=M-1;i>=0;i--){
			for(int j=i-1;j>=0;j--){
				if((p[i]>>j)&1)p[i]^=p[j];
			}
		}
		for(int i=M-1;i>=0;i--)if(p[i])b[++m]=p[i];
	}
}F;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();P[0]=1;
	for(int i=1;i<=n;i++)P[i]=mod(P[i-1]<<1);
	for(int i=1;i<=n;i++)F.Insert(a[i]=read());
	F.Build();
	int Q=read(),x=0,Ans=0;
	for(int i=1;i<=m;i++){
		if((x^b[i])<Q){
			x^=b[i];
			Ans=mod(Ans+P[m-i]);
		}
	}
	if(Q)Ans=mod(Ans+1);
	Ans=1ll*Ans*P[n-m]%Mod;
	printf("%d",mod(Ans+1));
	return 0;
}