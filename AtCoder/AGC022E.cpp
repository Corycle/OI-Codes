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
const int N=3e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,Ans,f[N][3][3];
int mod(int x){return x>=Mod?x-Mod:x;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);f[0][0][0]=1;
	for(int i=0;i<n;i++){
		for(int x=0;x<=2;x++){
			for(int y=0;y<=2;y++){
				if(!f[i][x][y])continue;
				if(s[i+1]=='1'||s[i+1]=='?'){
					if(y)f[i+1][x][y-1]=mod(f[i+1][x][y-1]+f[i][x][y]);
					else f[i+1][min(x+1,2)][y]=mod(f[i+1][min(x+1,2)][y]+f[i][x][y]);
				}
				if(s[i+1]=='0'||s[i+1]=='?'){
					if(y==2)f[i+1][x][y-1]=mod(f[i+1][x][y-1]+f[i][x][y]);
					else f[i+1][x][y+1]=mod(f[i+1][x][y+1]+f[i][x][y]);
				}
			}
		}
	}
	for(int x=0;x<=2;x++){
		for(int y=0;y<=x;y++)Ans=mod(Ans+f[n][x][y]);
	}
	printf("%d",Ans);
	return 0;
}
