#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>
#include<stack>
#include<queue>
#include<map>
#define ll long long
using namespace std;
const int inf=0x3f3f3f3f;
const int N=205;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int n,m;
char s[N],a1[N],a2[N];
int p1[N],p2[N],num[N];
int m1[N][N],m2[N][N],q[N][N];
map<char,int>id1,id2;
/*
	a1[i]表示第i个男人的名字 
	a2[i]表示第i个女人的名字 
	p1[i]表示第i个男人的配偶 
	p2[i]表示第i个女人的配偶 
	m1[i][j]表示第i个男人心中排名第j个的女人 
	m2[i][j]表示第i个女人心中第i个男人的排名 
	num[i]表示第i个男人表白了num[i]个女人 
	q[i][j]表示第i个女人的第j个追求者 
*/
void Solve(){
	for(int i=1;i<=n;i++){
		p1[i]=p2[i]=num[i]=0;
	}
	int Num=0;
	while(Num<n){
		for(int i=1;i<=n;i++)q[i][0]=0;
		for(int i=1;i<=n;i++){
			if(!p1[i]){
				int x=m1[i][++num[i]];
				q[x][++q[x][0]]=i;
			}
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=q[i][0];j++){
				if(!p2[i]){
					p1[q[i][j]]=i;
					p2[i]=q[i][j];
					Num++;
				}
				else if(m2[i][q[i][j]]<m2[i][p2[i]]){
					p1[p2[i]]=0;
					p1[q[i][j]]=i;
					p2[i]=q[i][j];
				}
			}
		}
	}
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	int T=read();
	while(T--){
		n=read();
		for(int i=1;i<=n;i++){scanf("%s",s);id1[a1[i]=s[0]]=i;}
		for(int i=1;i<=n;i++){scanf("%s",s);id2[a2[i]=s[0]]=i;}
		for(int i=1;i<=n;i++){
			scanf("%s",s);
			for(int j=1;j<=n;j++){
				m1[id1[s[0]]][j]=id2[s[j+1]];
			}
		}
		for(int i=1;i<=n;i++){
			scanf("%s",s);
			for(int j=1;j<=n;j++){
				m2[id2[s[0]]][id1[s[j+1]]]=j;
			}
		}
		Solve();
		for(int i=1;i<=n;i++){
			printf("%c %c\n",a1[i],a2[p1[i]]);
		}
		printf("\n");
	}
	return 0;
}