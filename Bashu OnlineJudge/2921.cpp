#include<iostream>
#include<iomanip>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<ctime>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<queue>
#include<map>
#define inf 0x3f3f3f3f
using namespace std;
//struct _{};
//vector<_>_;
//stack<_>_;
//queue<_>_;
//deque<_>_;
//priority_queue<_>_;
//priority_queue<int,vector<int>,greater<int> >_;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char a[500005];
bool pd(int x){
	int i,j,k=0;
	for(i=1;i<=n;i++){
		if(a[i]=='1'){
			k++;
			i+=x-1;
		}
	}
	if(k<=m)return 1;
	return 0;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	n=read();m=read();
	scanf("%s",a+1);
	int l=0,r=n/m+1;
	while(l<=r){
		int mid=l+r>>1;
		if(pd(mid))r=mid-1;
		else l=mid+1;
	}
	printf("%d",l);
	return 0;
}