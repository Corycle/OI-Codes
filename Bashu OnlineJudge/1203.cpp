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
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,p;
struct tree{
	int maxx,bj;
}t[240005];
void pushdown(int num){
	t[num<<1].bj+=t[num].bj;
	t[num<<1|1].bj+=t[num].bj;
	t[num<<1].maxx+=t[num].bj;
	t[num<<1|1].maxx+=t[num].bj;
	t[num].bj=0;
}
int Ask(int x,int y,int num,int l,int r){
	int mid=l+r>>1;
	if(y<l||r<x)return 0;
	if(x<=l&&r<=y){
		return t[num].maxx;
	}
	if(t[num].bj)pushdown(num);
	return max(Ask(x,y,lson),Ask(x,y,rson));
}
void Add(int x,int y,int z,int num,int l,int r){
	int mid=l+r>>1;
	if(y<l||r<x)return;
	if(x<=l&&r<=y){
		t[num].bj+=z;
		t[num].maxx+=z;
		return;
	}
	if(t[num].bj)pushdown(num);
	Add(x,y,z,lson);
	Add(x,y,z,rson);
	t[num].maxx=max(t[num<<1].maxx,t[num<<1|1].maxx);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();p=read();m=read();
	for(i=1;i<=m;i++){
		int x=read(),y=read()-1,z=read();
		int num=Ask(x,y,1,1,n);
		if(num+z<=p){
			Add(x,y,z,1,1,n);
			printf("YES\n");
		}
		else printf("NO\n");
	}
	return 0;
}