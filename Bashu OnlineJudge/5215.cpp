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
#include<unordered_map>
#define ll long long
#define ull unsigned ll
using namespace std;
const int inf=0x3f3f3f3f;
const int Mod=998244353;
const int Mul=13131;
const int N=62;
const int M=12;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[M];
unordered_map<ull,bool>Vis;
int n,Ans,a[M],num[N],g[M][N][N],f[N][N][N];
int mod(int x){return x>=Mod?x-Mod:x;}
int Get(char c){return (c>='a'&&c<='z')?c-'a':((c>='A'&&c<='Z')?c-'A'+26:c-'0'+52);}
void Insert(int len){
	ull Hash=1;for(int i=1;i<=len;i++)Hash=Hash*Mul+a[i];
	if(!Vis[Hash]){Vis[Hash]=true;g[len][a[1]][a[len]]++;}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);int len=strlen(s+1);
		for(int j=1;j<=len;j++)a[j]=Get(s[j]);
		Insert(len);reverse(a+1,a+len+1);Insert(len);
	}
	for(int l=3;l<=10;l++){
		memset(f,0,sizeof(f));
		for(int a=0;a<N;a++){
			for(int b=0;b<N;b++){
				if(!g[l][a][b])continue;
				for(int c=b;c<N;c++){
					if(!g[l][a][c])continue;
					for(int d=c;d<N;d++){
						if(!g[l][a][d])continue;
						f[b][c][d]=mod(f[b][c][d]+1ll*g[l][a][b]*g[l][a][c]%Mod*g[l][a][d]%Mod);
					}
				}
			}
		}
		int Num=24;//4!
		for(int a=0;a<N;a++){
			num[a]++;Num/=num[a];
			for(int b=a;b<N;b++){
				num[b]++;Num/=num[b];
				for(int c=b;c<N;c++){
					if(!f[a][b][c])continue;
					num[c]++;Num/=num[c];
					for(int d=c;d<N;d++){
						num[d]++;Num/=num[d];
						Ans=mod(Ans+1ll*Num*f[a][b][c]%Mod*f[a][b][d]%Mod*f[a][c][d]%Mod*f[b][c][d]%Mod);
						Num*=num[d];num[d]--;
					}
					Num*=num[c];num[c]--;
				}
				Num*=num[b];num[b]--;
			}
			Num*=num[a];num[a]--;
		}
	}
	printf("%d",Ans);
	return 0;
}