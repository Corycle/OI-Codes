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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,T;
int a[N],b[N],sum[N],Height[N];
int Rank[N],fir[N],sec[N],sa[N];
int RMQ[N][25];
void GetSA(){
	int p=0,*x=Rank,*y=sec;
	for(int i=0;i<=m;i++)sum[i]=0;
	for(int i=1;i<=n;i++)sum[x[i]=a[i]]++;
	for(int i=1;i<=m;i++)sum[i]+=sum[i-1];
	for(int i=n;i>=1;i--)sa[sum[x[i]]--]=i;
	for(int j=1;p<n;j<<=1,m=p){
		p=0;
		for(int i=n-j+1;i<=n;i++)y[++p]=i;
		for(int i=1;i<=n;i++)if(sa[i]-j>0)y[++p]=sa[i]-j;
		for(int i=1;i<=n;i++)fir[i]=x[y[i]];
		for(int i=0;i<=m;i++)sum[i]=0;
		for(int i=1;i<=n;i++)sum[fir[i]]++;
		for(int i=1;i<=n;i++)sum[i]+=sum[i-1];
		for(int i=n;i>=1;i--)sa[sum[fir[i]]--]=y[i];
		swap(x,y);
		x[sa[1]]=p=1;
		for(int i=2;i<=n;i++){
			if(y[sa[i-1]]!=y[sa[i]]||y[sa[i-1]+j]!=y[sa[i]+j])p++;
			x[sa[i]]=p;
		}
	}
	for(int i=1;i<=n;i++)Rank[sa[i]]=i;
}
void GetHeight(){
	int k=0;
	for(int i=1;i<=n;i++){
		if(Rank[i]==1)Height[Rank[i]]=0;
		else{
			int j=sa[Rank[i]-1];
			while(a[i+k]==a[j+k])k++;
			Height[Rank[i]]=k;
			if(k!=0)k--;
		}
	}
}
void ST(){
	for(int i=1;i<=n;i++)RMQ[i][0]=Height[i];
	int k=(int)(log(n)/log(2));
	for(int j=1;j<=k;j++){
		for(int i=1;i+(1<<j)-1<=n;i++){
			RMQ[i][j]=min(RMQ[i][j-1],RMQ[i+(1<<(j-1))][j-1]);
		}
	}
}
int Ask(int x,int y){
	if(x==y)return n-x+1;
	x=Rank[x];y=Rank[y];
	if(x>y)swap(x,y);
	x++;
	int k=(int)(log(y-x+1)/log(2));
	return min(RMQ[x][k],RMQ[y+1-(1<<k)][k]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();T=read();
	for(int i=1;i<=n;i++){
		a[i]=b[i]=read();
	}
	sort(b+1,b+n+1);
	int tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++){
		a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	}
	m=tot;
	GetSA();
	GetHeight();
	ST();
	while(T--){
		int x=read(),y=read();
		printf("%d\n",Ask(x,y));
	}
	return 0;
}