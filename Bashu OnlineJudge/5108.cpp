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
const int N=2005;
const int M=30;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int p[M];
char a[N],b[N];
int Check(){
	for(int i=0;i<=1000;i++){
		if(!('a'<=a[i]&&a[i]<='z')&&!('a'<=b[i]&&b[i]<='z')&&a[i]!=b[i])return 0;
		if(('a'<=a[i]&&a[i]<='z')&&!('a'<=b[i]&&b[i]<='z'))return 0;
		if(('a'<=b[i]&&b[i]<='z')&&!('a'<=a[i]&&a[i]<='z'))return 0;
		if(p[a[i]-'a'+1]&&p[a[i]-'a'+1]!=b[i]-'a'+1)return 0;
		p[a[i]-'a'+1]=b[i]-'a'+1;
	}
	return 1;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(p,0,sizeof(p));
		cin.getline(a,2000);
		cin.getline(b,2000);
		printf("%d\n",Check());
	}
	return 0;
}