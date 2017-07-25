/*
Description
sort an random array which only has small range of integer elements using count sort
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
/* get the total number of the elements which are smaller than or equal to arr[i]*/
void getArrCount(const vector <int > &arr,vector <int > &count,vector <int > &res){
	for (int i=0;i<arr.size();i++)
		count[arr[i]]++;//get the nunber of each distinct element in array

	for (int i=1;i<count.size();i++)
		count[i]+=count[i-1];//get the total number of the elements which are smaller than or equal to i

}

/* sort using count sort*/
vector<int> countSort(const vector <int > &arr, int maxRange){
	vector <int> count(maxRange,0);
	vector <int > res(arr.size(),0);

	getArrCount(arr,count,res);
	//put arr[i] in result vector in order
	for (int i=0;i<arr.size();i++){
		res[count[arr[i]]]=arr[i];
		count[arr[i]]--;
	}

	return res;
	
}

int main(){
    vector<int> arr;
    for(int i=0;i<10;i++)
        arr.push_back(i);
    arr.push_back(5);
    random_shuffle(&arr[0],&arr[arr.size()]);//permute arr randomly

    vector<int > res=countSort(arr,11);
    for( int i=0;i<res.size();i++)
    	cout<<res[i]<<endl;
    
	return 0;
}