/*
Description: DP is a method to solve optimal problem,the problem should has two key property:
(1) optimal structure: all the optimal solutions of subproblems can be combined to be the optimal solution of the original problem
(2) overlapping subproblems: some subprobems may reappeared
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
/*matrix-chain multiplicion,*/
/*split rod,get most profit*/
int cutRodMemoUpBottom(int n,vector< int> price,vector<int> &r){
	if(r[n]>=0)
		return r[n];
	int max=-1;
	int q;
	if(n==0)
		return 0;
	else{
		for(int i=0;i<=n;i++){
		max=max>(q=price[i]+cutRodMemoUpBottom(n-i,price,r))?max:q;
		}
	}
	r[n]=max;
	return r[n];
}
/*use up to bottom method, n is lengh of rod, use recurse*/
int cutRodMemo(int n,vector<int> price){
	vector<int> r;
	for(int i=0;i<n;i++)
		r.push_back(-1);
	
	return cutRodMemoUpBottom(n,price,r);//return r[n]
}
/*from botoom to up, no recurse. first get max profit when n=1, then when n=2.... */
int cutRodBottomUp(int n,vector<int> price){
	int max=-1;
	vector<int> r(n,0);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			max=max>(price[j]+r[i-j])?max:(price[j]+r[i-j]);
		}
		r[i]=max;
	}
	return r[n];
}
int main(){
	vector<int> price;
	price.push_back(0);
	price.push_back(1);
	price.push_back(5);
	price.push_back(8);
	price.push_back(9);
	price.push_back(10);
	price.push_back(17);
	price.push_back(17);
	price.push_back(20);
	price.push_back(24);
	price.push_back(30);
	cout<<cutRodBottomUp(6,price)<<endl;
	return 0;
}