#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int M=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int l1,l2,n,m;
struct tree{
	int l,r,sum,bj;
}t[800005];
void Build(int l,int r,int num){
	int mid=(l+r)/2;
	t[num].l=l;
	t[num].r=r;
	if(l==r)return;
	Build(l,mid,num*2);
	Build(mid+1,r,num*2+1);
}
//void pushdown(int num){
//	if(t[num].bj==1){
//		t[num].bj=0;
//		t[num*2].bj=t[num*2+1].bj=1;
//		t[num*2].sum=t[num*2].r-t[num*2].l+1;
//		t[num*2+1].sum=t[num*2+1].r-t[num*2+1].l+1;
//	}
//}
void Add(int x,int y,int num){
	int l=t[num].l,r=t[num].r;
	if(x>r||y<l)return;
	if(t[num].bj==1)return;
	if(x<=l&&r<=y){
		t[num].bj=1;
		t[num].sum=r-l+1;
		return;
	}
//	pushdown(num);
	if(l<r){
		Add(x,y,num*2);
		Add(x,y,num*2+1);
	}
	t[num].sum=t[num*2].sum+t[num*2+1].sum;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	l1=read()+M;l2=read()+M;m=read();
	l2--;
	Build(l1,l2,1);
	n=l2-l1+1;
	while(m--){
		i=read()+M;j=read()+M;
		j--;
		if(i>j)continue;
		Add(i,j,1);
	}
	printf("%d",t[1].sum);
	return 0;
}