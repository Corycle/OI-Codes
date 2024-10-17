/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x7f7f7f7f7f7f7f7f;
const ll N=2000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll SumB[N],SumR[N];
ll Sum1[N],Sum2[N];
int main(){
//	freopen("sushi.in","r",stdin);
//	freopen("sushi.out","w",stdout);
	ll T=read();
	while(T--){
		scanf("%s",s+1);
		ll n=strlen(s+1),ans=inf;
		for(ll i=1;i<=n;i++)s[i+n]=s[i];
		for(ll i=1;i<=n*2;i++)SumB[i]=SumB[i-1]+(s[i]=='B');
		for(ll i=1;i<=n*2;i++)SumR[i]=SumR[i-1]+(s[i]=='R');
		for(ll i=1;i<=n*2;i++)Sum1[i]=Sum1[i-1]+(s[i]=='R')*SumB[i];
		for(ll i=1;i<=n*2;i++)Sum2[i]=Sum2[i-1]+(s[i]=='B')*SumR[i];
		ll mid=n/2;
		for(ll l=1;l<=n;l++){
			ll r=l+n-1;mid++;
			ll sum=0;
			if(s[mid]=='R'){
				ll sumR=SumR[mid-1]-SumR[l-1];
				sum+=SumB[mid]*sumR-(Sum1[mid-1]-Sum1[l-1]);
				sumR=SumR[r]-SumR[mid];
				sum+=(Sum1[r]-Sum1[mid])-SumB[mid]*sumR;
//				for(ll j=l;j<mid;j++){
//					if(s[j]=='R')sum+=SumB[mid]-SumB[j-1];
//				}
//				for(ll j=mid+1;j<=r;j++){
//					if(s[j]=='R')sum+=SumB[j]-SumB[mid];
//				}
			}
			if(s[mid]=='B'){
				ll sumB=SumB[mid-1]-SumB[l-1];
				sum+=SumR[mid]*sumB-(Sum2[mid-1]-Sum2[l-1]);
				sumB=SumB[r]-SumB[mid];
				sum+=(Sum2[r]-Sum2[mid])-SumR[mid]*sumB;
//				for(ll j=l;j<mid;j++){
//					if(s[j]=='B')sum+=SumR[mid]-SumR[j-1];
//				}
//				for(ll j=mid+1;j<=r;j++){
//					if(s[j]=='B')sum+=SumR[j]-SumR[mid];
//				}
			}
			ans=min(ans,sum);
		}
		printf("%lld\n",ans);
	}
	return 0;
}