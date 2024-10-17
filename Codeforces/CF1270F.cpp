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
const int N=2e5+5;
const int M=450;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char s[N];
int n,m,sum[N],pos[N],num[N*M];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);m=sqrt(n);
	for(int i=1;i<=n;i++){sum[i]=sum[i-1]+(s[i]=='1');if(s[i]=='1')pos[sum[i]]=i;}
	for(int k=1;k<=m;k++){
		for(int i=0;i<=n;i++){Ans+=num[k*sum[i]-i+n];num[k*sum[i]-i+n]++;}
		for(int i=0;i<=n;i++)num[k*sum[i]-i+n]=0;
	}
	pos[sum[n]+1]=n+1;
	for(int l=0;l<=n;l++){
		for(int k=1;k<=n/m&&sum[n]-sum[l]>=k;k++){//k=sum[r]-sum[l];
			int L=max(pos[sum[l]+k]-l,k*m+1),R=pos[sum[l]+k+1]-l-1;
			if(L<=R)Ans+=R/k-(L-1)/k;
		}
	}
	printf("%lld\n",Ans);
	return 0;
}
