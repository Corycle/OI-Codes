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
const int M=1<<18;
const ull Mul=131;
const int N=105;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
char s[N];
int n,m,Sta;
ull P[N],sum[M];
map<ull,ull>num;
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	scanf("%s",s);
	P[0]=1;Sta=(1<<n)-1;
	for(int i=1;i<=n*2;i++)P[i]=P[i-1]*Mul;
	for(int i=1;i<=Sta;i++)sum[i]=sum[i>>1]+(i&1);
	for(int S=0;S<=Sta;S++){
		int l=1,r=n;
		ull Hash1=0,Hash2=0;
		for(int i=0;i<n;i++){
			if(((S>>i)&1)==1)Hash1+=s[i]*P[l++];
			if(((S>>i)&1)==0)Hash2+=s[i]*P[r--];
		}
		num[Hash1-Hash2]++;
	}
	for(int T=0;T<=Sta;T++){
		int l=n-sum[T]+1,r=n-sum[T];
		ull Hash1=0,Hash2=0;
		for(int i=0;i<n;i++){
			if(((T>>i)&1)==1)Hash1+=s[i+n]*P[l++];
			if(((T>>i)&1)==0)Hash2+=s[i+n]*P[r--];
		}
		Ans+=num[Hash2-Hash1];
	}
	printf("%lld",Ans/2);
	return 0;
}