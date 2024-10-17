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
const ll inf=0x3f3f3f3f;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ll n,t,Ans,cnt[N],lst[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	read();n=read();
	scanf("%s",s+1);
	cnt[t]++;
	for(ll i=1;i<=n;i++){
		lst[i]=lst[i-1];
		if(s[i]=='1'){
			t^=1;
			Ans+=cnt[t^1];
			Ans-=i-lst[i];
			lst[i]=i;
		}
		else Ans+=cnt[t^1]-(lst[i]!=0);
		cnt[t]++;
	}
	printf("%lld",Ans);
	return 0;
}