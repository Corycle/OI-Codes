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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,top;
int st[N],pos[N];
struct Tree{int l,r,fa,id;}t[N];
struct node{int key,val,id;}a[N];
bool cmp(node x,node y){
	return x.key<y.key;
}
void Build(){
	sort(a+1,a+n+1,cmp);//排序 
	for(int i=1;i<=n;i++){//按key值排序后依次插入 
		while(top&&a[st[top]].val>a[i].val)top--;
		//找到单调栈中比 a[i].val大的最后一个点 
		int pre=st[top];//该点即为插入点的父亲 
		t[i].fa=pre;//处理父亲 
		t[t[pre].r].fa=i;
		t[i].l=t[pre].r;//pre的右节点变成i的左节点 
		t[pre].r=i;
		st[++top]=i;//入栈 
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		a[i].id=i;
		a[i].key=read();
		a[i].val=read();
	}
	Build();
	//当key和value一定时，笛卡尔树是唯一的 
	printf("YES\n");//不可能存在 NO 的情况 
	for(int i=1;i<=n;i++){
		pos[a[i].id]=i;//排序前的每一个点排序后的位置 
		t[i].id=a[i].id;//在树中也存入 
	}
	for(int i=1;i<=n;i++){
		int x=pos[i];
		printf("%d %d %d\n",t[t[x].fa].id,t[t[x].l].id,t[t[x].r].id);
	}
	return 0;
}