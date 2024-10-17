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
const int N=20005;
const int M=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,blk,cnt,qnt,ans;
int s[N],b[N],pos[N],answer[N],used[M];
struct node{
	int x,y,lst;
}c[N];
struct ques{
	int l,r,t,id;
}q[N];
bool cmp(ques x,ques y){
	if(pos[x.l]==pos[y.l]){
		if(pos[x.r]==pos[y.r])return x.t<y.t;
		return pos[x.r]<pos[y.r];
	}
	return pos[x.l]<pos[y.l];
}
void Change(int x,int y,int l,int r){
	if(l<=x&&x<=r){
		used[s[x]]--;
		if(used[s[x]]==0)ans--;
		s[x]=y;
		if(used[s[x]]==0)ans++;
		used[s[x]]++;
	}
	else s[x]=y;
}
void update(int p,int addv){
	used[s[p]]+=addv;
	if(addv==1&&used[s[p]]==1)ans++;
	if(addv==-1&&used[s[p]]==0)ans--;
}
void Solve(){
	int l=1,r=0,head=0;//head 是当前询问指针 
	for(int i=1;i<=qnt;i++){
		while(head>q[i].t){//还原修改操作
			Change(c[head].x,c[head].lst,l,r);
			head--;
		}
		while(head<q[i].t){//补齐修改操作
			head++;
			Change(c[head].x,c[head].y,l,r);
		}
		while(r<q[i].r)update(++r,1);
		while(l>q[i].l)update(--l,1);
		while(r>q[i].r)update(r--,-1);
		while(l<q[i].l)update(l++,-1);
		answer[q[i].id]=ans;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	blk=sqrt(n);
	for(int i=1;i<=n;i++){
		s[i]=b[i]=read();
		pos[i]=(i-1)/blk+1;
	}
	for(int i=1;i<=m;i++){
		char op[3];
		scanf("%s",op);
		if(op[0]=='R'){
			cnt++;
			c[cnt].x=read();c[cnt].y=read();
			c[cnt].lst=b[c[cnt].x];//上一次的颜色
			b[c[cnt].x]=c[cnt].y;
		}
		if(op[0]=='Q'){
			qnt++;
			q[qnt].t=cnt;
			q[qnt].id=qnt;
			q[qnt].l=read();
			q[qnt].r=read();
		}
	}
	sort(q+1,q+qnt+1,cmp);
	Solve();
	for(int i=1;i<=qnt;i++){
		printf("%d\n",answer[i]);
	}
	return 0;
}