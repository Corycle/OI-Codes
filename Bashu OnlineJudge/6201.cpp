/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<bitset>
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
const int N=10000005;
const int M=1005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int cnt,blk,Siz;
bitset<M>tmp,Now,b[M];
struct Node{int x,y;}a[N];
int p[N],vis[N],pos[N],prime[N];
bool cmp(Node A,Node B){
	return A.y!=B.y?A.y<B.y:A.x<B.x;
}
int Pow(int x,int y){
	int ans=1,tot=x;
	while(y){
		if(y&1)ans=1ll*ans*tot%Mod;
		tot=1ll*tot*tot%Mod;
		y>>=1;
	}
	return ans;
}
void Prepare(int maxn){
	p[1]=1;
	for(int i=2;i<=maxn;i++){
		if(!vis[i]){
			prime[++cnt]=i;p[i]=i;
			pos[i]=cnt;Siz+=(i<=blk);
		}
		for(int j=1;j<=cnt&&1ll*i*prime[j]<=maxn;j++){
			p[i*prime[j]]=max(p[i],prime[j]);
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)break;
		}
	}
}
bool Divide(int x,bitset<M>&now){
	bool flag=0;now.reset();
	if(p[x]>blk)x/=p[x];
	while(x!=1){
		int i=p[x],num=0;
		while(x%i==0){x/=i;num++;}
		if(num&1){now[pos[i]]=1;flag=1;}
	}
	return flag;
}
int Insert(bitset<M> now){
	for(int i=1;i<=Siz;i++){
		if(now[i]){
			if(b[i][i])now^=b[i];
			else{b[i]=now;return 1;}
		}
	}
	return 0;
}
void Solve1(int l,int r){
	int tot1=0,tot2=0,num=0;
	for(int i=l;i<=r;i++)a[++num]=(Node){i,p[i]};
	sort(a+1,a+num+1,cmp);
	for(int i=1;i<=Siz;i++)b[i].reset();
	for(int i=1;i<=num;i++){
		Divide(a[i].x,Now);
		if(a[i].y<=blk)tot1+=Insert(Now);
		else if(a[i].y!=a[i-1].y){tot2++;tmp=Now;}
		else {Now^=tmp;tot1+=Insert(Now);}
	}
	printf("%d\n",Pow(2,r-l+1-tot1-tot2));
}
void Solve2(int l,int r){
	int tot=0;
	for(int i=1;i<=cnt&&prime[i]<=r;i++){
		if(r/prime[i]!=(l-1)/prime[i])tot++;
	}
	printf("%d\n",Pow(2,r-l+1-tot));
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	blk=sqrt(1e7);Prepare(1e7);
	while(T--){
		int l=read(),r=read();
		if(r-l<=6000)Solve1(l,r);
		else Solve2(l,r);
	}
	return 0;
}