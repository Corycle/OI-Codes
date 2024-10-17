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
const int N=1000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char op[10];
int tot,n,l,r,a[N],q[N];
void Insert(int x){
	a[++n]=x;
	while(l<=r&&a[q[r]]<=x)r--;
	q[++r]=n;
}
void Pop(int pos){
	while(l<=r&&q[l]<=pos)l++;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		scanf("%s",op);
		if(op[0]=='n')Insert(read());
		if(op[0]=='l')Pop(++tot);
		if(op[0]=='q')printf("%d\n",a[q[l]]);
	}
	return 0;
}