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
char s[N];
int n,m,t;
int a[N],b[N],sum[N],height[N],bj[N];
int Rank[N],fir[N],sec[N],sa[N];
void GetSA(){
	int p=0,*x=Rank,*y=sec;
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
void Prepare(){
	n=0;
	memset(sa,0,sizeof(sa));
	memset(fir,0,sizeof(fir));
	memset(sec,0,sizeof(sec));
	memset(Rank,0,sizeof(Rank));
	memset(height,0,sizeof(height));
}
bool Check(int maxx){
	int i=1;
	while(i<n){
		i++;
		if(height[i]>=maxx){
			int st=i;
			while(i<=n&&height[i]>=maxx)i++;
			for(int j=1;j<=t;j++)bj[j]=0;
			for(int j=st-1;j<=i-1;j++)bj[b[sa[j]]]++;
			int f=1;
			for(int j=1;j<=t;j++){
				if(!bj[j]){
					f=0;
					break;
				}
			}
			if(f)return true;
		}
	}
	return false;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		Prepare();
		t=read();m=300;
		for(int j=1;j<=t;j++){
			scanf("%s",s+1);
			int len=strlen(s+1);
			for(int i=1;i<=len;i++){
				a[++n]=s[i];
				b[n]=j;
			}
			a[++n]=m++;b[n]=0;
			for(int i=1;i<=len;i++){
				a[++n]=s[len-i+1];
				b[n]=j;
			}
			a[++n]=m++;b[n]=0;
		}
		n--;m=2000;
		GetSA();
		GetHeight();
		int l=1,r=1000,ans=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(Check(mid)){
				ans=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
