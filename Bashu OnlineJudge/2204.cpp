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
#include<set>
#define ll long long
#define set_it 
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m,Ans,a[N],c[N],num[N];
void Insert(int x){if(x>0){if(!c[x])Ans++;c[x]++;}}
void Delete(int x){if(x>0){c[x]--;if(!c[x])Ans--;}}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	n=read();m=read();
	for(int i=1;i<=n;i++){
		num[a[i]=read()]++;
		Insert(a[i]-num[a[i]]+1);
	}
	while(m--){
		int x=read(),y=read();
		Delete(a[x]-num[a[x]]+1);
		num[a[x]]--;a[x]=y;num[a[x]]++;
		Insert(a[x]-num[a[x]]+1);
		printf("%d\n",n-Ans);
	}
	return 0;
}
