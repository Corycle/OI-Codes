#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=50005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
struct Number{
	int a[N];
	void Init(){
		memset(a,0,sizeof(a));
		a[0]=1;
	}
	void Print(){
		for(int i=a[0];i>=1;i--){
			printf("%d",a[i]);
		}
		printf("\n");
	}
};
Number Multi(Number A,int B){
	for(int i=1;i<=A.a[0];i++)A.a[i]*=B;
	for(int i=1;i<=A.a[0];i++){
		A.a[i+1]+=A.a[i]/10;
		A.a[i]%=10;
		if(A.a[A.a[0]+1])A.a[0]++;
	}
	return A;
}
Number Plas(Number A,Number B){
	A.a[0]=max(A.a[0],B.a[0]);
	for(int i=1;i<=A.a[0];i++)A.a[i]+=B.a[i];
	for(int i=1;i<=A.a[0];i++){
		A.a[i+1]+=A.a[i]/10;
		A.a[i]%=10;
		if(A.a[A.a[0]+1])A.a[0]++;
	}
	return A;
}
Number Count(Number ans,int n,int m){
	if(n<m){
		Number res;
		res.Init();
		return res;
	}
	for(int i=n-m+1;i<=n;i++){
		ans=Multi(ans,i);
	}
	return ans;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int n=read(),m=read();
	Number ans1,ans2;
	ans1.Init();ans2.Init();
	ans1.a[1]=ans2.a[1]=1;
	
	ans1=Count(ans1,2,2);
	ans1=Count(ans1,n,n);
	ans1=Count(ans1,m,1);
	ans1=Count(ans1,n+1,1);
	ans1=Count(ans1,n+2,m-1);
	
	ans2=Count(ans2,n,n);
	ans2=Count(ans2,n+1,2);
	ans2=Count(ans2,n+3,m);
	
	Number ans=Plas(ans1,ans2);
	ans.Print();
	return 0;
}