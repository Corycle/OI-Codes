#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#include<ctime>
#include<vector>
#define inf 0x3f3f3f3f
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<long long,vector<long long>,greater<long long> >_;
long long read(){
	long long s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
long long mod,n,p,tot;
struct tree{
	long long maxx;
}t[800005];
void Add(long long x,long long y,long long num,long long l,long long r){
	long long mid=(l+r)>>1;
	if(x<l||r<x)return;
	if(l==r){
		t[num].maxx=y;
		return;
	}
	if(x<=mid)Add(x,y,lson);
	else Add(x,y,rson);
	t[num].maxx=max(t[num<<1].maxx,t[num<<1|1].maxx);
}
long long Ask(long long x,long long y,long long num,long long l,long long r){
	long long mid=(l+r)>>1;
	if(y<l||r<x)return 0;
	if(x<=l&&r<=y){
		return t[num].maxx;
	};
	return max(Ask(x,y,lson),Ask(x,y,rson));
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	long long i,j,k;
	n=read();mod=read();
	for(i=1;i<=n;i++){
		char qvq[1];
		scanf("%s",qvq);
		long long x=read();
		if(qvq[0]=='A'){
			tot++;
			Add(tot,(x+p)%mod,1,1,n);
		}
		else{
			p=Ask(tot-x+1,tot,1,1,n);
			printf("%lld\n",p);
		}
	}
	return 0;
}