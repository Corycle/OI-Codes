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
const int N=1e5+5;
const int M=21;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans,f[N][M];
int n,m,L,R,a[N],sum[N];
void Add(int pos){Ans+=sum[a[pos]];sum[a[pos]]++;}
void Del(int pos){sum[a[pos]]--;Ans-=sum[a[pos]];}
void GetAns(int l,int r){
	while(L>l)Add(--L);
	while(R<r)Add(++R);
	while(L<l)Del(L++);
	while(R>r)Del(R--);
}
void Solve(int K,int l,int r,int ql,int qr){
	int mid=(l+r)>>1,Max=min(mid,qr),pos=0;
	for(int i=ql;i<=Max;i++){
		GetAns(i,mid);
		if(f[mid][K]>f[i-1][K-1]+Ans){
			f[mid][K]=f[i-1][K-1]+Ans;
			pos=i;
		}
	}
	if(l<mid)Solve(K,l,mid-1,ql,pos);
	if(r>mid)Solve(K,mid+1,r,pos,qr);
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();L=1;R=0;
	for(int i=1;i<=n;i++)a[i]=read();
	memset(f,0x3f,sizeof(f));f[0][0]=0;
	for(int i=1;i<=m;i++)Solve(i,1,n,1,n);
	printf("%lld",f[n][m]);
	return 0;
}