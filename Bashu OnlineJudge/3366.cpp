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
#define inf 0x3f3f3f3f
#define ll long long 
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
string a[10005],k;
int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	int n=read();
	for(int i=1;i<=n;i++)cin>>a[i];
	cin>>k;
	sort(a+1,a+n+1);
	int len=k.length();
	for(int i=1;i<=n;i++){
		bool flag=true;
		for(int j=0;j<len;j++){
			if(k[j]!=a[i][j]){
				flag=false;
				break;
			}
		}
		if(flag)cout<<a[i]<<endl;
	}
	return 0;
}