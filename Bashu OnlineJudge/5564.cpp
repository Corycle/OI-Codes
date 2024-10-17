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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Flag,a[N];
struct Tree{
	ll sum0,sum1,l0,r0,ans;
	ll dl[2][2],dr[2][2],fl[3],fr[3];
	void Init(){
		l0=r0=sum0=sum1=ans=0;
		memset(dl,0,sizeof(dl));
		memset(dr,0,sizeof(dr));
		memset(fl,0,sizeof(fl));
		memset(fr,0,sizeof(fr));
	}
	void Prepare(int x){
		Init();
		if(x)dl[0][1]=dr[0][1]=fl[0]=fr[0]=sum1=ans=1;
		else dl[1][0]=dr[1][0]=sum0=l0=r0=1;
	}
	friend Tree operator+(Tree A,Tree B){
		Tree C;C.Init();
		C.sum0=A.sum0+B.sum0;
		C.sum1=A.sum1+B.sum1;
		C.l0=(!A.sum1)?A.l0+B.l0:A.l0;
		C.r0=(!B.sum1)?A.r0+B.r0:B.r0;
		
		C.ans=A.ans+B.ans;
		C.ans+=A.dr[1][0]*B.dl[0][1];
		C.ans+=A.dr[1][1]*B.dl[0][0];
		C.ans+=A.dr[0][0]*(B.dl[0][1]+B.dl[1][1]);
		C.ans+=A.dr[0][1]*(B.dl[0][0]+B.dl[1][0]);
		if(A.r0)C.ans+=A.r0*(B.fl[0]+B.fl[1]+B.fl[2])-B.fl[0];
		if(B.l0)C.ans+=B.l0*(A.fr[0]+A.fr[1]+A.fr[2])-A.fr[0];
		
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				C.dl[i][j]+=A.dl[i][j];
				C.dr[i][j]+=B.dr[i][j];
				if(i>=A.sum0)C.dl[i][j]+=B.dl[i-A.sum0][j^(A.sum1&1)];
				if(i>=B.sum0)C.dr[i][j]+=A.dr[i-B.sum0][j^(B.sum1&1)];
			}
		}
		
		for(int i=0;i<3;i++){
			C.fl[i]+=A.fl[i];
			C.fr[i]+=B.fr[i];
			if(!A.sum1)C.fl[min(2ll,i+A.sum0)]+=B.fl[i];
			if(!B.sum1)C.fr[min(2ll,i+B.sum0)]+=A.fr[i];
		}
		if(A.sum1==1&&B.l0){C.fl[min(2ll,A.sum0+B.l0)]++;C.fl[2]+=B.l0-1;}
		if(B.sum1==1&&A.r0){C.fr[min(2ll,B.sum0+A.r0)]++;C.fr[2]+=A.r0-1;}
		
		return C;
	}
};
Tree Ans;
struct Segment_Tree{
	Tree t[N*4];
	void Build(int p,int l,int r){
		if(l==r){t[p].Prepare(a[l]);return;}
		int mid=(l+r)>>1;
		Build(lson);Build(rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Change(int x,int p,int l,int r){
		if(x<l||x>r)return;
		if(l==r){t[p].Prepare(a[l]);return;}
		int mid=(l+r)>>1;
		Change(x,lson);Change(x,rson);
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void Query(int x,int y,int p,int l,int r){
		if(y<l||x>r)return;
		if(x<=l&&r<=y){
			if(!Flag)Ans=t[p];
			else Ans=Ans+t[p];
			Flag=1;
			return;
		}
		int mid=(l+r)>>1;
		Query(x,y,lson);Query(x,y,rson);
	}
}tree;
ll Sum(ll x){return (x+1)*x/2;}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	tree.Build(1,1,n);
	m=read();
	while(m--){
		int op=read();
		if(op==1){
			int x=read();a[x]^=1;
			tree.Change(x,1,1,n);
		}
		if(op==2){
			Ans.Init();Flag=0;
			int l=read(),r=read();
			tree.Query(l,r,1,1,n);
			printf("%lld\n",Sum(r-l+1)-Ans.ans);
		}
	}
	return 0;
}