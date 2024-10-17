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
const int N=505;
const int M=5005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
/*
	方法二 
*/
int n,m,ans1,ans2;
int rd[N],cd[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	while(1){
		n=read();m=read();
		if(n+m==0)break;
		memset(rd,0,sizeof(rd));
		memset(cd,0,sizeof(cd));
		ans1=ans2=0;
		for(int i=1;i<=m;i++){
			int x=read(),y=read();
			cd[x]++;rd[y]++;
		}
		for(int i=1;i<=n;i++){
			if(!cd[i])ans1++;
			if(!rd[i])ans2++;
		}
		printf("%d\n",max(ans1,ans2));
	}
	return 0;
}