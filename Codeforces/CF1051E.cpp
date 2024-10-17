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
int F[N],P[N],p1[N],p2[N];
int mod(int x){return x>=Mod?x-Mod:x;}
struct String{
	char s[N];
	int n,Hash[N];
	int GetHash(int l,int r){return mod(Hash[r]-1ll*Hash[l-1]*P[r-l+1]%Mod+Mod);}
	void Read(){
		scanf("%s",s+1);n=strlen(s+1);
		for(int i=1;i<=n;i++)Hash[i]=mod(1ll*Hash[i-1]*Mul%Mod+s[i]);
	}
}A,L,R;
struct Tree{
	int c[N];
	int lowbit(int x){return x&(-x);}
	void Add(int x,int y){for(;x<N;x+=lowbit(x))c[x]=mod(c[x]+y);}
	int Ask(int x){int ans=0;for(;x>=1;x-=lowbit(x))ans=mod(ans+c[x]);return ans;}
	int Query(int l,int r){return mod(Ask(r)-Ask(l-1)+Mod);}
}tree;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	A.Read();L.Read();R.Read();tree.Add(A.n+1,1);
	P[0]=1;for(int i=1;i<N;i++)P[i]=1ll*P[i-1]*Mul%Mod;
	for(int i=A.n,l=0,r=0;i>=1;i--){
		if(i+L.n-1<=A.n){
			l=1;r=L.n;
			while(l<=r){int mid=(l+r)>>1;if(A.GetHash(i,i+mid-1)==L.GetHash(1,mid)){p1[i]=mid;l=mid+1;}else r=mid-1;}
			if(p1[i]==L.n||A.s[i+p1[i]]>L.s[p1[i]+1])p1[i]=L.n;else p1[i]=L.n+1;
		}
		else continue;
		if(i+R.n-1<=A.n){
			l=1;r=R.n;
			while(l<=r){int mid=(l+r)>>1;if(A.GetHash(i,i+mid-1)==R.GetHash(1,mid)){p2[i]=mid;l=mid+1;}else r=mid-1;}
			if(p2[i]==R.n||A.s[i+p2[i]]<R.s[p2[i]+1])p2[i]=R.n;else p2[i]=R.n-1;
		}
		else p2[i]=A.n-i+1;
		if(A.s[i]=='0'){p1[i]=max(p1[i],1);p2[i]=min(p2[i],1);}
		if(p1[i]<=p2[i]){F[i]=tree.Query(i+p1[i],i+p2[i]);tree.Add(i,F[i]);}
	}
	printf("%d\n",F[1]);
	return 0;
}
