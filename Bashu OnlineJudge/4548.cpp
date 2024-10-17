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
int n,maxx,ans[N],c[N*2];
struct Point{
	int a,b,c,num,ans;
}p[N],a[N];
bool same(Point x,Point y){
	return x.a==y.a&&x.b==y.b&&x.c==y.c;
}
bool cmp1(Point x,Point y){
	if(x.a!=y.a)return x.a<y.a;
	if(x.b!=y.b)return x.b<y.b;
	return x.c<y.c;
}
bool cmp2(Point x,Point y){
	if(x.b!=y.b)return x.b<y.b;
	return x.c<y.c;
}
int lowbit(int x){
	return x&(-x);
}
void Add(int x,int y){
	for(int i=x;i<=maxx;i+=lowbit(i)){
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
	sort(p+l,p+mid+1,cmp2);
	sort(p+mid+1,p+r+1,cmp2);
	int i=l,j=mid+1;
	while(i<=mid&&j<=r){
		if(p[i].b<=p[j].b){
			Add(p[i].c,p[i].num);
			i++;
		}
		else{
			p[j].ans+=Ask(p[j].c);
			j++;
		}
	}
	while(j<=r){
		p[j].ans+=Ask(p[j].c);
		j++;
	}
	for(int x=l;x<i;x++){
		Add(p[x].c,-p[x].num);
	}
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();maxx=read();
	for(int i=1;i<=n;i++){
		a[i].a=read();
		a[i].b=read();
		a[i].c=read();
	}
	sort(a+1,a+n+1,cmp1);
	int cnt=0,num=0;
	for(int i=1;i<=n;i++){
		num++;
		if(!same(a[i],a[i+1])){
			p[++cnt]=a[i];
			p[cnt].num=num;
			num=0;
		}
	}
	CDQ(1,cnt);
	for(int i=1;i<=cnt;i++){
		ans[p[i].ans+p[i].num-1]+=p[i].num;
	}
	for(int i=0;i<n;i++){
		printf("%d\n",ans[i]);
	}
	return 0;
}