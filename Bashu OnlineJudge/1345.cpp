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
const int N=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,K;
int c[N][N];
int lowbit(int x){return x&(-x);}
void Add(int x,int y,int z){
	for(int i=x;i<=n;i+=lowbit(i)){
		for(int j=y;j<=n;j+=lowbit(j)){
			c[i][j]+=z;
		}
	}
}
int Ask(int x,int y){
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		for(int j=y;j>=1;j-=lowbit(j)){
			ans+=c[i][j];
		}
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();K=read();n=1001;
	while(m--){
		int sx=read()+1,sy=read()+1;
		int tx=read()+1,ty=read()+1;
		Add(tx,ty,1);
		Add(sx,sy,1);
		Add(sx,ty,-1);
		Add(tx,sy,-1);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			ans+=(Ask(i,j)==K);
		}
	}
	printf("%d",ans);
	return 0;
}