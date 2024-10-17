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
const int N=4005;
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int vis[N][N];
char A[N],B[N];
int n,m,lenA,lenB;
struct Suffix_Automaton{
	int tot,lst,root;
	int fa[N],len[N],ch[N][27];
	void Init(){
		tot=1;lst=1;root=1;
	}
	void Insert(int num){
		int x=lst,fx=++tot;len[fx]=len[x]+1;
		while(x&&!ch[x][num]){ch[x][num]=fx;x=fa[x];}
		if(!x)fa[fx]=root;
		else{
			int y=ch[x][num];
			if(len[y]==len[x]+1)fa[fx]=y;
			else{
				int fy=++tot;len[fy]=len[x]+1;
				for(int i=1;i<=26;i++)ch[fy][i]=ch[y][i];
				fa[fy]=fa[y];fa[y]=fa[fx]=fy;
				while(x&&ch[x][num]==y){ch[x][num]=fy;x=fa[x];}
			}
		}
		lst=fx;
	}
}SAM_A,SAM_B;
struct Sequential{
	int tot,root;
	int lst[27],ch[N][27],pre[N];
	void Init(){
		tot=1;root=1;
		for(int i=1;i<=26;i++)lst[i]=1;
	}
	void Insert(int num){
		int x=lst[num],y=++tot;pre[y]=x;
		for(int i=1;i<=26;i++){
			for(int j=lst[i];j&&!ch[j][num];j=pre[j])ch[j][num]=y;
		}
		lst[num]=y;
	}
}SQ_A,SQ_B;
struct Node{int x,y,step;};
int BFS1(){
	queue<Node>q;q.push((Node){1,1,0});vis[1][1]=1;
	while(q.size()){
		int x=q.front().x,y=q.front().y,t=q.front().step;q.pop();
		for(int i=1;i<=26;i++){
			int fx=SAM_A.ch[x][i],fy=SAM_B.ch[y][i];
			if(fx&&fy){
				if(vis[fx][fy]==1)continue;
				q.push((Node){fx,fy,t+1});
				vis[fx][fy]=1;
			}
			if(fx&&!fy)return t+1;
		}
	}
	return -1;
}
int BFS2(){
	queue<Node>q;q.push((Node){1,1,0});vis[1][1]=2;
	while(q.size()){
		int x=q.front().x,y=q.front().y,t=q.front().step;q.pop();
		for(int i=1;i<=26;i++){
			int fx=SAM_A.ch[x][i],fy=SQ_B.ch[y][i];
			if(fx&&fy){
				if(vis[fx][fy]==2)continue;
				q.push((Node){fx,fy,t+1});
				vis[fx][fy]=2;
			}
			if(fx&&!fy)return t+1;
		}
	}
	return -1;
}
int BFS3(){
	queue<Node>q;q.push((Node){1,1,0});vis[1][1]=3;
	while(q.size()){
		int x=q.front().x,y=q.front().y,t=q.front().step;q.pop();
		for(int i=1;i<=26;i++){
			int fx=SQ_A.ch[x][i],fy=SAM_B.ch[y][i];
			if(fx&&fy){
				if(vis[fx][fy]==3)continue;
				q.push((Node){fx,fy,t+1});
				vis[fx][fy]=3;
			}
			if(fx&&!fy)return t+1;
		}
	}
	return -1;
}
int BFS4(){
	queue<Node>q;q.push((Node){1,1,0});vis[1][1]=4;
	while(q.size()){
		int x=q.front().x,y=q.front().y,t=q.front().step;q.pop();
		for(int i=1;i<=26;i++){
			int fx=SQ_A.ch[x][i],fy=SQ_B.ch[y][i];
			if(fx&&fy){
				if(vis[fx][fy]==4)continue;
				q.push((Node){fx,fy,t+1});
				vis[fx][fy]=4;
			}
			if(fx&&!fy)return t+1;
		}
	}
	return -1;
}
int main(){
//	freopen("string.in","r",stdin);
//	freopen("string.out","w",stdout);
	scanf("%s",A+1);lenA=strlen(A+1);
	scanf("%s",B+1);lenB=strlen(B+1);
	SAM_A.Init();SQ_A.Init();
	SAM_B.Init();SQ_B.Init();
	for(int i=1;i<=lenA;i++){
		SQ_A.Insert(A[i]-'a'+1);
		SAM_A.Insert(A[i]-'a'+1);
	}
	for(int i=1;i<=lenB;i++){
		SQ_B.Insert(B[i]-'a'+1);
		SAM_B.Insert(B[i]-'a'+1);
	}
	printf("%d\n",BFS1());
	printf("%d\n",BFS2());
	printf("%d\n",BFS3());
	printf("%d\n",BFS4());
	return 0;
}