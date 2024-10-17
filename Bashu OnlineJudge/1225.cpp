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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int c[100005],n,m;
struct cows{
	int s,e,num,cnt;
}a[100005];
int lowbit(int x){
	return (x&(-x));
}
void Add(int x,int y){
	for(int i=x;i<=m;i+=lowbit(i)){
		c[i]+=y;
	}
}
int Ask(int x){
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		ans+=c[i];
	}
	return ans;
}
bool cmp1(cows x,cows y){
	if(x.s!=y.s)return x.s<y.s;
	return x.e>y.e;
}
bool cmp2(cows x,cows y){
	return x.num<y.num;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(1){
		n=read();
		if(n==0)break;
		memset(c,0,sizeof(c));
		memset(a,0,sizeof(a));
		m=-inf;
		for(int i=1;i<=n;i++){
			a[i].num=i;
			a[i].s=read()+1;
			a[i].e=read()+1;
			m=max(m,a[i].e);
		}
		sort(a+1,a+n+1,cmp1);
		for(int i=1;i<=n;i++){
			if(a[i].s==a[i-1].s&&a[i].e==a[i-1].e)a[i].cnt=a[i-1].cnt;
			else a[i].cnt=Ask(m)-Ask(a[i].e-1);
			Add(a[i].e,1);
		}
		sort(a+1,a+n+1,cmp2);
		for(int i=1;i<=n;i++){
			printf("%d ",a[i].cnt);
		}
		printf("\n");
	}
	return 0;
}