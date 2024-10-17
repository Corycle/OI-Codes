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
const int N=2e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,tot;
char s[N],b[N];
int f[N],Ans[N],vis[N];
void Manacher(){
	n=strlen(b+1);
	s[0]='&';
	for(int i=1;i<=n;i++){
		s[i*2-1]='#';
		s[i*2]=b[i];
	}
	s[n*2+1]='#';
	int Max=0,id=0;n=n*2+1;
	for(int i=1;i<=n;i++){
		if(i>Max)f[i]=1;
		else f[i]=min(Max-i,f[id*2-i]);
		while(s[i-f[i]-1]==s[i+f[i]+1])f[i]++;
		if(i+f[i]>Max){id=i;Max=i+f[i];}
	}
}
int main(){
//	freopen("green.in","r",stdin);
//	freopen("green.out","w",stdout);
	int T=read();
	while(T--){
		scanf("%s",b+1);
		Manacher();tot=0;
		memset(vis,0,sizeof(vis));
		for(int i=n;i>0;i--){
			if(i&1)continue;
			if(i/2+f[i]/2>=n/2||(vis[i/2+f[i]/2]&&(i/2-f[i]/2<=1))){
				Ans[++tot]=i/2;vis[i/2]=1;
			}
		}
		for(int i=tot;i>=1;i--)printf("%d ",Ans[i]);
		printf("\n");
	}
	return 0;
}