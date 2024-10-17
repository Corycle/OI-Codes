#include<cstdio>
#include<algorithm>
using namespace std;
int n;
long long ans;
int t;
struct node{
	int left,right,c;
} tree[4*40005*2];
struct edge{
	int left,right,h;
} a[40005];
int p[2*40005];
bool cmp(edge e1,edge e2){
	return e1.h<e2.h;
}
int erfen(int l,int r,int x){ 
	while(l<=r){
		int mid=(l+r)/2;
		if(p[mid]==x)return mid;
		else if(p[mid]>x)r=mid-1;
		else l=mid+1;
	}
	return 0;
}
void change(int now,int l,int r,int x) { //裸的区间修改
	if(tree[now].right<l||tree[now].left>r) return;
	if(tree[now].left>=l&&tree[now].right<=r){
		tree[now].c=x;
		return;
	}
	int mid=(tree[now].left+tree[now].right)/2;
	if(tree[now].c){
		tree[now*2].c=tree[now].c;
		tree[now*2+1].c=tree[now].c;
		tree[now].c=0;
	}
	if(mid>=r)change(now*2,l,r,x);
	else if(mid<=l)change(now*2+1,l,r,x);
	else{
		change(now*2,l,r,x);
		change(now*2+1,l,r,x);
	}
}
void built(int now,int l,int r){
	tree[now].left=l;
	tree[now].right=r;
	tree[now].c=0;
	if(l==r-1)return;
	built(now*2,l,(l+r)/2);
	built(now*2+1,(l+r)/2,r);//*右界要包括mid，因为一个矩形所占的位置肯定大于一个点，如果不包括mid，会漏掉一些矩形；
}
void quest(int now){
	if(tree[now].c){
		ans+=(p[tree[now].right]-p[tree[now].left])*(long long)tree[now].c;
		return;
	}
	if(tree[now].right==tree[now].left+1) return;
	quest(now*2);
	quest(now*2+1);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&a[i].left,&a[i].right,&a[i].h);
		p[++t]=a[i].left;
		p[++t]=a[i].right;
	}//离散化顶点
	sort(p+1,p+1+2*n);
	sort(a+1,a+n+1,cmp);
	built(1,1,n*2);
	for(int i=1;i<=n;i++){
		int l=erfen(1,2*n,a[i].left);
		int r=erfen(1,2*n,a[i].right);
		change(1,l,r,a[i].h);
	}
	quest(1);
	printf("%lld",ans);
}