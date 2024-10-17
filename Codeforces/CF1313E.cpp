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
const int Mod=998244353;
const int Mul=13131;
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int n,m,P[N],F1[N],F2[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct String{
	char s[N];
	int Hash[N];
	int GetHash(int l,int r){return mod(Hash[r]-1ll*Hash[l-1]*P[r-l+1]%Mod+Mod);}
	void Init(int n){Hash[0]=1;for(int i=1;i<=n;i++)Hash[i]=mod(1ll*Hash[i-1]*Mul%Mod+s[i]);}
}A,B,S;
struct Tree{
	ll c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){x++;for(;x<N;x+=lowbit(x))c[x]+=y;}
	ll Ask(int x){x++;ll ans=0;for(;x>=1;x-=lowbit(x))ans+=c[x];return ans;}
}t1,t2;
void Update(int x,int f){int pos=m-F2[x]-1;t1.Add(pos,f);t2.Add(pos,F2[x]*f);}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	P[0]=1;for(int i=1;i<N;i++)P[i]=1ll*P[i-1]*Mul%Mod;
	scanf("%s%s%s",A.s+1,B.s+1,S.s+1);
	A.Init(n);B.Init(n);S.Init(m);
	for(int i=1,l=0,r=0;i<=n;i++){
		l=1;r=n-i+1;while(l<=r){int mid=(l+r)>>1;if(S.GetHash(1,mid)==A.GetHash(i,i+mid-1)){F1[i]=mid;l=mid+1;}else r=mid-1;}F1[i]=min(F1[i],m-1);
		l=1;r=i;while(l<=r){int mid=(l+r)>>1;if(S.GetHash(m-mid+1,m)==B.GetHash(i-mid+1,i)){F2[i]=mid;l=mid+1;}else r=mid-1;}F2[i]=min(F2[i],m-1);
	}
	for(int i=1,j=1;i<=n;i++){
		while(j<=min(i+m-2,n))Update(j++,1);
		Ans+=t2.Ask(F1[i])+t1.Ask(F1[i])*(F1[i]-m+1);
		Update(i,-1);
	}
	printf("%lld\n",Ans);
	return 0;
}
