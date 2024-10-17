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
struct cl{
	int p[10];
	int step[40],num;
};
int n=3,m=3,a[10],f[4][4][4][4][4][4][4][4][4];
//				   A B C D E F G H I
int ch[10][10]={{0,0,0,0,0,0,0,0,0,0},//0
				{0,1,1,0,1,1,0,0,0,0},//1
				{0,1,1,1,0,0,0,0,0,0},//2
				{0,0,1,1,0,1,1,0,0,0},//3
				{0,1,0,0,1,0,0,1,0,0},//4
				{0,0,1,0,1,1,1,0,1,0},//5
				{0,0,0,1,0,0,1,0,0,1},//6
				{0,0,0,0,1,1,0,1,1,0},//7
				{0,0,0,0,0,0,0,1,1,1},//8
				{0,0,0,0,0,1,1,0,1,1}};//9
queue<cl>q;
bool pd(cl x){
	int i,j,k;
	for(i=1;i<=9;i++){
		if(x.p[i]!=0)return false;
	}
	return true;
}
int main(){
//  freopen("_.in","r",stdin);
//  freopen("_.out","w",stdout);
	int i,j,k;
	for(i=1;i<=9;i++){
		a[i]=read();
	}
	cl dzh;
	memcpy(dzh.p,a,sizeof(a));
	q.push(dzh);
	memset(f,0x3f,sizeof(f));
	f[a[1]][a[2]][a[3]][a[4]][a[5]][a[6]][a[7]][a[8]][a[9]]=0;
	while(q.size()){
		cl now=q.front();
		if(now.num>=30)continue;
		if(pd(now)){
			for(i=1;i<=now.num;i++)printf("%d ",now.step[i]);
			return 0;
		}
		int st=f[now.p[1]][now.p[2]][now.p[3]][now.p[4]][now.p[5]][now.p[6]][now.p[7]][now.p[8]][now.p[9]];
		q.pop();
		for(i=1;i<=9;i++){
			cl to=now;
			for(j=1;j<=9;j++){
				if(ch[i][j]==1){
					to.p[j]=(to.p[j]+1)%4;
				}
			}
			int st_to=f[to.p[1]][to.p[2]][to.p[3]][to.p[4]][to.p[5]][to.p[6]][to.p[7]][to.p[8]][to.p[9]];
			if(st_to>st+1){
				f[to.p[1]][to.p[2]][to.p[3]][to.p[4]][to.p[5]][to.p[6]][to.p[7]][to.p[8]][to.p[9]]=st+1;
				to.step[++to.num]=i;
				q.push(to);
			}
		}
	}
	return 0;
}