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
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,c[N],ans;
struct node{
	int a,b,c,bj;
}t[N],t1[N],t2[N];
int lowbit(int x){
	return x&(-x);
}
void Add(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=y;
	}
}
int Ask(int x){
	int tot=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		tot+=c[i];
	}
	return tot;
}
void CDQ2(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ2(l,mid);
	CDQ2(mid+1,r);
	int i=l,j=mid+1;
	for(int k=l;k<=r;k++){
		if(j>r||t1[i].b<t1[j].b&&i<=mid){
			if(t1[i].bj==1)Add(t1[i].c,1);
			t2[k]=t1[i++];
		}
		else{
			if(t1[j].bj==2)ans+=Ask(t1[j].c-1);
			t2[k]=t1[j++];
		}
	}
	for(i=l;i<=mid;i++){
		if(t1[i].bj==1)Add(t1[i].c,-1);
	}
	for(i=l;i<=r;i++)t1[i]=t2[i];
}
void CDQ1(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ1(l,mid);
	CDQ1(mid+1,r);
	int i=l,j=mid+1;
	for(int k=l;k<=r;k++){
		if(j>r||t[i].a<t[j].a&&i<=mid){
			t[i].bj=1;
			t1[k]=t[i++];
		}
		else{
			t[j].bj=2;
			t1[k]=t[j++];
		}
	}
	for(i=l;i<=r;i++)t[i]=t1[i];
	CDQ2(l,r);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)t[i].a=read();
	for(int i=1;i<=n;i++)t[i].b=read();
	for(int i=1;i<=n;i++)t[i].c=read();
	CDQ1(1,n);
	printf("%d",ans);
	return 0;
}
