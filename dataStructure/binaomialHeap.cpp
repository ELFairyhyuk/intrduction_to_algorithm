#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
using namespace std;

struct node{
	int key;
	int degree;
	node* left;//leftmost child
	node* sibling;// brother of node immediately to its right
	node* parent;
};

node* mergeBinomialHeap(node* head1, node* head2){
	node* h1=head1;
	node* h2=head2;
	node* end1;//end of head1 list f heap1
	if(h2==NULL)
		return h1;
	if(h1==NULL)
		return h2;

	while(h1!=NULL){
		end1=h1;
		h1=h1->sibling;
	}
	end1->sibling=h2;
	h1=head1;
	node* temp=h1;
	while(h2!=NULL){
		while(h2->degree>h1->degree&&h1!=h2){
			temp=h1;
			h1=h1->sibling;
		}
		if(h1!=h2){
			end1->sibling=h2->sibling;
			if(h1==head1){
				h2->sibling=h1;
				h1=h2;
				head1=h2;
			}
			else{
				
				h2->sibling=h1;
				temp->sibling=h2;
				h1=h2;
				
			}
			h2=end1->sibling;
		}
		else
			return head1;
	}
	return head1;
}
node* unionBinomialHeap(node* head1, node*head2){
	node* h1=mergeBinomialHeap(head1,head2);

	node* p=h1;
	node* prev=h1;
	while(p!=NULL){
		while(p->sibling!=NULL&&p->degree<p->sibling->degree){
				prev=p;
				p=p->sibling;
		}
		if(p->sibling!=NULL){
			if(p->sibling->sibling!=NULL&&p->sibling->degree==p->sibling->sibling->degree){
				prev=p;
				p=p->sibling;
			}

			if(p->key<p->sibling->key){
				node *temp=p->sibling;
				p->sibling=p->sibling->sibling;
				temp->sibling=p->left;
				p->left=temp;
				temp->parent=p;
				p->degree+=1;
			}
			else{
				if(p==h1){
					h1=p->sibling;
					p->sibling=h1->left;
					h1->left=p;
					p->parent=h1;
					h1->degree+=1;
					p=h1;
				}
				else{
					prev->sibling=p->sibling;
					p->sibling=prev->sibling->left;
					prev->sibling->left=p;
					p->parent=prev->sibling;
					prev->sibling->degree+=1;
					p=prev->sibling;
				}

			}
		}
		else
			p=p->sibling;
	}

	return h1;
}
node* insertBinomialHeap(node* head, node* n){
	node* h=n;
	node* res=unionBinomialHeap(head,h);
	
	return res;
}


node* buildBinomialHeap(vector<node> &arr){
	node* head=NULL;
	for(int i=0;i<arr.size();i++){
		head=insertBinomialHeap(head,&arr[i]);
	}
	node* p=head;
	    while(p!=NULL){
     	cout<<"e"<<p->key<<endl;
     	//cout<<p->sibling->key<<endl;
         p=p->sibling;
    }
	return head;
}

//decrease dec->key to k in the heap
void binomialHeapDecreasingKey(node* head, node* dec, int k){
	node* parent=dec->parent;
	node* p=dec;
	dec->key=k;
	while(parent!=NULL&&p->key<parent->key){
		int key=parent->key;
		parent->key=p->key;
		p->key=key;
		p=parent;
		parent=p->parent;
	}
}

node* deleteMin(node* head){
	node* p;
	node* h=NULL;
	node* prev;
	node* minprev;
	node* minp;
	int min=head->key;

	if(head->sibling!=NULL){
		p=head->sibling;
		while(p!=NULL){
			//find min node
			if(p->key<min){
				min=p->key;
				minprev=prev;
				minp=p;
			}
			prev=p;
			p=p->sibling;
		}
		//delete min node
		if(minp==h){
			head=h->sibling;
			h=h->left;
		}
		else{
			minprev->sibling=minp->sibling;
			h=minp->left;
		}
		
	}
	//head list only has one root
	else{
		h=head->left;
		head=NULL;
	}
	node* temp=h;
	while(temp!=NULL){
		temp->parent=NULL;
		temp=temp->sibling;
	}
	//refix the heap
	head=unionBinomialHeap(head,h);
	return head;
}

node* binomialHeapDelete(node* head, node* del){
	//del->key=log(0);
	binomialHeapDecreasingKey(head,del,log(0));//log_e (0) is a negetive infinite number
	return deleteMin(head);
}
int main(){
	 vector<node> arr;
    for(int i=0;i<10;i++){
        node n;
        n.key=i;
        n.degree=0;
        n.left=NULL;
        n.sibling=NULL;
        n.parent=NULL;
        arr.push_back(n);
    }
    node* head=buildBinomialHeap(arr);
    node* p=head;
   
    head=deleteMin(head);
     while(p!=NULL){
     	cout<<p->key<<endl;
     	//cout<<p->sibling->key<<endl;
         p=p->sibling;
    }
 //    random_shuffle(&arr[0],&arr[arr.size()]);//permute arr randomly
	// for( int i=0;i<arr.size();i++)
 //    	cout<<arr[i].key<<endl;
 //    cout<<"test"<<endl;
   // node *root=binaryBuildTree(arr);
    //node *p=root;
    // while(p!=NULL){
    // 	cout<<p->key<<endl;
    //     p=p->left;
    // }
    // node *res=binarySearch(root,12);
    // if(res!=NULL)
   	// 	cout<<res->key<<endl;
   	// node* newroot=binaryDelete(root,8);
   	// p=newroot;
    // while(p!=NULL){
    // 	cout<<p->key<<endl;
    //     p=p->left;
    // }
	return 0;
}