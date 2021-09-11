#include<iostream> 
using namespace std;
template <typename T>
class Node{
	public:
	int x;
	int y;
	T data;
	Node * next;
};
template <typename T>
class SparseMatrices{
	Node<T> * matrix;
	int capacity;
	int size;
	public:
	SparseMatrices(int size){
		this->size=size;
		this->capacity=capacity;
		this->matrix=new Node<T>();
	}
	
	void transpose(){
		Node<T> * temp=this->matrix;
		while(temp!=NULL){
			int t=temp->x;
			temp->x=temp->y;
			temp->y=t;
			temp=temp->next;
		}
	}
	
	void print(){
		Node<T> * temp=this->matrix;
		while(temp->next!=NULL && temp->data!=0){
			cout<<temp->x<<" "<<temp->y<<" "<<temp->data<<endl;
			temp=temp->next;
		}	
	}
	
	void addElement(int x,int y,T data){
		Node<T> * t=new Node<T>;
		t->x=x; t->y=y; t->data=data;
		t->next=this->matrix;
		this->matrix=t;
		this->capacity++;
	}
	
	void Add(SparseMatrices<T>* mat){
		Node<T> * t1=this->matrix; Node<T> * t2=mat->matrix;
		while(t1!=NULL){
			int x=t1->x;
			int y=t1->y;
			t2=mat->matrix;
			while(t2!=NULL){
				if(x==t2->x && y==t2->y){
					t1->data+=t2->data;
				}
				t2=t2->next;
			}
			t1=t1->next;
		}
		while(t2!=NULL){
			int x=t2->x; int y=t2->y;
			t1=this->matrix; bool b=false;
			while(t1!=NULL){
				if(x==t1->x && y==t1->y){
					b=true;
				}
				t1=t1->next;
			}
			if(!b){
				this->addElement(x,y,t2->data);
			}
			t2=t2->next;
		}
	}
	
	void Multiply(SparseMatrices<T>* mat){
  		SparseMatrices<T>* res=new SparseMatrices<T>(this->capacity+mat->capacity);
  		Node<T> *t1,*t2,*temp;
  		temp=new Node<T>();
  		t1=this->matrix->next;
 		 while(t1!=NULL)
  		{
   			t2=mat->matrix->next;
   			while(t2->next!=NULL)
   			{
    				if(t1->y==t2->x)
    				{
    					temp->x=t1->x;
    					temp->y=t2->y;
    					temp->data=(t1->data)*(t2->data);
   					temp->next=NULL;
    					res->addElement(temp->x,temp->y,temp->data);
    				}
    				t2=t2->next;
   			}
   			if(t2->next==NULL)
   			{
    				if(t1->y==t2->x)
    				{
    					temp->x=t1->x;
    					temp->y=t2->y;
    					temp->data=(t1->data)*(t2->data);
    					temp->next=NULL;
    					res->addElement(temp->x,temp->y,temp->data);
    				}
   			}
   			t1=t1->next;
  		}

  		res->matrix->x=this->matrix->x;
  		res->matrix->y=mat->matrix->y;
  		res->print(); 
  		//cout<<res->capacity;
	
	}	
};
int main(){
	cout<<"Enter the matrices"<<endl;
	cout<<"Enter the size"<<endl;
	int size; cin>>size; 
	cout<<"Enter the number of elements to be added"<<endl;
	int z; cin>>z;
	SparseMatrices<int> * mat1=new SparseMatrices<int>(size);
	for(int i=0;i<z;i++){
		int x,y,value; cin>>x>>y>>value;
		mat1->addElement(x,y,value);
	}
	cout<<"Enter second matric of size "<<size<<endl;
	cout<<"Enter number of elements to be added"<<endl;
	int num; cin>>num;
	SparseMatrices<int> * mat2=new SparseMatrices<int>(size);
	for(int i=0;i<num;i++){
		int x,y,value; cin>>x>>y>>value;
		mat2->addElement(x,y,value);
	}
	mat1->Multiply(mat2);
	//mat1->Add(mat2);
	//mat1->transpose();
	//mat1->print();
	return 0;	
}
