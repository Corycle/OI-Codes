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
using namespace std;
const int inf=0x3f3f3f3f;
const int N=2000005;
namespace IO{
	int c;
	unsigned int seed;
	unsigned int randnum(){
		seed^=seed<<13;
		seed^=seed>>17;
		seed^=seed<<5;
		return seed;
	}
	inline int read(int &x){scanf("%d",&x);return x;}
	inline void init_case(int &m,int &a,int &b,int &d,int p[]){
		scanf("%d%u%d%d%d%d",&m,&seed,&a,&b,&c,&d);
		for(int i=1;i<=m;i++){
			if(randnum()%c==0)p[i]=-1;
			else p[i]=randnum()%b;
		}
	}
	inline void update_ans(unsigned int &ans_sum,unsigned int cur_ans,int no){
		const static unsigned int mod=998244353;
		ans_sum^=(long long)no*(no+7)%mod*cur_ans%mod;
	}
}
using IO::read;
using IO::init_case;
using IO::update_ans;

int ql,qr,fl,fr,tmp,Ans;
int p[N],q[N],F[N],vis1[N],vis2[N];
inline void Insert(int x){
	vis1[x]=vis2[x]=tmp;
	while(vis1[Ans]==tmp)Ans++;
}
inline void Delete(int x){
	while(fl<=fr&&F[fr]>x)fr--;
	q[++qr]=x;F[++fr]=x;vis2[x]=0;
}
inline void Find(){
	int x=q[ql++];
	while(fl<=fr&&F[fl]==x)fl++;
	Insert(x);
}
int main(){
//	freopen("knowledge.in","qr",stdin);
//	freopen("knowledge.out","w",stdout);
	int T;read(T);
	int m,a,b,d;
	while(T--){
		unsigned int ans_sum=0,cur_ans=0;
		init_case(m,a,b,d,p);
		tmp++;ql=1;qr=0;fl=1;fr=0;Ans=0;
		for(int i=0;i<=a;i++)Insert(i);
		for(int i=1;i<=m;i++){
			if(d==1){
				if(p[i]==-1)continue;
				if(vis1[p[i]]!=tmp)Insert(p[i]);
				else continue;
			}
			else{
				if(p[i]==-1){
					if(ql>qr)continue;
					else Find();
				}
				else if(vis1[p[i]]!=tmp)Insert(p[i]);
				else if(vis2[p[i]]==tmp)Delete(p[i]);
				else{
					if(ql>qr)continue;
					else Find();
				}
			}
			cur_ans=(fl<=fr?min(F[fl],Ans):Ans);
			update_ans(ans_sum,cur_ans,i);
		}
		printf("%u\n",ans_sum);
	}
	return 0;
}