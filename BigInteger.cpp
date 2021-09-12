#include<iostream>
#include<string>
#include<stack>
using namespace std;
template <typename T>
class Block{
	public:
	T data;
	Block * next;
	
	Block(T data){
		this->data=data;
		this->next=NULL;
	}
};
template <typename T>
class Stack {
    Block<T> * tp;
    int size=0;
   public:
    Stack() {
        tp=NULL;
        size=0;
    }


    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size==0;
    }

    void push(T element) {
        Block<T> * temp=new Block<T>(element);
        temp->next=tp;
        tp=temp;
        size++;
    }

    T pop() {
        if(size==0){
            return -1;
        }
        Block<T> * a=tp;
        tp=tp->next;
        int data=a->data;
        delete a;
        size--;
        return data;
    }

    T top() {
        if(size>0){
            return tp->data;
        }
        return -1;
    }
};
class Node{
	public:
	int data;
	Node * next;
	
	//Constructor
	Node(int data){
		this->data=data;
		this->next=NULL;
	}
};

class BigInteger{
	Node * Integer;
	int size;
	bool isNegative;
	public:
	//Constructor
	BigInteger(string integer){
		int l=integer.size();
		Integer=NULL;
		for(int i=0;i<l;i++){
			int x=integer[i]-'0';
			Node* temp=new Node(x);
			temp->next=Integer;
			Integer=temp;
			size++;
		}
		isNegative = false;
	}
	
	
	
	//Addtion of two BigIntegers
	void Add(BigInteger *num){
		    int carry=0;
        	int a=this->size; int b=num->size;
        	if(a==1 && this->Integer->data==0){this->Integer=num->Integer; this->size=num->size; return ;}
        	if(b==1 && num->Integer->data==0) return ;
        	if(a>b){
            		int x=a-b; 
            		Node * p=num->Integer;
            		while(p->next!=NULL) p=p->next;
            		for(int i=1;i<=x;i++){
            			Node * temp=new Node(0);
            			p->next=temp; p=temp;
            		}
            	}
        	else{
            		int x=b-a;
            		Node * p=this->Integer;
            		while(p->next!=NULL) p=p->next;
            		for(int i=1;i<=x;i++){
            			Node * temp=new Node(0);
            			p->next=temp; p=temp;
            		}
            		
        	}
        	Node * p=this->Integer; Node * q=num->Integer; 
        	for(int i=1;i<=max(a,b);i++){
        	    int t=p->data+q->data+carry;  
            	   if(t<10){ p->data=t; carry=0;}
            	   else {
                	int temp=t%10; t/=10;
                	p->data=temp; carry=t;
            	  }
            	  p=p->next; q=q->next;
        	}
  	      if(carry!=0){
  	          Node * temp=new Node(carry);
  	          p=this->Integer; while(p->next!=NULL) p=p->next;
  	          p->next=temp;
  	          size++;
  	      }
	}
	
	bool equals(BigInteger* num){
	    if(this->size!=num->size) return false;
        Node * t1=this->Integer; Node * t2=num->Integer;
        while(t1!=NULL && t2!=NULL){
            if(t1->data!=t2->data) return false;
            t1=t1->next; t2=t2->next;
        }
        return true;
	}
	//Printing a BigInteger
	void print(){
		Node * temp=this->Integer;
		int arr[this->size]; int ind=0;
		while(temp!=NULL){
			arr[ind++]=temp->data;
			temp=temp->next;
		}
		for(int i=this->size-1;i>=0;i--) cout<<arr[i];
		cout<<endl;
	}
	
	string ToString(){
	    string str="";
	    Node * temp=this->Integer;
	    while(temp!=NULL){
	        char ch=temp->data+'0';
	        str+=ch;
	        temp=temp->next;
	    }
	    for(int i=0;i<str.size()/2;i++){
	        char ch=str[i]; str[i]=str[str.size()-i-1]; str[str.size()-i-1]=ch;
	    }
	    return str;
	}
	
	void helper_multiply(int n){
	     int carry=0; Node * temp=this->Integer;
	     while(temp!=NULL){
	     	int x=temp->data*n+carry; 
	     	if(x>9){
	     		int rem=x%10;
	     		temp->data=rem;
	     		carry=x/10;   
	     	}
	     	else{
	     		carry=0; temp->data=x;
	     	}
	     	temp=temp->next;
	     }
	     if(carry!=0){
            Node * temp=new Node(carry);
  	        Node *p=this->Integer; while(p->next!=NULL) p=p->next;
  	        p->next=temp;
  	        size++;
	     }
	}
	void padzeros(int c){
	    Node * temp=this->Integer;
	    for(int i=1;i<=c;i++){
	        Node * t=new Node(0);
	        t->next=temp;
	        temp=t;
	    }
	    this->Integer=temp;
	    this->size+=c;
	}
	//Multiplication of Two Numbers
	void Multiply(BigInteger * num){
	    int counter=0; Node * n1=num->Integer;
	    string str=this->ToString();
	    BigInteger * ans=new BigInteger("0");
	    while(counter<num->size){
	        BigInteger * x=new BigInteger(str);
	    	x->helper_multiply(n1->data);
	    	x->padzeros(counter);
	        n1=n1->next; 
	        ans->Add(x);
	        ans->size=x->size;
	        counter++;
	    }
	    this->Integer=ans->Integer;
	    this->size=ans->size;
	}
	void swap(BigInteger * num){
		Node* temp=this->Integer;
		this->Integer=num->Integer;
		num->Integer=temp;
		int size=this->size;
		this->size=num->size;
		num->size=size;
	}
	void Subtraction(BigInteger * num){
		if(num->isGreater(this)){
			
			this->swap(num);
		}
		int borrow=0;
        	int a=this->size; int b=num->size;
        	if(a==1 && this->Integer->data==0){this->Integer=num->Integer; this->size=num->size; isNegative=true; return ;}
        	if(b==1 && num->Integer->data==0) return ;	
        	
        	if(a<b){
        		int x=b-a; 
        		Node * p=this->Integer;
            		while(p->next!=NULL) p=p->next;
            		for(int i=1;i<=x;i++){
            			Node * temp=new Node(0);
            			p->next=temp; p=temp;
            		}
        	}
        	else if(a>b){
        		int x=a-b; 
        		Node * p=num->Integer;
            		while(p->next!=NULL) p=p->next;
            		for(int i=1;i<=x;i++){
            			Node * temp=new Node(0);
            			p->next=temp; p=temp;
            		}
        	}
        	Node * p=this->Integer; Node * q=num->Integer;
        	for(int i=0;i<this->size-1;i++){
        		if(p->data>=q->data){
        			p->data-=q->data; borrow=0;
        		}
        		else{
        			p->data=p->data+10;
        			p->data-=q->data; p->next->data-=1;
        		}
        		p=p->next; q=q->next;
        	}
        	if(p->data>=q->data){ p->data-=q->data;}
        	else{
        		p->data=p->data+10; p->data-=q->data; isNegative = true;
        	}
		
	
	}
	
	bool isGreater(BigInteger* num){
		if(this->size>num->size) return true;
		else if(this->size<num->size) return  false;
		else{
			Node * t1=this->Integer; Node * t2=num->Integer;
			while(t1->next!=NULL){
				t1=t1->next; t2=t2->next;
			}
			if(t1->data>t2->data) return true;
		}
		return false;
	}
	void helper_GCD(BigInteger* num){
		BigInteger * zero=new BigInteger("0");
		while(!this->equals(num)){
			if(this->isGreater(num)){
				this->Subtraction(num);
				if(this->equals(zero)){
				num->print(); return;}
			}
			else {
				num->Subtraction(this);
				if(num->equals(zero)){
				this->print(); return;}
			}
			
			
		}
		this->print();
	}
	//GCD of two numbers 
	void GCD(BigInteger *num){
		if(num->isGreater(this)){
			num->helper_GCD(this);
		}
		else this->helper_GCD(num);
	
	}
	//Factorial of a number
	void factorial(){
	    BigInteger * counter =new BigInteger("1");
	    BigInteger * increment =new BigInteger("1");
	    BigInteger * ans=new BigInteger("1");
	    while(!counter->equals(this)){
	        ans->Multiply(counter);
	        counter->Add(increment);
	    }
	    ans->Multiply(counter);
	    cout<<ans->size<<endl;
	    ans->print();
	}
	
	void Exponentiation(BigInteger * num){
	    BigInteger * counter =new BigInteger("1");
	    BigInteger * increment=new BigInteger("1");
	    string str=this->ToString();
	    BigInteger * x=new BigInteger(str);
	    while(!counter->equals(num)){
	   	counter->Add(increment);
	   	this->Multiply(x); 
	    }	
	    this->print();	
	}
	
	string convert(string tokens,int index){
		string str=""; int i=index;
		while(true){
			if(i==tokens.size()) break;
			int x=tokens[i]-'0';
			if(0<=x && x<=9){
				str+=tokens[i];
			}
			else break;
			i++;
		}
		return str;
	}
	
	int precedence(char op){
	    if(op == '+'||op == '-')
   		 return 1;
   	    if(op == '*')
    		return 2;
            return 0;
	}
 

	BigInteger * applyOp(BigInteger * b,char op){
		//this->print(); b->print(); 
    		switch(op){
        		case '+': this->Add(b); 
        		case '-': this->Subtraction(b);
        		case '*': this->Multiply(b);
    		}
    		return this;
	}

	void evaluate(string tokens){
    		int i;
     
		stack <BigInteger*> values;
     		stack <char> ops;
     
    		for(i = 0; i < tokens.size(); i++){
         

        	if(tokens[i] == ' ')
           		 continue;
         
        	else if(tokens[i] == '('){
            		ops.push(tokens[i]);
        	}

        	else if(0<=tokens[i]-'0' && 9>=tokens[i]-'0'){
            		string str=convert(tokens,i);
             		BigInteger* val=new BigInteger(str);
        	    	values.push(val);
			//cout<<str.size();
        	       i+=str.size()-1;
        	}

        	else if(tokens[i] == ')')
        	{
            		while(!ops.empty() && ops.top() != '(')
            		{
                		BigInteger *val2 = values.top();
                		values.pop();
                 
                		BigInteger* val1 = values.top();
                		values.pop();
                 
                		char op = ops.top();
                		ops.pop();
                 
                		values.push(val1->applyOp(val2, op));
            		}
             

            	if(!ops.empty())
               	ops.pop();
        	}
         

        	else
        	{

            		while(!ops.empty() && precedence(ops.top())
                                >= precedence(tokens[i])){
                	BigInteger* val2 = values.top();
                	values.pop();
                 
                	BigInteger *val1 = values.top();
                	values.pop();
                 
                	char op = ops.top();
               	ops.pop();
                 
                	values.push(val1->applyOp(val2, op));
            	}
             

            	ops.push(tokens[i]);
        	}
    	}
     

    	while(!ops.empty()){
        	BigInteger *val2 = values.top();
        	values.pop();
                 
        	BigInteger *val1 = values.top();
        	values.pop();
                 
        	char op = ops.top();
        	ops.pop();
                 
        	values.push(val1->applyOp(val2, op));
    	}
     

    		values.top()->print();
    		return;
	}


};



int main(){
	while(true){
		cout<<"Enter your choice:"<<endl;
		cout<<"1 for Exponentiation"<<endl;
		cout<<"2 for GCD"<<endl;
		cout<<"3 for factorial"<<endl;
		cout<<"4 for math operations"<<endl;
		cout<<"5 for calculator"<<endl;
		cout<<"6 if done"<<endl;
		
		int choice; cin>>choice;
		if(choice==6) { break;}
		else if(choice == 1){
			cout<<"Enter a number and its exponent"<<endl;
			string str1,str2; cin>>str1>>str2; cout<<endl;
			BigInteger *num=new BigInteger(str1);
			BigInteger *exponent=new BigInteger(str2);
			num->Exponentiation(exponent);		
		}
		else if(choice == 2){
			cout<<"Enter two numbers whose GCD is to be calculated"<<endl;
			string str1,str2; cin>>str1>>str2; cout<<endl;
			BigInteger * num1=new BigInteger(str1);
			BigInteger * num2=new BigInteger(str2);
			num1->GCD(num2);
		}
		else if(choice == 3){
			cout<<"Enter a number whose factorial is to be calculated"<<endl;
			string str1; cin>>str1; cout<<endl;
			BigInteger * num =new BigInteger(str1);
			num->factorial();
		}
		else if(choice == 4){
			cout<<"Enter a to add"<<endl;
			cout<<"Enter s to subtract"<<endl;
			cout<<"Enter m to multiply"<<endl;
			char choice; cin>>choice; cout<<endl;
			cout<<"Enter two numbers"<<endl;
			string str1,str2; cin>>str1>>str2;
			BigInteger* n1=new BigInteger(str1);
			BigInteger* n2=new BigInteger(str2);
			if(choice=='a'){
				n1->Add(n2); n1->print();
			}
			else if(choice=='s'){
				n1->Subtraction(n2); n1->print();
			}
			else{
				n1->Multiply(n2); n1->print();
			}
		}
		else if(choice==5){
			cout<<"Enter expression string"<<endl;
			string str; cin>>str;
			BigInteger * num=new BigInteger("0");
			num->evaluate(str);
			
		}
	}
       return 0;

}
