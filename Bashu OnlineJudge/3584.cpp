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
const ll inf=0x3f3f3f3f;
const ll N=200005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m;
char s1[N],s2[N],s[N];
ll len1,len2,len,ans;
ll a[N],b[N],sum[N],height[N];
ll Rank[N],fir[N],sec[N],sa[N];
void GetSA(){
	ll p=0,*x=Rank,*y=sec;
	for(ll i=0;i<=m;i++)sum[i]=0;
	for(ll i=1;i<=n;i++)sum[x[i]=a[i]]++;
	for(ll i=1;i<=m;i++)sum[i]+=sum[i-1];
	for(ll i=n;i>=1;i--)sa[sum[x[i]]--]=i;
	for(ll j=1;p<n;j*=2,m=p){
		p=0;
		for(ll i=n-j+1;i<=n;i++)y[++p]=i;
		for(ll i=1;i<=n;i++)if(sa[i]-j>0)y[++p]=sa[i]-j;
		for(ll i=1;i<=n;i++)fir[i]=x[y[i]];
		for(ll i=0;i<=m;i++)sum[i]=0;
		for(ll i=1;i<=n;i++)sum[fir[i]]++;
		for(ll i=1;i<=m;i++)sum[i]+=sum[i-1];
		for(ll i=n;i>=1;i--)sa[sum[fir[i]]--]=y[i];
		swap(x,y);
		x[sa[1]]=p=1;
		for(ll i=2;i<=n;i++){
			if(y[sa[i-1]]!=y[sa[i]]||y[sa[i-1]+j]!=y[sa[i]+j])p++;
			x[sa[i]]=p;
		}
	}
	for(ll i=1;i<=n;i++)Rank[sa[i]]=i;
}
void GetHeight(){
	ll k=0;
	for(ll i=1;i<=n;i++){
		if(Rank[i]==1)height[Rank[i]]=0;
		else{
			ll j=sa[Rank[i]-1];
			while(a[i+k]==a[j+k])k++;
			height[Rank[i]]=k;
			if(k!=0)k--;
		}
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	ll minn=read();
	scanf("%s%s",s1+1,s2+1);
	len1=strlen(s1+1);
	len2=strlen(s2+1);
	for(ll i=1;i<=len1;i++)s[++n]=s1[i];
	s[++n]='&';
	for(ll i=1;i<=len2;i++)s[++n]=s2[i];
	for(ll i=1;i<=n;i++){
		a[i]=s[i];
		if(s[i]=='&')a[i]=93;
	}
	m=200;
	GetSA();
	GetHeight();
	for(ll i=1;i<=n;i++){
		ll t=inf;
		for(ll j=i+1;j<=n;j++){
			t=min(t,height[j]);
			if(t<minn)break;
			if((sa[i]<len1+1&&sa[j]>len1+1)||(sa[i]>len1+1&&sa[j]<len1+1))ans+=t-minn+1;
		}
	}
	printf("%lld",ans);
	return 0;
}