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
const int M=(1<<16)+5;
const int N=505;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,S,tot;
int A[M],B[M],C[M],f[N][M],sta[N],val[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void FMT_OR(int a[],int n,int f){
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);j++){
			if(i&j)a[j]=(f==1?mod(a[j]+a[j-i]):mod(a[j]-a[j-i]+Mod));
		}
	}
}
void FMT_AND(int a[],int n,int f){
	for(int i=1;i<(1<<n);i<<=1){
		for(int j=0;j<(1<<n);j++){
			if(i&j)a[j-i]=(f==1?mod(a[j-i]+a[j]):mod(a[j-i]-a[j]+Mod));
		}
	}
}
void Update_OR(int a[],int b[],int c[]){
	for(int i=0;i<(1<<n);i++){A[i]=a[i];B[i]=b[i];}
	FMT_OR(A,n,1);FMT_OR(B,n,1);
	for(int i=0;i<(1<<n);i++)C[i]=1ll*A[i]*B[i]%Mod;
	FMT_OR(C,n,-1);
	for(int i=0;i<(1<<n);i++)c[i]=mod(c[i]+C[i]);
}
void Update_AND(int a[],int b[],int c[]){
	for(int i=0;i<(1<<n);i++){A[i]=a[i];B[i]=b[i];}
	FMT_AND(A,n,1);FMT_AND(B,n,1);
	for(int i=0;i<(1<<n);i++)C[i]=1ll*A[i]*B[i]%Mod;
	FMT_AND(C,n,-1);
	for(int i=0;i<(1<<n);i++)c[i]=mod(c[i]+C[i]);
}
void update1(int x,int d){
	int s=0;
	for(int i=1;i<=n;i++)s|=(((sta[i]>>d)&1)<<(i-1));
	f[x][s]++;
}
void update2(int x,int d){
	int s=0;
	for(int i=1;i<=n;i++)s|=((((sta[i]>>d)&1)^1)<<(i-1));
	f[x][s]++;
}
void DFS(int x,int l,int r){
	if(l==r){
		if(s[l]>='A'&&s[l]<='D')update1(x,s[l]-'A');
		if(s[l]>='a'&&s[l]<='d')update2(x,s[l]-'a');
		if(s[l]=='?')for(int i=0;i<4;i++){update1(x,i);update2(x,i);}
		return;
	}
	int num=0,pos=0;
	for(int i=l;i<=r;i++){
		num+=(s[i]=='(')-(s[i]==')');
		if(!num){pos=i+1;break;}
	}
	if(pos==r+1){DFS(x,l+1,r-1);return;}
	int ls=++tot;DFS(ls,l,pos-1);
	int rs=++tot;DFS(rs,pos+1,r);
	if(s[pos]=='|'||s[pos]=='?')Update_OR(f[ls],f[rs],f[x]);
	if(s[pos]=='&'||s[pos]=='?')Update_AND(f[ls],f[rs],f[x]);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);m=strlen(s+1);n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=4;j++)sta[i]|=(read()<<(j-1));
		S|=((val[i]=read())<<(i-1));
	}
	DFS(++tot,1,m);
	printf("%d",f[1][S]);
	return 0;
}
