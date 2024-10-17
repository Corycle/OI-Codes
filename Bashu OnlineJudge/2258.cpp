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
const int M=1<<24;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Sta,a[M],b[N],f[M],g[M];
bool cmp(int x,int y){return x>y;}
int lowbit(int x){return x&(-x);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=0;i<n;i++)a[1<<i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	sort(b+1,b+m+1,cmp);
	Sta=(1<<n)-1;f[0]=1;
	for(int S=1;S<=Sta;S++){
		f[S]=m+1;
		for(int j=S,i=lowbit(j);j;j=j^lowbit(j),i=lowbit(j)){
			int T=S^i;
			int t1=(g[T]+a[i]<=b[f[T]]?f[T]:f[T]+1);
			int t2=(t1==f[T]?g[T]+a[i]:a[i]);
			if(b[t1]<t2)continue;
			if(f[S]>t1){f[S]=t1;g[S]=t2;}
			if(f[S]==t1)g[S]=min(g[S],t2);
		}
	}
	if(f[Sta]==m+1)puts("NIE");
	else printf("%d",f[Sta]);
	return 0;
}