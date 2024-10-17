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
const int N=400005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,num,m,ans;
int fir[N],sec[N],height[N];
int a[N],b[N],Rank[N],sum[N],sa[N];
void GetSA(){
	int *x=Rank,*y=sec,p;
	for(int i=0;i<=m;i++)sum[i]=0;
	for(int i=1;i<=n;i++)sum[x[i]=a[i]]++;
	for(int i=1;i<=m;i++)sum[i]+=sum[i-1];
	for(int i=n;i>=1;i--)sa[sum[x[i]]--]=i;
	for(int j=1;p<n;j*=2,m=p){
		p=0;
		for(int i=n-j+1;i<=n;i++)y[++p]=i;
		for(int i=1;i<=n;i++)if(sa[i]-j>0)y[++p]=sa[i]-j;
		for(int i=1;i<=n;i++)fir[i]=x[y[i]];
		for(int i=0;i<=m;i++)sum[i]=0;
		for(int i=1;i<=n;i++)sum[fir[i]]++;
		for(int i=1;i<=m;i++)sum[i]+=sum[i-1];
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
		if(Rank[i]==1)height[Rank[i]]=0;
		else{
			int j=sa[Rank[i]-1];
			while(a[i+k]==a[j+k])k++;
			height[Rank[i]]=k;
			if(k!=0)k--;
		}
	}
}
bool Check(int len){
	int tot=0;
	for(int i=2;i<=n;i++){
		if(height[i]>=len){
			tot++;
			if(tot==num-1)return true;
		}
		else tot=0;
	}
	return false;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();num=read();
	for(int i=1;i<=n;i++)a[i]=read();
	m=200;
	GetSA();
	GetHeight();
	int l=1,r=n;
	while(l<=r){
		int mid=(l+r)>>1;
		if(Check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d",ans);
	return 0;
}