/*====Corycle====*/
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<cstring>
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
const int DLT=1721424;
const int Dlt3=577460;//1582
const int Dlt1=365250;//1000
const int Dlt2=14610;//40
const ll Dlt4=14609700000ll;//40000000
const ll Dlt5=1460970000ll;//4000000
const ll Dlt6=146097000ll;//400000
const ll Dlt7=14609700ll;//40000
const ll Dlt8=1460970ll;//4000
const ll Dlt9=146097ll;//400
ll read(){
	ll s=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){s=s*10+c-'0';c=getchar();}
	return s*f;
}
int sum[15];
int a[15]={0,31,28,31,30,31,30,31,31,30,31,30,31};
bool Check(int x){return (x%4==0&&(x%100!=0||(x%400==0)));}
int main(){
//	freopen("julian.in","r",stdin);
//	freopen("julian.out","w",stdout);
	for(int i=1;i<=12;i++)sum[i]=sum[i-1]+a[i];
	int Case=read();
	while(Case--){
		ll n=read()+1;
		if(n<=DLT){
			ll Y=4714,M=12,D=31;
			while(n>Dlt1){n-=Dlt1;Y-=1000;}
			while(n>Dlt2){n-=Dlt2;Y-=40;}
			while(n){
				Y--;
				int tmp=365+(Y%4==1);
				if(n>=tmp)n-=tmp;
				else{
					if(tmp==366)for(int i=2;i<=12;i++)sum[i]++;
					for(int i=12;i>=1;i--)if(n>sum[i-1]){M=i;D=n-sum[i-1];n=0;break;}
					if(tmp==366)for(int i=2;i<=12;i++)sum[i]--;
				}
			}
			printf("%lld %lld %lld BC\n",D,M,Y);
		}
		else{
			n-=DLT;
			if(!n){puts("1 1 1");continue;}
			ll Y=0,M=12,D=31;
			if(n>Dlt3){
				Y=1582;n-=Dlt3;
				if(n>355)n-=355;
				else{
					for(int i=10;i<=12;i++)sum[i]-=10;
					for(int i=12;i>=1;i--)if(n>sum[i-1]){
						M=i;
						if(i!=10)D=n-sum[i-1];
						else{
							n-=sum[i-1];
							D=(n<=4?n:n+10);
						}
						n=0;break;
					}
					for(int i=10;i<=12;i++)sum[i]+=10;
				}
				while(n>Dlt4){n-=Dlt4;Y+=40000000;}
				while(n>Dlt5){n-=Dlt5;Y+=4000000;}
				while(n>Dlt6){n-=Dlt6;Y+=400000;}
				while(n>Dlt7){n-=Dlt7;Y+=40000;}
				while(n>Dlt8){n-=Dlt8;Y+=4000;}
				while(n>Dlt9){n-=Dlt9;Y+=400;}
				while(n){
					Y++;
					int tmp=365+Check(Y);
					if(n>=tmp)n-=tmp;
					else{
						if(tmp==366)for(int i=2;i<=12;i++)sum[i]++;
						for(int i=12;i>=1;i--)if(n>sum[i-1]){M=i;D=n-sum[i-1];n=0;break;}
						if(tmp==366)for(int i=2;i<=12;i++)sum[i]--;
					}
				}
			}
			else{
				while(n>Dlt1){n-=Dlt1;Y+=1000;}
				while(n>Dlt2){n-=Dlt2;Y+=40;}
				while(n){
					Y++;
					int tmp=365+(Y%4==0);
					if(n>=tmp)n-=tmp;
					else{
						if(tmp==366)for(int i=2;i<=12;i++)sum[i]++;
						for(int i=12;i>=1;i--)if(n>sum[i-1]){M=i;D=n-sum[i-1];n=0;break;}
						if(tmp==366)for(int i=2;i<=12;i++)sum[i]--;
					}
				}
			}
			printf("%lld %lld %lld\n",D,M,Y);
		}
	}
	return 0;
}