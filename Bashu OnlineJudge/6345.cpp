/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<queue>
#include<stack>
#include<map>
#define ll long long
using namespace std;
const ll inf=0x3f3f3f3f;
const ll N=100005;
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
ll n,k,Ans,flag;
ll a[N],s1[N],s2[N],h[N][3];
bool Check1(ll i){return a[i-1]+a[i-2]>a[i];}
bool Check2(ll i){
	if(a[i-1]+a[i-2]>a[i]&&a[i-4]+a[i-5]>a[i-3])return 1;
	if(a[i-1]+a[i-3]>a[i]&&a[i-4]+a[i-5]>a[i-2])return 1;
	if(a[i-1]+a[i-4]>a[i]&&a[i-3]+a[i-5]>a[i-2])return 1;
	if(a[i-1]+a[i-5]>a[i]&&a[i-3]+a[i-4]>a[i-2])return 1;
	if(a[i-2]+a[i-3]>a[i]&&a[i-4]+a[i-5]>a[i-1])return 1;
	if(a[i-2]+a[i-4]>a[i]&&a[i-3]+a[i-5]>a[i-1])return 1;
	if(a[i-2]+a[i-5]>a[i]&&a[i-3]+a[i-4]>a[i-1])return 1;
	if(a[i-3]+a[i-4]>a[i]&&a[i-2]+a[i-5]>a[i-1])return 1;
	if(a[i-3]+a[i-5]>a[i]&&a[i-2]+a[i-4]>a[i-1])return 1;
	if(a[i-4]+a[i-5]>a[i]&&a[i-2]+a[i-3]>a[i-1])return 1;
	return 0;
}
void DFS(ll depth,ll x,ll y,ll z,ll i){
	if(depth==9){
		flag=1;
		if(a[i-h[2][0]]+a[i-h[3][0]]<=a[i-h[1][0]])flag=0;
		if(a[i-h[2][1]]+a[i-h[3][1]]<=a[i-h[1][1]])flag=0;
		if(a[i-h[2][2]]+a[i-h[3][2]]<=a[i-h[1][2]])flag=0;
		return;
	}
	if(x)h[4-x][0]=depth,DFS(depth+1,x-1,y,z,i),h[4-x][0]=0;if(flag)return;
	if(y)h[4-y][1]=depth,DFS(depth+1,x,y-1,z,i),h[4-y][1]=0;if(flag)return;
	if(z)h[4-z][2]=depth,DFS(depth+1,x,y,z-1,i),h[4-z][2]=0;if(flag)return;
}
bool Check3(ll i){
	flag=0;
	DFS(0,3,3,3,i);
	return flag;
}
namespace Subtask1{
	void Solve(){
		Ans=-1;
		for(ll i=3;i<=n;i++){
			if(Check1(i))Ans=a[i]+a[i-1]+a[i-2];
			s1[i]=Ans;
		}
	}
}
namespace Subtask2{
	void Solve(){
		Ans=-1;
		for(ll i=6;i<=n;i++){
			if(Check1(i)&&s1[i-3]!=-1)Ans=max(Ans,a[i]+a[i-1]+a[i-2]+s1[i-3]);
			if(Check2(i))Ans=max(Ans,a[i]+a[i-1]+a[i-2]+a[i-3]+a[i-4]+a[i-5]);
			s2[i]=Ans;
		}
	}
}
namespace Subtask3{
	void Solve(){
		Ans=-1;
		for(ll i=9;i<=n;i++){
			if(Check1(i)&&s2[i-3]!=-1)Ans=max(Ans,a[i]+a[i-1]+a[i-2]+s2[i-3]);
			if(Check2(i)&&s1[i-6]!=-1)Ans=max(Ans,a[i]+a[i-1]+a[i-2]+a[i-3]+a[i-4]+a[i-5]+s1[i-6]);
			if(Check3(i))Ans=max(Ans,a[i]+a[i-1]+a[i-2]+a[i-3]+a[i-4]+a[i-5]+a[i-6]+a[i-7]+a[i-8]);
		}
	}
}
int main(){
//	freopen("triangle.in","r",stdin);
//	freopen("triangle.out","w",stdout);
	n=read(),k=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	sort(a+1,a+n+1);
	if(k>=1)Subtask1::Solve(); 
	if(k>=2)Subtask2::Solve();
	if(k>=3)Subtask3::Solve();
	printf("%lld",Ans);
	return 0;
}