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
const int N=30005;
const int M=25;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int s1[N],s2[N],vis[N],sg[M][M][M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	for(int i=1;i<N;i++){
		if(i%2==0)s1[i]=s1[i/2]+1;
		if(i%3==0)s2[i]=s2[i/3]+1;
	}
	for(int MaxQ=1;MaxQ<=20;MaxQ++){
		for(int a=0;a<=20;a++){
			for(int b=0;b<=20;b++){
				vector<int>tmp;
				for(int p=1;p<=a;p++){
					int s=0;
					for(int q=1;p*q<=a&&q<=MaxQ;q++){
						s^=sg[MaxQ][a-p*q][b];
						vis[s]=1;tmp.push_back(s);
					}
				}
				for(int p=1;p<=b;p++){
					int s=0;
					for(int q=1;p*q<=b&&q<=MaxQ;q++){
						s^=sg[MaxQ][a][b-p*q];
						vis[s]=1;tmp.push_back(s);
					}
				}
				for(int i=0;;i++)if(!vis[i]){sg[MaxQ][a][b]=i;break;}
				for(auto x:tmp)vis[x]=0;
			}
		}
	}
	int T=read();
	while(T--){
		int n=read(),MaxQ=read(),Ans=0;
		for(int i=1;i<=n;i++){
			int x=read();
			if(!x)Ans^=sg[MaxQ][s1[i]][s2[i]];
		}
		puts(Ans?"win":"lose");
	}
	return 0;
}