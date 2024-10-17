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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,ans,k,tot;
int s[N],c[N],pos[N],b[N*2];
struct ques{
	int l,r,id,x;
}q[N];
bool cmp1(ques x,ques y){
	if(pos[x.l]==pos[y.l])return x.r<y.r;
	return pos[x.l]<pos[y.l];
}
bool cmp2(ques x,ques y){
	return x.id<y.id;
}
int lowbit(int x){
	return x&(-x);
}
void Add(int x,int y){
	for(int i=x;i<=n;i+=lowbit(i)){
		c[i]+=y;
	}
}
int Ask(int x){
	int tmp=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		tmp+=c[i];
	}
	return tmp;
}
void update(int p,int addv){
	if(addv==1){
		ans-=Ask(tot)-Ask(s[p]);
		Add(s[p],-1);
	}
	if(addv==2){
		ans+=Ask(tot)-Ask(s[p]);
		Add(s[p],1);
	}
	if(addv==3){
		ans-=Ask(s[p]-1);
		Add(s[p],-1);
	}
	if(addv==4){
		ans+=Ask(s[p]-1);
		Add(s[p],1);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	int blk=(int)(sqrt(n));
	for(int i=1;i<=n;i++){
		b[++tot]=s[i]=read();
		pos[i]=(i-1)/blk+1;
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=n;i++){
		s[i]=lower_bound(b+1,b+tot+1,s[i])-b;
	}
	m=read();
	for(int i=1;i<=m;i++){
		q[i].id=i;
		q[i].l=read();
		q[i].r=read();
	}
	sort(q+1,q+m+1,cmp1);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		for(;r>q[i].r;r--)update(r,1);
		for(;r<q[i].r;r++)update(r+1,2);
		for(;l<q[i].l;l++)update(l,3);
		for(;l>q[i].l;l--)update(l-1,4);
		q[i].x=ans;
	}
	sort(q+1,q+m+1,cmp2);
	for(int i=1;i<=m;i++){
		printf("%d\n",q[i].x);
	}
	return 0;
}