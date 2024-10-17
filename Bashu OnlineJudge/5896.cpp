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
const int inf=2147483647;
const int N=100005;
const int M=20;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll Ans;
int a[N],b[N],f[N];
int n,m,A,B,P,id1,id2,Min;
bool cmp(int x,int y){return a[x]<a[y];}
struct Trie{
	int tot;
	struct Tree{
		int id,ch[2];
		void Init(){id=ch[0]=ch[1]=0;}
	}t[N*20];
	void Init(){t[tot=1].Init();}
	void Insert(int x){
		int p=1;
		for(int i=30;i>=0;i--){
			int c=(a[x]>>i)&1;
			if(!t[p].ch[c])t[t[p].ch[c]=++tot].Init();
			p=t[p].ch[c];
		}
		t[p].id=x;
	}
	void Query(int x){
		int p=1;
		for(int i=30;i>=0;i--){
			int c=(a[x]>>i)&1;
			if(t[p].ch[c])p=t[p].ch[c];
			else p=t[p].ch[c^1];
		}
		int y=t[p].id;
		if(Min>(a[x]^a[y])){
			Min=(a[x]^a[y]);
			id1=x;id2=y;
		}
	}
}tree;
void Divide(int l,int r,int len){
	if(l>=r||len<0)return;
	int cnt0=0,cnt1=0;
	for(int i=l;i<=r;i++){
		if(((a[b[i]]>>len)&1)==0)cnt0++;
		if(((a[b[i]]>>len)&1)==1)cnt1++;
	}
	if(cnt0&&cnt1){
		Min=inf;tree.Init();
		for(int i=l;i<l+cnt0;i++)tree.Insert(b[i]);
		for(int i=l+cnt0;i<=r;i++)tree.Query(b[i]);
		Ans+=Min;
	}
	Divide(l,l+cnt0-1,len-1);
	Divide(r-cnt1+1,r,len-1);
}
int main(){
//	freopen("fight.in","r",stdin);
//	freopen("fight.out","w",stdout);
	n=read();a[1]=read();
	A=read();B=read();P=read();
	if(A==1&&B==0)printf("0");
	else if(A==1&&B==1){
		int Maxn=min(P-1,n-1);
		for(int i=30;i>=0;i--){
			int t=(Maxn>>i)&1;
			Ans+=(1ll<<i)*(f[i+1]+t);
			f[i]=f[i+1]<<1|t;
		}
		printf("%lld",Ans);
	}
	else{
		for(int i=2;i<=n;i++)a[i]=(1ll*a[i-1]*A+B)%P;
		for(int i=1;i<=n;i++)b[i]=i;
		sort(b+1,b+n+1,cmp);
		Divide(1,n,30);
		printf("%lld",Ans);
	}
	return 0;
}