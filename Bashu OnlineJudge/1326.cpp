#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<complex>
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
int read(){
	int s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int a[20][5],num[20],sum[20];
int GetNum(char s){
	if(s=='A')return 1;
	if(s=='2')return 2;
	if(s=='3')return 3;
	if(s=='4')return 4;
	if(s=='5')return 5;
	if(s=='6')return 6;
	if(s=='7')return 7;
	if(s=='8')return 8;
	if(s=='9')return 9;
	if(s=='0')return 10;
	if(s=='J')return 11;
	if(s=='Q')return 12;
	if(s=='K')return 13;
}
int main(){
//	freopen("_.in","r",stdin);
//	freopen("_.out","w",stdout);
	for(int i=1;i<=13;i++){
		num[i]=4;
		for(int j=1;j<=4;j++){
			char s[5];scanf("%s",s);
			a[i][j]=GetNum(s[0]);
		}
	}
	for(int i=1;i<=4;i++){
		int t=a[13][i];
		while(t!=13){
			sum[t]++;
			t=a[t][num[t]--];
		}
	}
	int ans=0;
	for(int i=1;i<=12;i++)if(sum[i]==4)ans++;
	printf("%d",ans);
	return 0;
}