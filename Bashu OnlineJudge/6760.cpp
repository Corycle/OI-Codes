#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
double k[N],b[N];
struct Tree{int num;}t[N*4];
double GetY(int x,int num){return k[num]*x+b[num];}
void Update(int x,int y,int num,int p,int l,int r){
	if(y<l||x>r)return;
	int mid=(l+r)>>1;
	if(x<=l&&r<=y){
		if(GetY(l,num)<=GetY(l,t[p].num)&&GetY(r,num)<=GetY(r,t[p].num))return;
		if(GetY(l,num)>=GetY(l,t[p].num)&&GetY(r,num)>=GetY(r,t[p].num)){t[p].num=num;return;}
		if(k[num]>k[t[p].num]){
			if(GetY(mid,num)>GetY(mid,t[p].num)){
				Update(x,y,t[p].num,lson);
				t[p].num=num;
			}
			else Update(x,y,num,rson);
		}
		else{
			if(GetY(mid,num)>GetY(mid,t[p].num)){
				Update(x,y,t[p].num,rson);
				t[p].num=num;
			}
			else Update(x,y,num,lson);
		}
		return;
	}
	Update(x,y,num,lson);
	Update(x,y,num,rson);
}
double Ask(int x,int p,int l,int r){
	if(x<l||x>r)return -inf;
	if(l==r)return GetY(x,t[p].num);
	int mid=(l+r)>>1;
	double ans=GetY(x,t[p].num);
	ans=max(ans,Ask(x,lson));
	ans=max(ans,Ask(x,rson));
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	m=read();
	while(m--){
		char s[10];
		scanf("%s",s);
		if(s[0]=='P'){
			n++;
			scanf("%lf%lf",&b[n],&k[n]);
			b[n]-=k[n];
			Update(1,1e5,n,1,1,1e5);
		}
		if(s[0]=='Q'){
			int x=read();
			printf("%d\n",(int)(Ask(x,1,1,1e5)/100));
		}
	}
	return 0;
}