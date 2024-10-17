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
const int N=300005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N*2];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)a[i]=a[i+n]=read();
	int i=1,j=2,k=0;
	while(i<=n&&j<=n&&k<=n){
		if(a[i+k]==a[j+k])k++;
		else{
			if(a[i+k]<a[j+k])j=j+k+1;
			else i=i+k+1;
			if(i==j)j++;
			k=0;
		}
	}
	i=min(i,j);
	for(int j=1;j<=n;j++){
		printf("%d ",a[i+j-1]);
	}
	return 0;
}