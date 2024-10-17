#include <iostream>
#include <cstring>
using namespace std;
int ans;
string pre,back;
 
int main()
{
	cin>>pre>>back;ans=0;
	for (int i=1;i<pre.size();i++)
	 for (int j=0;j<back.size()-1;j++)//注意pre和back的判断起始位置
	 	if (pre[i]==back[j]&&pre[i-1]==back[j+1])ans++;
	cout<<(1<<ans)<<endl;
	return 0;
}
