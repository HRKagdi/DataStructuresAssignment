#include<iostream>
using namespace std;

template <typename T>
class Deque{
	T * queue;
	int front; 
	int end;
	int left;
	int right;
	int queueSize;
	int spaceLeft;
	public:
	Deque(){

	}
	Deque(int size,T x){
		this->queue=new T[size];
		for(int i=0;i<size;i++){
			this->queue[i]=x;
		}
		this->front=this->left=0;
		this->end=this->right=size-1;
		this->queueSize=0;
		this->spaceLeft=size;
	}
	void push_back(T data){
		if(this->spaceLeft>0){
			this->queue[end--]=data;
			this->queueSize++;
			this->spaceLeft--;
		}
		else{
			this->resize();
			this->push_back(data);
		}
		return;
	}
	void push_front(T data){
		if(this->spaceLeft>0){
			this->queue[front++]=data;
			this->queueSize++;
			this->spaceLeft--;
		}
		else{
			this->resize();
			this->push_front(data);
		}
		return;
	}
	void pop_back(){
		int capacity=this->queueSize+this->spaceLeft;
		if(this->end<capacity-1){
			this->queue[left++]=0;
			this->queueSize--;
			this->spaceLeft++;
		}
		else{
			this->resize();
		}
		return ;
	}
	void pop_front(){
 		if(this->front>0){
 			this->queue[right--]=0;
 			this->queueSize--;
 			this->spaceLeft++;
 		}
		return ;		
	}
	T frontQ(){
		if(this->front>0){
			return this->queue[left];
		}
		return -1;
	}	
	T backQ(){
		int capacity=this->queueSize+this->spaceLeft;
		if(this->end<capacity-1){
			return this->queue[right];
		}
		return -1;
	}
	bool empty(){
		return this->queueSize==0;
	}	
	int size(){
		return this->queueSize;
	}
	void clear(){
		delete [] this->queue;
		this->queueSize=0;
		this->SpaceLeft=0;
	}	
	T operator[](int n)  const{
		int capacity=this->queueSize+this->spaceLeft;
		if(n<=this->front && n>=0){
			return this->queue[n];
		}	
		else if(n>=this->end && n<capacity){
			return this->queue[n];
		}
		return ;
	}
	
	void print(){
		for(int i=this->left;i<this->front;i++){
			cout<<this->queue[i]<<" ";
		}
		for(int i=this->right;i>this->end;i--){
			cout<<this->queue[i]<<" ";
		}
		cout<<endl;
		return ;
	}
	T& operator[](int n){
		if(this->left+n<this->capacity){
			return this->queue[left+n-1];
		}
		return 0;
	}
	
	void resize(){
		int capacity=this->queueSize+this->spaceLeft;
		T * temp=new T[2*capacity];
		for(int i=0;i<2*capacity;i++){ 
			temp[i]=0;
		}
		int a=0; int b=capacity-1;
		for(int i=this->left-1;i<this->front;i++){
			temp[a++]=this->queue[i];
		}
		for(int i=this->right+1;i>this->end;i--){
			temp[b--]=this->queue[i];
		}
		this->queue=temp;
		this->spaceLeft=2*capacity-this->queueSize;
		this->front=a; this->end=b;
		
	}
	
};

int main(){
	Deque<int> * myQueue=new Deque<int>(10,0);
	myQueue->push_back(1);
	myQueue->push_back(2);
	myQueue->push_back(3);
	myQueue->push_back(4);
	myQueue->push_back(5);
	myQueue->push_back(6);
	myQueue->push_front(7);
	myQueue->push_front(8);
	myQueue->push_front(9);
	
	myQueue->print();
	cout<<"Size: "<<myQueue->size()<<endl;
	
	myQueue->pop_front();
	myQueue->pop_back();
	
	myQueue->print();
	cout<<"Size: "<<myQueue->size()<<endl;		
	cout<<"ELement at front: "<<myQueue->frontQ()<<endl;
	cout<<"Element at back: "<<myQueue->backQ()<<endl;
	
	cout<<"Is empty: "<<myQueue->empty()<<endl;
	myQueue->print();
	cout<<myQueue->size()<<endl;
	return 0;
}
