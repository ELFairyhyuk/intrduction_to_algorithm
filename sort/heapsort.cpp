/*

date:2017-07-23 
author:Yawen Chen
Description:
this algorithm aims to sort an random array using max heap sort.
max-heap data structure:in the binary tree, every parent should > its children, 
if the node is from 1 to n, and parent=i, then left child=2i,right child=2i+1
heapsort comlexity=O(nlgn)

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <class T> void exchange(T &x, T &y){
    T temp=x;
    x=y;
    y=temp;
}
/*to get a max-heap of a single node i (i.e. arr[i-1]) */
void maxHeap(vector<int> &arr,int i, int length){
	int max=i;
	if((2*i-1)<length&&arr[2*i-1]>arr[max-1])//node 2*i (i.e. arr[2*i-1]) is the left child of node i
		max=2*i;
	if((2*i)<length&&arr[2*i]>arr[max-1])//node 2*i+1 is the right child of node i
		max=2*i+1;
    if(max!=i){
        exchange(arr[i-1],arr[max-1]);
    	maxHeap(arr,max,length);
    }

}

/* to get the sorted array by output the top of the binary tree*/
void sortArr(vector<int> &arr, int length){
    for(int i=length-1;i>0;i--){
        exchange(arr[0],arr[i]);//swap the last node and the first node, after swap, the last node is the max node
        maxHeap(arr,1,i);//get max-heap for node 1(i.e arr[0]) in the tree without the last node

    }

}

/* use heapsort to get a sorted increasing array */
vector<int> heapsort(vector<int> arr){
	int l=arr.size();
	int n=l/2;//node n has the last leaf in the bianry tree
	for (int i=n;i>0;i--){ //iterate from bottom to top
		maxHeap(arr,i,l); //get max-heap for node i in the binary tree(i.e arr[i-1] in the vector)
	}
    sortArr(arr,l);
	
    return arr;
}




int main(){
    vector<int> arr;
    for(int i=0;i<10;i++)
        arr.push_back(i);
    random_shuffle(&arr[0],&arr[arr.size()]);//repermutate arr randomly

    vector<int> res=heapsort(arr);
    for( int i=0;i<res.size();i++)
    	cout<<res[i]<<endl;

	return 0;
}