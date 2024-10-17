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
const int Mod=1e9+7;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N],t[N];
int n,m,flag,a[N],b[N],g[N],f[N],P[N],nxt[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Change(char s[],int a[],int n){
	int len=strlen(s+1),tot=0;
	for(int i=1;i<=len;i++){
		int x=(('a'<=s[i]&&s[i]<='z')?(s[i]-'a'):(s[i]-'A'+26));
		for(int j=4;j>=0;j--)if(tot<n)a[++tot]=(x>>j)&1;
		if(tot==n)break;
	}
}
void GetNext(int a[],int n){
	for(int i=2,j=0;i<=n;i++){
		while(j&&a[j+1]!=a[i])j=nxt[j];
		if(a[j+1]==a[i])j++;nxt[i]=j;
	}
}
void Check(){
	flag=0;
	for(int i=1,j=0;i<=m;i++){
		while(j&&a[j+1]!=b[i])j=nxt[j];
		if(a[j+1]==b[i])j++;g[i]=j;
		if(g[i]==n)flag=1;
	}
}
int main(){
//	freopen("pizza.in","r",stdin);
//	freopen("pizza.out","w",stdout);
	int Case=read();
	P[0]=1;for(int i=1;i<N;i++)P[i]=mod(P[i-1]<<1);
	while(Case--){
		n=read();scanf("%s",s+1);Change(s,a,n);
		m=read();scanf("%s",t+1);Change(t,b,m);
		GetNext(a,n);Check();
		if(flag){puts("0");continue;}
		for(int i=1;i<=n;i++)f[i]=mod(f[nxt[i]]+P[i]);
		printf("%d\n",mod(f[n]-f[g[m]]+Mod));
	}
	return 0;
}