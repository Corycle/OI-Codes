#include<cstdio>
int a,b,c=1;
int main()
{
	for(;~scanf("%d%d",&a,&b);printf("%d\n",c),c=1)
		for(a%=10;b;b>>=1,a=a*a%10)
			if(b&1)c=c*a%10;
}