/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
#include<cstdio>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=500005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,Ans,a[N],ans[N];
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		int l=0,r=0;
		for(int j=i;j>=1&&a[j]%a[i]==0;j--)l=j;
		for(int j=i;j<=n&&a[j]%a[i]==0;j++)r=j;
		if(r-l>Ans){Ans=r-l;ans[ans[0]=1]=l;}
		else if(r-l==Ans)ans[++ans[0]]=l;
	}
	sort(ans+1,ans+ans[0]+1);
	ans[0]=unique(ans+1,ans+ans[0]+1)-ans-1;
	printf("%d %d\n",ans[0],Ans);
	for(int i=1;i<=ans[0];i++)printf("%d ",ans[i]);
	return 0;
}