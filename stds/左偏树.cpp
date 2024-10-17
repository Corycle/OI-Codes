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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
struct tree{int l,r,dis,data;}t[N];
int Merge(int x,int y){
	if(!x||!y)return x+y;
	if(t[x].data<t[y].data)swap(x,y);
	t[x].r=Merge(t[x].r,y);
	if(t[t[x].l].dis<t[t[x].r].dis)swap(t[x].l,t[x].r);
	if(!t[x].r)t[x].dis=0;
	else t[x].dis=t[t[x].r].dis+1;
	return x;
}
int main(){
//	freopen("duliu.in","r",stdin);
//	freopen("duliu.out","w",stdout);
	
	return 0;
}
