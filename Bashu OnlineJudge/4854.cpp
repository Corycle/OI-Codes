/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
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
const int N=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
map<int,int>num;
int n,m,a[N],Ans[N];
int main(){
//	freopen("div.in","r",stdin);
//	freopen("div.out","w",stdout);
	n=read();m=read();Ans[0]=n;
	for(int i=1;i<=m;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		for(int j=1;1ll*j*j<=a[i]&&j<=n;j++){
			if(a[i]%j)continue;
			Ans[num[j]]--;num[j]++;Ans[num[j]]++;
			if(a[i]!=j*j&&a[i]/j<=n){
				Ans[num[a[i]/j]]--;
				num[a[i]/j]++;
				Ans[num[a[i]/j]]++;
			}
		}
	}
	for(int i=0;i<=m;i++)printf("%d\n",Ans[i]);
	return 0;
}