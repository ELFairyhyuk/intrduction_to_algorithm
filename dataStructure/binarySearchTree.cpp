/*Description:
binary search tree:bulid, search, insert, delete, findMinimum*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct node{
	int key;
	node *parent;
	node *left;
	node *right;
};

node* binaryInsert(node *root, node *pn){
	if(root==NULL){
		root=pn;
	}
	else{
	node *p=root;
	node *parent=NULL;
	while(p!=NULL){
		parent=p;
		if(pn->key>p->key){

			p=p->right;
		}
		else{
			p=p->left;
		}
	}
	if(pn->key>parent->key)
		parent->right=pn;
	else
		parent->left=pn;
	pn->parent=parent;
	}
	return root;
}

node* binaryBuildTree(vector<node> &tree){
	if(tree.empty()){
		cout<<"input cna not be empty"<<endl;
		return NULL;
	}
	node *root=&tree[0];
	for(int i=1;i<tree.size();i++){
		binaryInsert(root,&tree[i]);
	}
	return root;
}
/*search if key is in the tree, if not , return NULL; if is ,return the pointer that point to the node has the same key*/
node* binarySearch(node *root,int key){
	node *p=root;
	while(p!=NULL){
		if(key>p->key){
			p=p->right;
		}
		else if(key==p->key)
			return p;
		else{
			p=p->left;
		}
	}
	return NULL;
}

node* binaryDelete(node *root, int key){
	node* del=binarySearch(root,key);
	if(del==NULL){
		cout<<"node which is to be deleted is not in the tree"<<endl;
		return NULL;
	}

	if(del->left==NULL){
		if(root==del){
			root=del->right;
			if(del->right!=NULL)
				del->right->parent=NULL;
		}
		else{
			if(del->parent->right==del)
				del->parent->right=del->right;
			else
				del->parent->left=del->right;
			if(del->right!=NULL)
				del->right->parent=del->parent;			
		}	
	}
	else{//has left
		node *temp=del->left;
		while(temp->right!=NULL)
			temp=temp->right;

		if(del->left==temp){//del->left has no right child
			if(root!=del){
				if(del->parent->right==del)
					del->parent->right=temp;
				if(del->parent->left==del)
					del->parent->left=temp;
				temp->parent=del->parent;
			}
			else{
				root=temp;	
				temp->parent=NULL;
			}
			temp->right=del->right;
			if(del->right!=NULL)
				temp->right->parent=temp;
		}

		else{//del->left has right child
			if(temp->left!=NULL){
				temp->parent->right=temp->left;
				temp->left->parent=temp->parent;
			}
			if(root!=del){
				if(del->parent->right==del)
					del->parent->right=temp;
				else
					del->parent->left=temp;
				temp->parent=del->parent;
			}
			else{
				root=temp;
				temp->parent=NULL;
			}
			temp->left=del->left;
			temp->right=del->right;
			temp->left->parent=temp;
			if(del->right!=NULL)
				del->right->parent=temp;
		}
	
	}

	del->parent=NULL;
	del->left=NULL;
	del->right=NULL;

	return root;
}
/* return the minimum node in the tree*/
node* binaryMin(node* root){
	node* p=root;
	while(true){
		if(p->left==NULL)
			break;
		p=p->left;
	}
	return p;
}
node* binarySuccessor(node* root){
	node* x=root;
	if(x->right!=NULL)
		return binaryMin(x->right);
	node *y=x->parent;
	while(y!=NULL&&x==y->right){
		x=y;
		y=y->parent;
	}
	return y;
}

int main(){
    vector<node> arr;
    for(int i=0;i<10;i++){
        node n;
        n.key=i;
        n.left=NULL;
        n.right=NULL;
        n.parent=NULL;
        arr.push_back(n);
    }
    //arr.push_back(0);
    random_shuffle(&arr[0],&arr[arr.size()]);//permute arr randomly
	for( int i=0;i<arr.size();i++)
    	cout<<arr[i].key<<endl;
    cout<<"test"<<endl;
    node *root=binaryBuildTree(arr);
    node *p=root;
    // while(p!=NULL){
    // 	cout<<p->key<<endl;
    //     p=p->left;
    // }
    node *res=binarySearch(root,12);
    if(res!=NULL)
   		cout<<res->key<<endl;
   	node* newroot=binaryDelete(root,8);
   	p=newroot;
    while(p!=NULL){
    	cout<<p->key<<endl;
        p=p->left;
    }
	return 0;
}
