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
const int N=200005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
char s[N];
int n,tot;
int b[N],c[N];
struct Ques{int type,x,y;}q[N];
int lowbit(int x){
	return x&(-x);
}
void Add(int x,int y){
	for(int i=x;i<=tot;i+=lowbit(i)){
		c[i]+=y;
	}
}
int Ask(int x){
	int sum=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		sum+=c[i];
	}
	return sum;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	n=read();
	for(int i=1;i<=n;i++){
		cin.getline(s,100);
		int x=0,y=0,flag=-1;
		for(int j=0;j<=100;j++){
			if(!s[j])break;
			if('0'<=s[j]&&s[j]<='9'){
				if(flag==-1)flag=0;
				if(!flag)x=x*10+s[j]-'0';
				else y=y*10+s[j]-'0';
			}
			else if(flag==0)flag=1;
		}
		if(!y)q[i].type=1;
		else q[i].type=2;
		q[i].x=x;q[i].y=y;
		if(x)b[++tot]=x;
		if(y)b[++tot]=y;
	}
	sort(b+1,b+tot+1);
	tot=unique(b+1,b+tot+1)-b-1;
	for(int i=1;i<=n;i++){
		if(q[i].x)q[i].x=lower_bound(b+1,b+tot+1,q[i].x)-b;
		if(q[i].y)q[i].y=lower_bound(b+1,b+tot+1,q[i].y)-b;
		if(q[i].type==1)Add(q[i].x,1);
		if(q[i].type==2)printf("%d\n",Ask(q[i].y)-Ask(q[i].x-1));
	}
	return 0;
}
/*
6
1
2
3
4
1 3
2 2
*/