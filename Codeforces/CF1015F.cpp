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
const int N=205;
const int Mod=1e9+7;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,m,a[N],to[N][2],fail[N],f[N][N][N];
void mod(int &x,int y){x+=y;if(x>=Mod)x-=Mod;}
void Prepare(){
	for(int i=2,lst=0;i<=m;++i){
		while(lst&&a[lst+1]!=a[i])lst=fail[lst];
		if(a[lst+1]==a[i])fail[i]=++lst; 
	}
	to[0][a[1]]=1;
	for(int i=1;i<m;++i){
		int tmp=fail[i];to[i][a[i+1]]=i+1;
		while(tmp&&a[tmp+1]==a[i+1])tmp=fail[tmp];
		if(a[tmp+1]!=a[i+1])to[i][a[tmp+1]]=tmp+1;
	}
	to[m][0]=to[m][1]=m;
}
int main(){
	n=read();scanf("%s",s+1);m=strlen(s+1);
	for(int i=1;i<=m;++i)a[i]=(s[i]==')');
	Prepare();
	f[0][0][0]=1;
	for(int i=0;i<2*n;++i){
		for(int j=0;j<=m;++j){
			for(int k=0;k<=n;++k){
				int tmp=f[i][j][k];
				if(!tmp)continue;
				if(k)mod(f[i+1][to[j][1]][k-1],tmp);
				if(k+1<=n)mod(f[i+1][to[j][0]][k+1],tmp);
			}
		}
	}
	printf("%d\n",f[2*n][m][0]);
	return 0;
}
