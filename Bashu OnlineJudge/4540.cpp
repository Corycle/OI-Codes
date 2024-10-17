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
const int N=500005;
const int p=13;
int read(){
	int a=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){a=a*10+c-'0';c=getchar();}
	return a*f;
}
ll ans;
int n,l,r,mid;
int Hash[N],s[N],b[N];
char a[N];
void Build(){
	b[0]=1;
	for(int i=1;i<=500000;i++)b[i]=b[i-1]*p;
	for(int i=1;i<=n;++i)Hash[i]=Hash[i-1]*p+a[i]-'0';
	for(int i=n;i;--i)s[i]=s[i+1]*p-(a[i]-'0')+1;
}
bool Check(int l1,int r1,int l2,int r2){
	return (Hash[r1]-Hash[l1-1]*b[r1-l1+1]==s[l2]-s[r2+1]*b[r2-l2+1]);
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	cin>>n;
	scanf("%s",a+1);
	Build();
	for(int i=1;i<n;++i){
		if(a[i]==a[i+1])continue;
		l=1;
		if(i<n-i)r=i;
		else r=n-i;
		while(r>=l){
			mid=(l+r)>>1;
			if(Check(i-mid+1,i,i+1,i+mid))l=mid+1;
			else r=mid-1;
		}
		ans+=r;
	}
	printf("%d",ans);
	return 0;
}