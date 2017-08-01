/*Descroption
red-black binary tree: a kind of balenced bianry tree*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct node{
	int key;
	int color;//0 for red, 1 for balck
	node *parent;
	node *left;
	node *right;

};
/* rotate left around the node center*/
void leftRotate(node* root, node* center,node* sentinel){
	node* r=center->right;
	center->right=r->left;
	if(r->left!=sentinel)
		r->left->parent=center;
	if(center==root){
		root=r;
		r->parent=sentinel;
	}
	else{
		r->parent=center->parent;
		if(center==center->parent->left)
			center->parent->left=r;
		if(center==center->parent->right)
			center->parent->right=r;
	}
	r->left=center;
	center->parent=r;
}
/* rotate right around the node center*/
void rightRotate(node* root, node* center,node* sentinel){
	node* l=center->left;
	center->left=l->right;
	if(l->right!=sentinel)
		l->right->parent=center;
	if(center==root){
		root=l;
		l->parent=sentinel;
	}
	else{
		l->parent=center->parent;
		if(center==center->parent->left)
			center->parent->left=l;
		if(center==center->parent->right)
			center->parent->right=l;
	}
	l->right=center;
	center->parent=l;
}
/*fixup insert operation to mainten the red-black property, i.e. correct the color in the tree after the node inserted*/
void RBInsertFixup(node* root,node* sentinel, node* pn){
	node* z=pn;
	while(z->parent->color==0){

		if(z->parent==z->parent->parent->left){
			node* uncle=z->parent->parent->right;
			if(uncle->color==0){
				uncle->color=1;
				z->parent->color=1;
				z->parent->parent->color=0;
				z=z->parent->parent;
			}
			else{
				if(z==z->parent->right){
					z=z->parent;
					leftRotate(root,z,sentinel);
				}
				z->parent->color=1;
				z->parent->parent->color=0;
				rightRotate(root,z->parent->parent,sentinel);
			}
		}
		else{
			node* uncle=z->parent->parent->left;
			if(uncle->color==0){
				uncle->color=1;
				z->parent->color=1;
				z->parent->parent->color=0;
				z=z->parent->parent;
			}
			else{
				if(z==z->parent->left){
					z=z->parent;
					rightRotate(root,z,sentinel);
				}
				z->parent->color=1;
				z->parent->parent->color=0;
				leftRotate(root,z->parent->parent,sentinel);
			}
		}
	}
	root->color=1;
}
/*insert a node pn*/
node* RBInsert(node* root, node* sentinel, node *pn){
	node* p=root;
	node* parent=sentinel;
	while(p!=sentinel){
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
	pn->left=sentinel;
	pn->right=sentinel;
	pn->color=0;
	if(root==sentinel)
		root=pn;
	//correct color
	RBInsertFixup(root,sentinel,pn);
	return root;
}
/*build a red-black tree*/
node* RBBuild(vector<node> &arr,node* sentinel){
	node* root;
	root=&arr[0];
	for(int i=1;i<arr.size();i++)
		root=RBInsert(root,sentinel,&arr[i]);
	return root;
}
/*find the minimum node, search from root*/
node* RBMin(node* root, node* sentinel){
	node* p=root;
	while(true){
		if(p->left==sentinel)
			break;
		p=p->left;
	}
	return p;
}
/* return the node that is the smallest one among the nodes that are greater than 'root' */
node* RBSuccessor(node* root,node* sentinel){
	node* x=root;
	if(x->right!=sentinel)
		return RBMin(x->right,sentinel);
	node *y=x->parent;
	while(y!=sentinel&&x==y->right){
		x=y;
		y=y->parent;
	}
	return y;
}
/*fixup delete operation, i.e. correct the color*/
void RBDeleteFixup(node* root, node* sentinel, node* x){
	node* uncle;
	while(x!=root&&x->color==1){
		if(x==x->parent->left){
			uncle=x->parent->right;
			if(uncle->color==0){//turn uncle to be black
				uncle->color=1;
				x->parent->color=0;
				leftRotate(root,x->parent,sentinel);
				uncle=x->parent->right;
			}
			if(uncle->left->color==1&&uncle->right->color==1){
				uncle->color=0;
				x=x->parent;
			}
			else{ 
				if(uncle->right->color==1){
					uncle->left->color=1;
					uncle->color=0;
					rightRotate(root,uncle,sentinel);
					uncle=x->parent->right;
				}
				uncle->color=x->parent->color;
				x->parent->color=1;
				uncle->right->color=1;
				leftRotate(root,x->parent,sentinel);
				x=root;
			}
		}
		else{
			uncle=x->parent->left;
			if(uncle->color==0){//turn uncle to be black
				uncle->color=1;
				x->parent->color=0;
				rightRotate(root,x->parent,sentinel);
				uncle=x->parent->left;
			}
			if(uncle->left->color==1&&uncle->right->color==1){
				uncle->color=0;
				x=x->parent;
			}
			else{ 
				if(uncle->left->color==1){
					uncle->right->color=1;
					uncle->color=0;
					leftRotate(root,uncle,sentinel);
					uncle=x->parent->left;
				}
				uncle->color=x->parent->color;
				x->parent->color=1;
				uncle->left->color=1;
				rightRotate(root,x->parent,sentinel);
				x=root;
			}
		}
	x->color=1;
	}
}
/* delete node del */
node* RBDelete(node* root, node *del, node* sentinel){
	node* y;
	node* x;
	if(del->left==sentinel||del->right==sentinel)
		y=del;
	else
		y=RBSuccessor(del,sentinel);
	if(y->left!=sentinel)
		x=y->left;
	else
		x=y->right;
	x->parent=y->parent;
	if(y->parent==sentinel)
		root=x;
	else{
		if(y==y->parent->right)
			y->parent->right=x;
		else
			y->parent->left=x;
	}
	if(y!=del){
		del->color=y->color;
		del->key=y->key;

	}
	if(y->color==1)
		RBDeleteFixup(root,sentinel,x);
	return root;
}
int main(){
 	vector<node> arr;
 	node sent;
 	sent.key=-1;
 	sent.color=1;
 	sent.left=NULL;
 	sent.right=NULL;
 	sent.parent=NULL;
 	//sentinel is a child of all leaves, and also is the parent of root
 	node* sentinel=&sent;
    for(int i=0;i<10;i++){
        node n;
        n.color=1;
        n.key=i;
        n.left=sentinel;
        n.right=sentinel;
        n.parent=sentinel;
        arr.push_back(n);
    }

    random_shuffle(&arr[0],&arr[arr.size()]);//permute arr randomly
	for( int i=0;i<arr.size();i++)
    	cout<<arr[i].key<<endl;
    cout<<"test"<<endl;
    node *root=RBBuild(arr,sentinel);
    node* del=&arr[2];
    root=RBDelete(root,del,sentinel);
    node *p=root;
    while(p!=sentinel){
     	cout<<p->key<<" "<<p->color<<endl;
         p=p->left;
    }
	return 0;
}