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
	int sum;
}t[400005];
void add(int x,int y,int z,int num,int l,int r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		t[num].sum+=z;
		return;
	}
	int mid=(l+r)>>1;
	add(x,y,z,lson);
	add(x,y,z,rson);
}
int ask(int x,int num,int l,int r){
	if(x<l||x>r)return 0;
	if(l==r){
		return t[num].sum;
	}
	int mid=(l+r)>>1;
	return ask(x,lson)+ask(x,rson)+t[num].sum;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	while(m--){
		int p=read();
		if(p==1){
			int x=read(),y=read();
			add(x,y,1,1,1,n);
		}
		if(p==2){
			int x=read();
			printf("%d\n",ask(x,1,1,n)%2);
		}
	}
	return 0;
}