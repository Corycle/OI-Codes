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
const int M=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
bool f[N][M];
char s[M],t[N];
int n,m,top,p[N],st[N],nxt[N];
bool Check(char a,char b){return a=='?'||a=='*'||a==b;}
int main(){
//	freopen("walking.in","r",stdin);
//	freopen("walking.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=1;i<=n;i++){
		if(s[i]=='[')st[++top]=i;
		if(s[i]==']'){p[p[i]=st[top]]=i;top--;}
	}
	for(int i=n,lst=n+1;i>=0;i--){
		nxt[i]=lst;
		if(s[i]!='['&&s[i]!=']')lst=i;
	}
	int T=read();
	while(T--){
		scanf("%s",t+1);m=strlen(t+1);
		for(int i=0;i<=n+1;i++)f[0][i]=0;f[0][0]=1;
		for(int i=0;i<m;i++){
			for(int j=0;j<=n+1;j++)f[i+1][j]=0;
			for(int j=0;j<=n;j++){
				if(!f[i][j])continue;
				if(s[j]=='*')f[i+1][j]=1;
				if(s[j+1]=='*')f[i][j+1]=1;
				if(s[j+1]==']')f[i][j+1]=1;
				if(s[j+1]=='[')f[i][j+1]=f[i][p[j+1]]=1;
				f[i+1][nxt[j]]|=Check(s[nxt[j]],t[i+1]);
			}
			printf("%c",f[i+1][n]?'1':'0');
		}
		puts("");
	}
	return 0;
}