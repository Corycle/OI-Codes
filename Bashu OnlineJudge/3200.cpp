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
#define ull unsigned ll
using namespace std;
const ll inf=0x3f3f3f3f;
const ull Mul=13131;
const ll N=1000005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
ull Hash[N];
ll n,ans,top,st[N],id[N];
int main(){
//	freopen("brackets.in","r",stdin);
//	freopen("brackets.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	for(ll i=1;i<=n;i++){
		if(top&&s[i]==st[top]){
			Hash[i]=Hash[id[top--]];
		}
		else{
			st[++top]=s[i];id[top]=i-1;
			Hash[i]=Hash[i-1]*Mul+s[i];
		}
	}
	Hash[++n]=0;
	sort(Hash+1,Hash+n+1);
	for(ll i=1,j=0;i<=n;i=j+1){
		j=i;
		while(j<n&&Hash[i]==Hash[j+1])j++;
		ll len=j-i+1;
		ans+=len*(len-1)/2;
	}
	printf("%lld",ans);
	return 0;
}