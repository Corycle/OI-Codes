/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
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
const int N=1e6+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,top,Answer,a[N],st[N],L[N],R[N],sum1[N],sum2[N],Ans[N];
int mod(int x){return x>=Mod?x-Mod:x;}
void Update(int l,int r,int t1,int t2){
	if(l>r)return;
	sum1[l]=mod(sum1[l]+t1);
	sum2[l]=mod(sum2[l]+t2);
	sum1[r+1]=mod(sum1[r+1]-t1+Mod);
	sum2[r+1]=mod(sum2[r+1]-t2+Mod);
}
int main(){
//	freopen("fight.in","r",stdin);
//	freopen("fight.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	st[top=0]=0;
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]<a[i])top--;
		L[i]=st[top];st[++top]=i;
	}
	st[top=0]=n+1;
	for(int i=n;i>=1;i--){
		while(top&&a[st[top]]<=a[i])top--;
		R[i]=st[top];st[++top]=i;
	}
	for(int i=1;i<=n;i++)a[i]%=Mod;
	for(int i=1;i<=n;i++){
		int A=i-L[i]-1,B=R[i]-i-1;
		if(A<B)swap(A,B);
		Update(1,B,0,a[i]);
		Update(B+1,A+1,1ll*(B+1)*a[i]%Mod,0);
		Update(A+2,A+B+1,1ll*(A+B+2)*a[i]%Mod,mod(Mod-a[i]));
	}
	for(int i=1;i<=n;i++){
		sum1[i]=mod(sum1[i]+sum1[i-1]);
		sum2[i]=mod(sum2[i]+sum2[i-1]);
		Ans[i]=mod(sum1[i]+1ll*i*sum2[i]%Mod);
		Answer^=Ans[i];
	}
	printf("%d",Answer);
	return 0;
}