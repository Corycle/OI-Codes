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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll ans,a[N];
int n,top,root,st[N],pos[N];
struct Tree{int l,r,sum;}t[N];
void Build(){//建树模板 
	for(int i=1;i<=n;i++){
		while(top&&a[st[top]]>a[i])top--;
		int pre=st[top];
		t[i].l=t[pre].r;
		t[pre].r=i;
		st[++top]=i;
	}
	root=t[0].r;
}
void DFS(int x){//统计答案 
	t[x].sum=1;
	if(t[x].l)DFS(t[x].l);
	if(t[x].r)DFS(t[x].r);
	t[x].sum+=t[t[x].l].sum+t[t[x].r].sum;
	ans=max(ans,a[x]*t[x].sum);
}
int main(){
	int size=40<<20;//40M
//	__asm__ ("movl  %0, %%esp\n"::"r"((char*)malloc(size)+size));//调试用这个
	__asm__ ("movq %0,%%rsp\n"::"r"((char*)malloc(size)+size));//提交用这个
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	Build();DFS(root);
	printf("%lld\n",ans);
	exit(0);//手工开栈不能 return 0; 
}