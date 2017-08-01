
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
template <class T> void exchange(T &x, T &y){
    T temp=x;
    x=y;
    y=temp;
}

int partition(vector< int> &arr, int p, int r){
	int i=p-1;
	int j=p;
	if(p<r){
		while(j<r){
			if(arr[j]<=arr[r]){
				i++;
				exchange(arr[i],arr[j]);
			}
			j++;
		}
		exchange(arr[r],arr[i+1]);
	}
	return i+1;
}

int randomSelect(vector<int> arr, int i,int p, int r){
	int q= partition(arr,p,r);
	//cout<<arr[q]<<endl;
	int k=q-p+1;
	if(i==k){
		cout<<arr[q]<<endl;
		return res;
	}
	else if(i<k)
		randomSelect(arr,i,p,q-1);
	else
		randomSelect(arr,i-k,q+1,r);
}

int main(){
 vector<int> arr;
    for(int i=0;i<10;i++)
        arr.push_back(i);
    arr.push_back(0);
    random_shuffle(&arr[0],&arr[arr.size()]);//permute arr randomly
    randomSelect(arr,5,0,arr.size()-1);

 
	return 0;
}