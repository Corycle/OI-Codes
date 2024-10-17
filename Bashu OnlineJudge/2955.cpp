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
#define lson num<<1,l,mid
#define rson num<<1|1,mid+1,r
using namespace std;
const int inf=0x3f3f3f3f;
const int N=10000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,nxt[N],T;
char a[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(1){
		n=read();
		if(!n)break;
		memset(nxt,0,sizeof(nxt));
		scanf("%s",a+1);
		for(int i=2,j=0;i<=n;i++){
			while(j>0&&a[i]!=a[j+1])j=nxt[j];
			if(a[i]==a[j+1])j++;
			nxt[i]=j;
		}
		printf("Test case #%d\n",++T);
		for(int i=2;i<=n;i++){
			if(i%(i-nxt[i])==0&&i/(i-nxt[i])>1){
				printf("%d %d\n",i,i/(i-nxt[i]));
			}
		}
		printf("\n");
	}
	return 0;
}