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
const ull Mul=1313131;
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans1,Ans2;
ull P[N],Hash[N];
int n,m,a[N],b[N],num[N],lst[N];
ll Sum(ll x){return x*(x-1)/2;}
bool cmp(int x,int y){
	return Hash[x]!=Hash[y]?Hash[x]<Hash[y]:x<y;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();P[0]=1;
	for(int i=1;i<=n;i++)P[i]=P[i-1]*Mul;
	for(int i=1;i<=n;i++){a[i]=read();lst[a[i]]=i;num[a[i]]++;}
	for(int i=1;i<=n;i++){
		b[i]=i;
		Hash[i]=Hash[i-1]+P[a[i]];
		if(i==lst[a[i]])Hash[i]-=P[a[i]]*num[a[i]];
	}
	Ans2=inf;
	sort(b+1,b+n+1,cmp);
	for(int i=1;i<=n;i++){
		int l=i,r=i;
		while(r<n&&Hash[b[r+1]]==Hash[b[l]])r++;
		Ans1+=Sum(r-l+1);
		for(int j=l;j<=r;j++){
			while(l<j&&b[j]-b[l]>=(n+1)/2)l++;
			Ans2=min((int)Ans2,abs(n-2*(b[j]-b[l])));
			if(l>i)Ans2=min((int)Ans2,abs(n-2*(b[j]-b[l-1])));
		}
		i=r;
	}
	printf("%lld %lld",Ans1,Ans2);
	return 0;
}