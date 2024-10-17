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
const ll inf=0x3f3f3f3f;
const ll Mod=998244353;
const ll N=200005;
const ll Mul=29;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,Ans,P[N];
struct String{
	char s[N],ch[N];
	ll cnt,f[N],Hash1[N],Hash2[N];
	void Manacher(){
		ch[cnt]='&';
		for(ll i=1;i<=n;i++){
			ch[++cnt]='#';
			ch[++cnt]=s[i];
		}
		ch[++cnt]='#';
		ll k=0,Max=0;
		for(ll i=1;i<=cnt;i++){
			if(Max<=i)f[i]=1;
			else f[i]=min(f[k*2-i],Max-i);
			while(ch[i-f[i]]==ch[i+f[i]])f[i]++;
			if(i+f[i]>Max){Max=i+f[i];k=i;}
		}
		for(ll i=1;i<=cnt;i++)Ans=max(Ans,f[i]-1);
	}
	void Prepare(){
		scanf("%s",s+1);Manacher();
		for(ll i=1;i<=n;i++)Hash1[i]=(Hash1[i-1]*Mul%Mod+s[i]-'a'+1)%Mod;
		for(ll i=n;i>=1;i--)Hash2[i]=(Hash2[i+1]*Mul%Mod+s[i]-'a'+1)%Mod;
	}
	ll GetHash1(ll l,ll r){
		return (Hash1[r]-Hash1[l-1]*P[r-l+1]%Mod+Mod)%Mod;
	}
	ll GetHash2(ll l,ll r){
		return (Hash2[l]-Hash2[r+1]*P[r-l+1]%Mod+Mod)%Mod;
	}
}A,B;
ll Check(ll L,ll R){
	ll l=0,r=min(L,n-R+1),ans=0;
	while(l<=r){
		ll mid=(l+r)>>1;
		ll F1=A.GetHash1(L-mid,L-1);
		ll F2=B.GetHash2(R+1,R+mid);
		if(F1==F2){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	return ans*2;
}
void Solve(){
	for(ll i=1;i<=n*2+1;i++){
		ll len=max(A.f[i],B.f[i]);
		if(len==1)continue;
		ll L=(i-len+2)>>1,R=(i+len-2)>>1;
		if(A.f[i]>B.f[i])Ans=max(Ans,Check(L,R-1)+len-1);
		if(A.f[i]<B.f[i])Ans=max(Ans,Check(L+1,R)+len-1);
		if(A.f[i]==B.f[i]){
			Ans=max(Ans,Check(L+1,R)+len-1);
			Ans=max(Ans,Check(L,R+1)+len-1);
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();P[0]=1;
	for(ll i=1;i<=n*2+1;i++)P[i]=P[i-1]*Mul%Mod;
	A.Prepare();B.Prepare();Solve();
	printf("%lld",Ans);
	return 0;
}