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
void printOptimalSolution(vector<int> solution, int n){
	while(n>0){
		cout<<solution[n]<<endl;
		n=n-solution[n];
	}
}

int cutRodMemoUpBottom(int n,vector< int> price,vector<int> &opProfit, vector<int> &solution){
	if(opProfit[n]>=0)
		return opProfit[n];
	int max=-1;
	int q;
	if(n==0)
		return 0;
	int i;
	for(i=1;i<=n;i++){
		q=price[i]+cutRodMemoUpBottom(n-i,price,opProfit,solution);
		if(max<q){
			max=q;
			solution[n]=i;
		}
	}
	
	opProfit[n]=max;
	
	return opProfit[n];
}
/*method 1: use up to bottom method, n is lengh of rod, use recurse*/
int cutRodMemo(int n,vector<int> price){
	vector<int> opProfit;//opProfit[i] stroe the optimal profit when n=i
	vector<int> solution;//solution[i] stroe the optimal solution when n=i
	for(int i=0;i<=n;i++){//opProfit.size()=n+1
		opProfit.push_back(-1);
		solution.push_back(-1);
	}
	
	opProfit[n]=cutRodMemoUpBottom(n,price,opProfit,solution);//return opProfit[n]
	printOptimalSolution(solution,n);
	return opProfit[n];
}
/*mwthod 2: from botoom to up, no recurse. first get max profit when n=1, then when n=2.... */
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
	cout<<cutRodMemo(6,price)<<endl;
	return 0;
}