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
const int Mod=1e9+7;
const int N=100005;
const int M=22;
inline char getch(){
    static char buf[10000],*p1=buf,*p2=buf;
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
__attribute__((optimize("Ofast")))
inline int read(){
	int s=0,f=1;char c=getch();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getch();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getch();}
	return s*f;
}
int a[N];
int n,ans1,ans2,type;
void Print(){
	if(type==1)printf("%d",ans1);
	if(type==2)printf("%d",ans2);
	if(type==3)printf("%d\n%d",ans1,ans2);
}
inline int mod(int x){return x>=Mod?x-Mod:x;}
namespace Task1{
	void Main(){
		for(int l=1;l<=n;l++){
			int Max=a[l];
			for(int r=l;r<=n;r++){
				Max=max(Max,a[r]);
				ans1=mod(ans1+1ll*((a[l]^a[r])%Mod)*Max%Mod);
				ans2=mod(ans2+1ll*((a[l]^a[r])>Max)*Max%Mod);
			}
		}
		Print();
	}
}
namespace Task2{
	int num,sta[M];
	struct Tree{
		int ch[2],sum;
		void Init(){ch[0]=ch[1]=sum=0;}
	};
	struct Trie{
		int tot;
		Tree t[N*M];
		void Init(){t[tot=1].Init();}
		void Insert(int x){
			int p=1;
			for(int i=num;i>=0;i--){
				int c=(x>>i)&1;
				if(!t[p].ch[c]){
					t[p].ch[c]=++tot;
					t[tot].Init();
				}
				p=t[p].ch[c];
				t[p].sum++;
			}
		}
		int Ask(int x,int Max){
			int p=1,ans=0;
			for(int i=num;i>=0;i--){
				int c=(x>>i)&1;
				if((Max>>i)&1)p=t[p].ch[c^1];
				else{
					ans+=t[t[p].ch[c^1]].sum;
					p=t[p].ch[c];
				}
			}
			return ans;
		}
	}tree;
	int sum[N][M][2];
	inline int Sum(int l,int r,int x,int c){
		return sum[r][x][c]-sum[l-1][x][c];
	}
	void Divide(int l,int r){
		if(l==r)return;
		int mid=(l+r)>>1,Max=0;
		Divide(l,mid);
		Divide(mid+1,r);
		int pos1=mid;tree.Init();Max=0;
		for(int i=mid;i>=l;i--){
			int dlt=0;Max=max(Max,a[i]);
			while(pos1<r&&a[pos1+1]<=Max)tree.Insert(a[++pos1]);
			for(int j=0;j<=num;j++){
				int c=(a[i]>>j)&1;
				dlt=mod(dlt+1ll*(c^0)*sta[j]%Mod*Sum(mid+1,pos1,j,0)%Mod);
				dlt=mod(dlt+1ll*(c^1)*sta[j]%Mod*Sum(mid+1,pos1,j,1)%Mod);
			}
			ans1=mod(ans1+1ll*dlt*Max%Mod);
			ans2=mod(ans2+1ll*tree.Ask(a[i],Max)*Max%Mod);
		}
		int pos2=mid+1;tree.Init();Max=0;
		for(int i=mid+1;i<=r;i++){
			int dlt=0;Max=max(Max,a[i]);
			while(pos2>l&&a[pos2-1]<Max)tree.Insert(a[--pos2]);
			for(int j=0;j<=num;j++){
				int c=(a[i]>>j)&1;
				dlt=mod(dlt+1ll*(c^0)*sta[j]%Mod*Sum(pos2,mid,j,0)%Mod);
				dlt=mod(dlt+1ll*(c^1)*sta[j]%Mod*Sum(pos2,mid,j,1)%Mod);
			}
			ans1=mod(ans1+1ll*dlt*Max%Mod);
			ans2=mod(ans2+1ll*tree.Ask(a[i],Max)*Max%Mod);
		}
	}
	void Main(){
		int Max=0;
		for(int i=1;i<=n;i++)Max=max(Max,a[i]);
		num=(int)(log(Max)/log(2));
		for(int i=1;i<=n;i++){
			for(int j=0;j<=num;j++){
				sum[i][j][0]=sum[i-1][j][0];
				sum[i][j][1]=sum[i-1][j][1];
				sum[i][j][(a[i]>>j)&1]++;
			}
		}
		for(int i=0;i<=num;i++)sta[i]=(1<<i)%Mod;
		Divide(1,n);
		Print();
	}
}
int main(){
//	freopen("english.in","r",stdin);
//	freopen("english.out","w",stdout);
	n=read();type=read();
	for(int i=1;i<=n;i++)a[i]=read();
//	if(n<=1000){Task1::Main();return 0;}
	Task2::Main();
	return 0;
}