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
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
map<int,int>a,sum;
vector<int>v[N*4];
struct Ques{
	int l,r,data;
}q[N];
struct Line{
	int p[35];
	void Add(int x){
		for(int i=30;i>=0;i--){
			if(x&(1<<i)){
				if(!p[i]){p[i]=x;break;}
				x^=p[i];
			}
		}
	}
	int Ask(){
		int ans=0;
		for(int i=30;i>=0;i--){
			if(ans<(ans^p[i]))ans^=p[i];
		}
		return ans;
	}
}st;
void Add(int x,int y,int z,int p,int l,int r){
	if(y<l||x>r)return;
	if(x<=l&&r<=y){
		v[p].push_back(z);
		return;
	}
	int mid=(l+r)>>1;
	Add(x,y,z,lson);
	Add(x,y,z,rson);
}
void Solve(int p,int l,int r,Line data){
	int num=v[p].size();
	for(int i=0;i<num;i++){
		data.Add(v[p][i]);
	}
	if(l==r){
		printf("%d\n",data.Ask());
		return;
	}
	int mid=(l+r)>>1;
	Solve(lson,data);
	Solve(rson,data);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		int x=read();
		if(x>0){
			sum[x]++;
			if(sum[x]==1){
				q[i].data=x;
				q[i].l=a[x]=i;
			}
		}
		if(x<0){
			x=-x;
			sum[x]--;
			if(sum[x]==0){
				q[a[x]].r=i;
				a[x]=0;
			}
		}
	}
	for(int i=1;i<=n;i++){
		if(q[i].l&&!q[i].r)q[i].r=n+1;
		if(q[i].l)Add(q[i].l,q[i].r-1,q[i].data,1,1,n);
	}
	Solve(1,1,n,st);
	return 0;
}