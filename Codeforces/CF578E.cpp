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
#include<set>
#define ll long long
#define set_it set<int>::iterator
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+5;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
set<int>L,R;
int n,Ans,lst,SumL,SumR,a[N],b[N];
void Solve(int flag){
	L.clear();R.clear();
	for(int i=1;i<=n;i++){
		if(s[i]=='L')L.insert(i);
		if(s[i]=='R')R.insert(i);
	}
	L.insert(inf);R.insert(inf);
	int sum=0,nxt=(flag?(*R.begin()):(*L.begin()));
	for(int num=1;num<=n;num++){
		int Lfst=(*L.begin()),Lnxt=(*L.lower_bound(nxt));
		int Rfst=(*R.begin()),Rnxt=(*R.lower_bound(nxt));
		if(flag==0){
			if(nxt==inf||(Rnxt==inf&&Lfst<Rfst))nxt=Lfst;
			int pos=nxt;L.erase(pos);nxt=(*R.lower_bound(pos));b[num]=pos;
		}
		if(flag==1){
			if(nxt==inf||(Lnxt==inf&&Rfst<Lfst))nxt=Rfst;
			int pos=nxt;R.erase(pos);nxt=(*L.lower_bound(pos));b[num]=pos;
		}
		sum+=(b[num]<b[num-1]);flag^=1;
	}
	if(sum<Ans){Ans=sum;for(int i=1;i<=n;i++)a[i]=b[i];}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	scanf("%s",s+1);n=strlen(s+1);Ans=inf;
	for(int i=1;i<=n;i++)SumL+=(s[i]=='L');
	for(int i=1;i<=n;i++)SumR+=(s[i]=='R');
	if(SumL>=SumR)Solve(0);
	if(SumR>=SumL)Solve(1);
	printf("%d\n",Ans);
	for(int i=1;i<=n;i++)printf("%d ",a[i]);
	return 0;
}
