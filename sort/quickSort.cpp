/*

description:
this algorithm aims to sort an random array using quickSort,.
There are three versions of quick sort in this file
worst case :O(n^2)
best and average case: O(nlgn)
*/

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <class T> void exchange(T &x, T &y){
    T temp=x;
    x=y;
    y=temp;
}

/* Version 1: Hoare quicksort, iterate the array from head and rear*/
void hoareQuickSort(vector< int> &arr, int p, int r){
	if (p<r){
		int i=p;
		int j=r;
		while(i<j){
			while(i<j&&arr[i]<=arr[r]){
				i++;
			}
			while(j>i&&arr[j]>arr[r]){
				j--;
			}
			exchange(arr[i],arr[j]);
		}
		exchange(arr[r],arr[i]);
		hoareQuickSort(arr,p,i-1);
		hoareQuickSort(arr,i+1,r);
	}
}

/*Version 2: iterate the array from head*/
void quickSort(vector< int> &arr, int p, int r){
	int i=p-1;
	int j=p;
	if(p<r){
		while(j<r){
			if(arr[j]<=arr[r]){
				i++;
				exchange(arr[i],arr[j]);
			}
			j++;
			// while(i<(r-1)&&arr[j]<=arr[r]){
			// 	i++;
			//exchange(arr[i+1],arr[j]);
			//     j++;}
			// while(true){
			// 	
			//	j++;
			//	if(arr[j]<=arr[r]){
			//		exchange(arr[i],arr[j]);
			//		break;
			//	}
			// }
			// 	
		}
		exchange(arr[r],arr[i+1]);
		quickSort(arr,p,i);
		quickSort(arr,i+2,r);
	}
}
/* Version 3: quicksort using tail recursion, i.e. sort with only one recursively call to quickSort*/
void quickSortTailRecursion(vector< int> &arr, int p, int r){
	
	while(p<r){
		int i=p-1;
		int j=p;
		while(j<r){
			if(arr[j]<=arr[r]){
				i++;
				exchange(arr[i],arr[j]);
			}
			j++;
		}
		exchange(arr[r],arr[i+1]);
		quickSort(arr,p,i);
		p=i+2;//use p=i+2 to sort the right part
	}
}

int main(){
    vector<int> arr;
    for(int i=0;i<10;i++)
        arr.push_back(i);
    arr.push_back(0);
    random_shuffle(&arr[0],&arr[arr.size()]);//permute arr randomly

    quickSortTailRecursion(arr,0,arr.size()-1);
    for( int i=0;i<arr.size();i++)
    	cout<<arr[i]<<endl;

	return 0;
}