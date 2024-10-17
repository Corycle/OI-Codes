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
const int N=10005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int S,n,ans[N],c[N*200];
struct node{
	int a,b,type,data;
}q[N*20],tmp[N*20];
bool cmp(node x,node y){
	if(x.a!=y.a)return x.a<y.a;
	if(x.b!=y.b)return x.b<y.b;
	return x.type<y.type;
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
	int tot=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		tot+=c[i];
	}
	return tot;
}
void CDQ(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	int i=l,j=mid+1;
	int num=l;
	while(i<=mid&&j<=r){
		if(cmp(q[i],q[j])){
			if(q[i].type==1)Add(q[i].b,q[i].data);
			tmp[num++]=q[i++];
		}
		else{
			if(q[j].type==2)ans[q[j].data]+=Ask(q[j].b);
			if(q[j].type==3)ans[q[j].data]-=Ask(q[j].b);
			tmp[num++]=q[j++];
		}
	}
	int p=i;
	while(i<=mid){
		tmp[num++]=q[i++];
	}
	while(j<=r){
		if(q[j].type==2)ans[q[j].data]+=Ask(q[j].b);
		if(q[j].type==3)ans[q[j].data]-=Ask(q[j].b);
		tmp[num++]=q[j++];
	}
	for(int x=l;x<p;x++){
		if(q[x].type==1)Add(q[x].b,-q[x].data);
	}
	for(int i=l;i<=r;i++)q[i]=tmp[i];
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	S=read();n=read();
	int cnt=0,qnt=0;
	int op=0;
	while(scanf("%d",&op)!=EOF){
		if(op==1){
			int x=read(),y=read(),z=read();
			q[++cnt]=(node){x,y,1,z};
		}
		if(op==2){
			int a=read(),b=read(),x=read(),y=read();
			ans[++qnt]+=(x-a+1)*(y-b+1)*S;
			q[++cnt]=(node){x,y,2,qnt};
			q[++cnt]=(node){x,b-1,3,qnt};
			q[++cnt]=(node){a-1,y,3,qnt};
			q[++cnt]=(node){a-1,b-1,2,qnt};
		}
		if(op==3)break;
	}
	CDQ(1,cnt);
	for(int i=1;i<=qnt;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}