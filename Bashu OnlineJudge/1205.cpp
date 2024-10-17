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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
const int M=100005;
int l1,l2,m,ans;
struct tree{
	int l,r,sum,bj;
}t[800005];
bool p[200005];
void Build(int l,int r,int num){
	int mid=(l+r)/2;
	t[num].l=l;
	t[num].r=r;
	if(l==r)return;
	Build(l,mid,num*2);
	Build(mid+1,r,num*2+1);
}
void pushdown(int num){
	t[num*2].bj=t[num].bj;
	t[num*2+1].bj=t[num].bj;
	t[num].bj=0;
}
void Add(int x,int y,int num,int z){
	int l=t[num].l,r=t[num].r;
	if(l>y||r<x)return;
	if(x<=l&&r<=y){
		t[num].bj=z;
		return;
	}
	if(l==r)return;
	if(t[num].bj)pushdown(num);
	Add(x,y,num*2,z);
	Add(x,y,num*2+1,z);
}
void Ask(int num){
	int l=t[num].l,r=t[num].r;
//	cout<<l<<" "<<r<<endl;
	if(t[num].bj!=0){
		if(p[t[num].bj]==0){
			p[t[num].bj]=1;
			ans++;
		}
		return;
	}
	if(l==r)return;
	if(t[num].bj)pushdown(num);
	Ask(num*2);
	Ask(num*2+1);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	l1=read()+M;l2=read()+M;m=read();
	l2--;
	Build(l1,l2,1);
	for(i=1;i<=m;i++){
		j=read()+M;k=read()+M;
		k--;
		if(j>k)continue;
		Add(j,k,1,i);
	}
//	cout<<endl;
	Ask(1);
	printf("%d",ans);
	return 0;
}
/*
考虑负数
*/