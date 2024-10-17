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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,a[N],b[N],L[N],R[N];
void Delete(int x){R[L[x]]=R[x];L[R[x]]=L[x];}
int Solve(){
	int num=n,K=n-1;R[0]=1;L[n+1]=n;
	for(int i=1;i<=n;i++){b[i]=a[i];L[i]=i-1;R[i]=i+1;}
	while(1){
		int x=L[n+1],y=R[0];
		if(x==y||num==2)return 1;
		b[x]-=b[y];Delete(x);Delete(y);if(K==y)K=0;
		while(K&&(b[K]>b[x]||(b[K]==b[x]&&K>x)))K=L[K];
		if(!K)return num-((num&1)^1);
		num--;L[x]=K;R[x]=R[K];L[R[K]]=x;R[K]=x;
	}
}
int main(){
//	freopen("snakes.in","r",stdin);
//	freopen("snakes.out","w",stdout);
	int Case=read()-1;n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	printf("%d\n",Solve());
	while(Case--){
		int num=read();
		while(num--){int x=read();a[x]=read();}
		printf("%d\n",Solve());
	}
	return 0;
}