#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,g[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();m=read();
		if(n<m)swap(n,m);
		int tot=0;
		while(m!=0){
			g[++tot]=(n-m)/m+1;
			int t=n;
			n=m;
			m=t%m;
		}
		int x=1;
		for(int i=tot-1;i>=1;i--){
			if(x==1){
				if(g[i]==1)x=0;
				else x=1;
			}
			else x=1;
		}
		if(x==1)printf("Stan wins\n");
		else printf("Ollie wins\n");
	}
	return 0;
}