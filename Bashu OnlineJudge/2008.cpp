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
const int N=30005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,cnt;
char s[N];
string l[N],r[N];
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++)cin>>s[i];
	for(int i=n;i>=1;i--)l[i]=s[i]+l[i+1];
	for(int i=1;i<=n;i++)r[i]=s[i]+r[i-1];
	int x=1,y=n;
	while(x<=y){
		if(l[x]<r[y])cout<<s[x++];
		else cout<<s[y--];
		cnt++;
		if(cnt%80==0){
			cnt=0;
			cout<<endl;
		}
	}
	return 0;
}