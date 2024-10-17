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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
int fa[N];
struct edge{
	int s,t,num;
	int data,type;
}e[N*2],q[N*2];
struct tree{
	int ch[2],fa,num;
	int aux,rev,data;
}t[N*2];
bool cmp1(edge x,edge y){
	return x.data<y.data;
}
bool cmp2(edge x,edge y){
	if(x.s!=y.s)return x.s<y.s;
	return x.t<y.t;
}
bool cmp3(edge x,edge y){
	return x.num<y.num;
}
int Find(int x){
	return x==fa[x]?x:fa[x]=Find(fa[x]);
}
void Pushup(int x){
	t[x].num=x;
	if(t[t[t[x].ch[0]].num].data>t[t[x].num].data)t[x].num=t[t[x].ch[0]].num;
	if(t[t[t[x].ch[1]].num].data>t[t[x].num].data)t[x].num=t[t[x].ch[1]].num;
}
void Pushdown(int x){
	if(t[x].rev){
		t[x].rev^=1;
		t[t[x].ch[0]].rev^=1;
		t[t[x].ch[1]].rev^=1;
		swap(t[x].ch[0],t[x].ch[1]);
	}
}
void Rotate(int x){
	int y=t[x].fa;int z=t[y].fa;
	int l=(x!=t[y].ch[0]);int r=l^1;
	if(t[y].aux){
		if(y==t[z].ch[0])t[z].ch[0]=x;
		else t[z].ch[1]=x;
	}
	else{
		t[y].aux=1;
		t[x].aux=0;
	}
	t[x].fa=z;t[y].fa=x;
	t[t[x].ch[r]].fa=y;
	t[y].ch[l]=t[x].ch[r];
	t[x].ch[r]=y;
	Pushup(y);Pushup(x);
}
void Splay(int x){
	Pushdown(x);
	while(t[x].aux){
		int y=t[x].fa;int z=t[y].fa;
		if(t[y].aux)Pushdown(z);
		Pushdown(y);Pushdown(x);
		if(t[y].aux){
			if(t[y].ch[0]==x^t[z].ch[0]==y)Rotate(x);
			else Rotate(y);
		}
		Rotate(x);
	}
}
void Access(int x){
	int y=0;
	while(x){
		Splay(x);
		t[t[x].ch[1]].aux=0;
		t[x].ch[1]=y;
		t[y].aux=1;
		t[y].fa=x;
		Pushup(x);
		y=x;
		x=t[x].fa;
	}
}
void Evert(int x){
	Access(x);
	Splay(x);
	t[x].rev^=1;
	Pushup(x);
}
void Link(int x,int y){
	Evert(x);
	t[x].fa=y;
}
void Cut(int x,int y){
	Evert(x);
	Access(y);
	Splay(y);
	t[t[y].ch[0]].aux=0;
	t[t[y].ch[0]].fa=0;
	t[y].ch[0]=0;
	Pushup(y);
}
int Ask(int x,int y){
	Evert(x);
	Access(y);
	Splay(y);
	return t[y].num;
}
int GetNum(int x,int y){
	int l=1,r=m;
	while(l<=r){
		int mid=(l+r)>>1;
		if(e[mid].s<x||(e[mid].s==x&&e[mid].t<y))l=mid+1;
		else if(e[mid].s==x&&e[mid].t==y)return mid;
		else r=mid-1;
	}
}
void Kruscal(){
	int num=1;
	sort(e+1,e+m+1,cmp3);
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		if(e[i].type)continue;
		int x=Find(e[i].s);
		int y=Find(e[i].t);
		if(x==y)continue;
		num++;
		fa[x]=y;
		Link(e[i].s,i+n);
		Link(e[i].t,i+n);
		if(num==n)return;
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();m=read();
	int Q=read();
	for(int i=1;i<=m;i++){
		e[i].s=read();
		e[i].t=read();
		e[i].data=read();
		if(e[i].s>e[i].t)swap(e[i].s,e[i].t);
	}
	sort(e+1,e+m+1,cmp1);
	for(int i=1;i<=m;i++){
		e[i].num=i;
		t[n+i].num=n+i;
		t[n+i].data=e[i].data;
	}
	sort(e+1,e+m+1,cmp2);
	for(int i=1;i<=Q;i++){
		q[i].type=read();
		q[i].s=read();
		q[i].t=read();
		if(q[i].type==2){
			if(q[i].s>q[i].t)swap(q[i].s,q[i].t);
			int id=GetNum(q[i].s,q[i].t);
			q[i].num=e[id].num;
			e[id].type=1;
		}
	}
	Kruscal();
	for(int i=Q;i>=1;i--){
		int dlt=Ask(q[i].s,q[i].t);
		if(q[i].type==1){
			q[i].data=t[dlt].data;
		}
		else{
			if(t[dlt].data>t[q[i].num+n].data){
				Cut(e[dlt-n].s,dlt);
				Cut(e[dlt-n].t,dlt);
				Link(q[i].s,q[i].num+n);
				Link(q[i].t,q[i].num+n);
			}
		}
	}
	for(int i=1;i<=Q;i++){
		if(q[i].type==1){
			printf("%d\n",q[i].data);
		}
	}
	return 0;
}