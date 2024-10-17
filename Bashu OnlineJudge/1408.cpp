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
int f[50005],n,t;
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	j=0;k=t=2;
	f[1]=1;
	for(i=2;i<=50000;i++){
		j++;
		f[i]=(f[i-1]+t)%10000;
		if(j==k){
			j=0;
			k++;
			t=t*2%10000;
		}
	}
	while(scanf("%d",&n)!=EOF)printf("%d\n",f[n]);
	return 0;
}