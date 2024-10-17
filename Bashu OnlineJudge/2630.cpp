#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#define ll long long
using namespace std;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,m,num1=1,num2=1,cnt,ans;
struct node{
	ll x,bj;
}p[4005];
bool cmp(node x,node y){
	return x.x>y.x;
}
int main(){
//	freopen("cut.in","r",stdin);
//	freopen("cut.out","w",stdout);
	n=read();m=read();
	for(ll i=1;i<n;i++)p[++cnt]=(node){read(),1};
	for(ll i=1;i<m;i++)p[++cnt]=(node){read(),2};
	sort(p+1,p+cnt+1,cmp);
	for(ll i=1;i<=cnt;i++){
		if(p[i].bj==1){
			ans+=p[i].x*num2;
			num1++;
		}
		if(p[i].bj==2){
			ans+=p[i].x*num1;
			num2++;
		}
	}
	printf("%lld",ans);
	return 0;
}
/*
8:30-12:00
2:30-6:00
*/