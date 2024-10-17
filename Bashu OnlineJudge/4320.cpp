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
const double eps=1e-10;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
double f[N];
int n,Ans,a[N];
vector<int>G[N];
void DFS(int x,int fa,double sum){
	int num=0;f[x]=sum+log(a[x]);
	for(auto y:G[x])if(y!=fa)num++;
	for(auto y:G[x])if(y!=fa)DFS(y,x,sum+log(num));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++){
		int x=read(),y=read();
		G[x].push_back(y);
		G[y].push_back(x);
	}
	DFS(1,0,log(1));
	sort(f+1,f+n+1);
	for(int i=2,num=1;i<=n;i++){
		if(fabs(f[i]-f[i-1])<eps)num++;
		else num=1;
		Ans=max(Ans,num);
	}
	printf("%d",n-Ans);
	return 0;
}