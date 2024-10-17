#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5,Lim=2e5,M=17;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,tot,a[N],root[N];
struct Tree{int l,r,sum;}t[N*20];
int Insert(int x,int p,int l,int r){
	int y=++tot;t[y]=t[x];t[y].sum++;
	if(l==r)return y;int mid=(l+r)>>1;
	if(p<=mid)t[y].l=Insert(t[x].l,p,l,mid);
	else t[y].r=Insert(t[x].r,p,mid+1,r);
	return y;
}
int Ask(int x,int y,int L,int R,int l,int r){
	if(R<l||L>r)return 0;
	if(L<=l&&r<=R)return t[y].sum-t[x].sum;
	int mid=(l+r)>>1,ans=0;
	ans+=Ask(t[x].l,t[y].l,L,R,l,mid);
	ans+=Ask(t[x].r,t[y].r,L,R,mid+1,r);
	return ans;
}
bool Find(int l1,int r1,int l2,int r2){
	int l=max(l2,0),r=min(r2,Lim);
	if(l<=r)return Ask(root[l1],root[r1],l,r,1,Lim);
	return false;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		root[i]=Insert(root[i-1],a[i],1,Lim);
	}
	while(m--){
		int b=read(),x=read(),l=read(),r=read(),ans=0;
		for(int i=M;i>=0;i--){
			int p=ans+((((b>>i)&1)^1)<<i);
			if(Find(l-1,r,p-x,p+(1<<i)-1-x))ans=p;
			else ans+=((b>>i)&1)<<i;
		}
		printf("%d\n",ans^b);
	}
	return 0;
}
/*
同样是按照数位一位一位的贪心，因为加了一个x， 
所以我们考虑对于所有的ai+x与b的按位异或。 

假设我们已经处理到b的第i位（转换成二进制），假设是1（0同理）， 

那么我们只需要查找是否存在aj+x使得其二进制第i位数字是0， 
显然我们已经处理了前i-1位了，设当前结果是ans， 
那么我们需要查找的数的大小就是在区间[ans-x,ans+(1<<i)-1-x]， 
手算一下就知道这个区间里的数字的第i位加了x后就都是0， 
 
那么现在我们就是要在a[1]...a[n]中找出是否存在于[ans-x,ans+(1<<i)-1-x]的数字， 
两个区间范围限制，用主席树模板一套就好了。 
*/