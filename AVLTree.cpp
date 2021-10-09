#include<iostream>
using namespace std;

template <typename T>
class TreeNode{
	T data;
	TreeNode<T> * left;
	TreeNode<T> * right;
	int height;
	
	public:
	TreeNode(T data){
		this->data=data;
		this->left=this->right=NULL;
		this->height=0;
	}
	
	int Height(TreeNode<T>* root){
		if(root==NULL) {
			return 0;
		}
		return 1+max(Height(root->left),Height(root->right));
	}
	TreeNode<T>* newNodeInsert(T data){
		TreeNode<T>* newNode=new TreeNode<T>(data);
		newNode->data=data;
		newNode->left=newNode->right=NULL;
		newNode->height=1;
		
		return newNode; 
	}
	TreeNode<T>* rightRotate(TreeNode<T>* node){
		TreeNode<T>* temp1=node->left;
		TreeNode<T>* temp2=temp1->right;
		
		temp1->right=node;
		node->left=temp2;
		
		node->height=max(Height(node->left),Height(node->right))+1;
		temp1->height=max(Height(temp1->left),Height(temp1->right))+1;
		
		return temp1;
	}
	
	TreeNode<T>* leftRotate(TreeNode<T> * node){
               TreeNode<T>* temp1=node->right;
		TreeNode<T>* temp2=temp1->left;
		
		temp1->left=node;
		node->right=temp2;
		
		node->height=max(Height(node->left),Height(node->right))+1;
		temp1->height=max(Height(temp1->left),Height(temp1->right))+1;
		
		return temp1;		
	}
	
	int balanceFactor(TreeNode<T> * node){
		if(node==NULL){
			return 0;
		}
		return Height(node->left) - Height(node->right);
	}
	

	TreeNode<T>* insert(TreeNode<T>* root,T data){
		if(root==NULL){
			return (newNodeInsert(data));
		}
		
		if(root->data > data){
			root->left=insert(root->left,data);
		}
		else{
			root->right=insert(root->right,data);
		}
		
		root->height=1+max(Height(root->left),Height(root->right));
		
		int balance=balanceFactor(root);
		
		if(balance>1 && data<root->left->data){
			return rightRotate(root);
		}
		
		if(balance>-1 && data>root->left->data){
			return leftRotate(root);
		}
		
		if(balance>1 && data>root->left->data){
			root->left=leftRotate(root->left);
			return rightRotate(root);
		}
		if(balance<-1 && data<root->right->data){
			root->right=rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
		
	}
	void insert(T data){
		this->insert(this,data);
	}
	
	bool search(TreeNode<T>* root,T data){
		if(root==NULL) return false;
		if(data==root->data){
			return true;
		}
		else if(data<root->data){
			return search(root->left,data);
		}
		else{
			return search(root->right,data);
		}
		return false;
	}
	bool search(T data){
		return search(this,data);
	}
	TreeNode<T> * minimum(TreeNode<T> * root){
		TreeNode<T>* temp=root;
		while(temp->left!=NULL){
			temp=temp->left;
		}
		return temp;
	}
	TreeNode<T> * maximum(TreeNode<T>* root){
		TreeNode<T> * temp=root;
		while(temp->right!=NULL){
			temp=temp->right;
		}
		return temp;
	}

	TreeNode<T>* deleteNode(TreeNode<T>* root, int data)
	{
     

	    if (root == NULL)
	           return root;
            if ( data < root->data )
                   root->left = deleteNode(root->left, data);
 

    	    else if( data > root->data )
                  root->right = deleteNode(root->right, data);

           else
           {

                 if( (root->left == NULL) || (root->right == NULL) )
                 {
                         TreeNode<T> *temp = root->left ?
                         root->left :
                         root->right;
 
                 if (temp == NULL)
                 {
                         temp = root;
                         root = NULL;
                 }
                 else 
                     *root = *temp; 
                 free(temp);
            }
            else
                {

            		TreeNode<T>* temp = minimum(root->right);
 
		        root->data = temp->data;
	 
	               root->right = deleteNode(root->right,
                                     temp->data);
        	}
 	    }

    	   if (root == NULL)
    		return root;
 

    	   root->height = 1 + max(Height(root->left),
                	           Height(root->right));

    	   int balance = balanceFactor(root);


    		if (balance > 1 && balanceFactor(root->left) >= 0)
        		return rightRotate(root);

    		if (balance > 1 && balanceFactor(root->left) < 0){
        		root->left = leftRotate(root->left);
        		return rightRotate(root);
    		}

    		if (balance < -1 && balanceFactor(root->right) <= 0)
        		return leftRotate(root);
 
    		if (balance < -1 &&  balanceFactor(root->right) > 0)
    		{
        		root->right = rightRotate(root->right);
        		return leftRotate(root);
    		}
 
    		return root;
}
	TreeNode<T>* deleteNode(T data){
		//Not working yet
		return deleteNode(this,data);
	}
	void inOrder(TreeNode<T>* root){
		if(root==NULL) return;
		this->inOrder(root->left);
		cout<<root->data<<" ";
		this->inOrder(root->right);
	}
	void inOrder(){
		this->inOrder(this);
	}
	T abs(T a,T b){
		if(a>b) return a-b;
		return b-a;
	}
	T closestValue(TreeNode<T> * root,T data){
		T ans=1000000000;
		if(root==NULL){
			return 0;	
		}
		if(root->data==data){

			TreeNode<T> * temp1=new TreeNode<T>(-1);
			TreeNode<T>* temp2=new TreeNode<T>(1000000000);
			if(root->left!=NULL){
				temp1= maximum(root->left);
			}
			else if(temp2->right!=NULL){
				temp2= minimum(root->right);
			}
			if(temp1->data==-1 || temp2->data==-1) return ans;
			if(temp1->data<temp2->data){
				return temp1->data;
			}
			return temp2->data;
		}
		else if(root->data<data){
			if(abs(root->data,data)-data<ans){
				ans=root->data;
			}
			return closestValue(root->right,data);
		}
		else{
			if(abs(root->data,data)-data<ans){
				ans=root->data;
			}
			return closestValue(root->left,data);
		}
		return ans;
	}
	T closestValue(T data){
		// Edge cases needs to be included ( Leaf nodes)
		return closestValue(this,data);
	}
	void countFrequency(TreeNode<T>* root,T data,int& count){
		if(root==NULL){
			return;
		}
		if(root->data==data){
			count++;
		}
		if(root->data<data){
			countFrequency(root->right,data,count);
		}
		else{
			countFrequency(root->left,data,count);
		}
		
	}
	int countFrequency(T data){
		int count=0;
		countFrequency(this,data,count);
		return count;
	}
	void KthLargestElement(TreeNode<T>* root,int k,int &count){
		if(root==NULL || count>=k){
			return ;
		}
		KthLargestElement(root->right,k,count);
		count++;
		
		if(k==count){
			cout<<root->data<<endl;
			return;
		}		
		KthLargestElement(root->left,k,count);
	}
	void KthLargestElement(int k){
		int count=0;
		return KthLargestElement(this,k,count);	
	}
	
	TreeNode<T> *lower_helper(TreeNode<T>* temp,T data){
		if(temp==NULL) return NULL;
		if(temp->left!=NULL && temp->left->data==data){return temp;}
		if(temp->right!=NULL && temp->right->data==data){ return temp;}
		else if(temp->data<data){
			return this->lower_helper(temp->right,data);
		}
		else{
			return this->lower_helper(temp->left,data);
		}
		return NULL;
	}
	T lower_bound(T data){
		if(this->search(data)) return data;
		this->insert(data);
		TreeNode<T>* temp; temp=this;
		TreeNode<T>* x=this->lower_helper(temp,data); 
		this->deleteNode(data);
		temp=this->minimum(x);
		return x->data;
	}
	TreeNode<T> *upper_helper(TreeNode<T>* temp,T data){
		if(temp==NULL) return NULL;
		if(temp->left!=NULL && temp->left->data==data){return temp;}
		if(temp->right!=NULL && temp->right->data==data){ return temp;}
		else if(temp->data<data){
			return this->upper_helper(temp->right,data);
		}
		else{
			return this->upper_helper(temp->left,data);
		}
		return NULL;
	}
	T upper_bound(T data){
		this->insert(data);
		TreeNode<T>* temp; temp=this;
		TreeNode<T>* x=this->upper_helper(temp,data); 
		this->deleteNode(data);
		temp=this->minimum(x);
		return x->data;
	}
	void rangeQuerry(TreeNode<T>* temp,T left,T right,int &count){
		if(temp==NULL) return;
		this->rangeQuerry(temp->left,left,right,count);
		if(temp->data>left && temp->data<right) count++;
		this->rangeQuerry(temp->right,left,right,count);
	}
	int rangeQuerry(T left,T right){
		int count=0;
		TreeNode<T>* temp=this;
		this->rangeQuerry(temp,left,right,count);
		return count;
	}

};

int main(){
	TreeNode<int>* tree=new TreeNode<int>(5);
	tree->insert(10);
	tree->insert(12);
	tree->insert(10);
	tree->insert(4);
	tree->insert(3);
	tree->insert(2);
	tree->insert(1);
	tree->insert(0);
	tree->inOrder();
	cout<<endl;
	if(tree->search(20)){
		cout<<"20 is present"<<endl;
	}
	else{
		cout<<"20 is not present"<<endl;
	}
	tree->deleteNode(4);
	tree->deleteNode(2);
	tree->inOrder();
	cout<<endl;
	cout<<tree->closestValue(5)<<endl;
	tree->KthLargestElement(4);
	cout<<tree->countFrequency(12)<<endl;
	cout<<tree->rangeQuerry(1,10)<<endl;
	cout<<tree->upper_bound(10)<<endl;
	return 0;
}
