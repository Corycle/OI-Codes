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
const int N=2000005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,a[N];
char s1[N],s2[N];
int Ask(){
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
	return i;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	scanf("%s%s",s1+1,s2+1);
	n=strlen(s1+1);
	for(int i=1;i<=n;i++){
		a[i]=a[i+n]=s1[i+n]=s1[i];
	}
	int p1=Ask();
	for(int i=1;i<=n;i++){
		a[i]=a[i+n]=s2[i+n]=s2[i];
	}
	int p2=Ask();
	for(int i=1;i<=n;i++){
		if(s1[p1+i-1]!=s2[p2+i-1]){
			printf("No\n");
			return 0;
		}
	}
	printf("Yes\n");
	for(int i=1;i<=n;i++){
		printf("%c",s1[p1+i-1]);
	}
	return 0;
}