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
#define ll long long
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
struct tree{
	int sum,bj;
}t[240005];
void pass(int z,int num,int l,int r){
	t[num].bj=z;
	t[num].sum=(z==1?r-l+1:0);
}
void pushdown(int num,int l,int r){
	int mid=(l+r)>>1;
	pass(t[num].bj,lson);
	pass(t[num].bj,rson);
	t[num].bj=0;
}
void update(int x,int y,int z,int num,int l,int r){
	if(x>r||y<l)return;
	if(x<=l&&r<=y){
		t[num].bj=z;
		t[num].sum=(z==1?r-l+1:0);
		return;
	}
	int mid=(l+r)>>1;
	if(t[num].bj!=0)pushdown(num,l,r);
	update(x,y,z,lson);
	update(x,y,z,rson);
	t[num].sum=t[num<<1].sum+t[num<<1|1].sum;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read()-1;m=read();
	while(m--){
		int p=read();
		int x=read(),y=read()-1;
		if(p==1){
			update(x,y,1,1,1,n);
		}
		if(p==2){
			update(x,y,-1,1,1,n);
		}
	}
	printf("%d",t[1].sum);
	return 0;
}