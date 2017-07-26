/*Description:
inner merge sort: aim to sort a random array using merge sort

*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


vector<int> combineSubArr(vector<int> arr1, vector<int> arr2){
	vector<int> combArr;
	int i=0;
	int j=0;
	while(i<arr1.size()&&j<arr2.size()){
		if(arr1[i]<=arr2[j]){
			combArr.push_back(arr1[i]);
			i++;
		}
		else{
			combArr.push_back(arr2[j]);
			j++;
		}
	}
	if(i==arr1.size()){

		combArr.insert(combArr.end(),arr2.begin()+j,arr2.end());
	}
	else
		combArr.insert(combArr.end(),arr1.begin()+i,arr1.end());

	return combArr;
}

vector<int> mergeSort(vector<int> arr, int p, int r){
	int n=(p+r)/2;
	vector<int> subArr1;
	vector<int> subArr2;
	if(p!=r){
		subArr1=mergeSort(arr,p,n);
		subArr2=mergeSort(arr,n+1,r);
	}
	else{
		vector<int> a;
		a.push_back(arr[p]);
		return a;
	}
	return combineSubArr(subArr1,subArr2);
}

int main(){
    vector<int> arr;
    for(int i=0;i<10;i++)
        arr.push_back(i);
    arr.push_back(0);
    random_shuffle(&arr[0],&arr[arr.size()]);//permute arr randomly

    vector<int > res=mergeSort(arr,0,arr.size()-1);
    for( int i=0;i<res.size();i++)
    	cout<<res[i]<<endl;
    
	return 0;
}