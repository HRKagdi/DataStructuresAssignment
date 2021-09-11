#include<iostream>
using namespace std;
template <typename T>
class SparseMatrices{
	T ** matrix=new T *[3];
	int size;
	int capacity;
	public :
	SparseMatrices(int size){
		this->size=size;
		for(int i=0;i<3;i++){
			matrix[i]=new T[size];
		}
		this->capacity=0;
	}
	
	void addElement(int r,int c,T value){
		matrix[0][capacity]=r;
		matrix[1][capacity]=c;
		matrix[2][capacity]=value;
		
		capacity++;
	}
	
	void transpose(){
		for(int i=0;i<size;i++){
			T temp=this->matrix[0][i];
			this->matrix[0][i]=this->matrix[1][i];
			this->matrix[1][i]=temp;
		}
	}
	
	void Add(SparseMatrices<T> *mat){
		for(int i=0;i<this->size;i++){
			int x=this->matrix[0][i];
			int y=this->matrix[1][i];
			bool b=false;
			for(int j=0;j<this->size;j++){
				if(x==mat->matrix[0][j] && y==mat->matrix[1][j]){
					this->matrix[0][i]=x;
					this->matrix[1][i]=y;
					this->matrix[2][i]=this->matrix[2][i]+mat->matrix[2][j];
				}
			}
		}
		
		for(int i=0;i<this->size;i++){
			int x=mat->matrix[0][i];
			int y=mat->matrix[1][i];
			bool b=false;
			for(int j=0;j<this->size;j++){
				if(x==this->matrix[0][j] && y==this->matrix[1][j]){
					b=true;
				}
			}
			if(!b){
				this->addElement(x,y,mat->matrix[2][i]);
			}
		}	
	}
	void print(){
		for(int i=0;i<this->capacity;i++){
			cout<<this->matrix[0][i]<<" "<<this->matrix[1][i]
			<<" "<<this->matrix[2][i]<<endl; 
		}
	}
	void Multiply(SparseMatrices<T> * mat){
	if (this->size != mat->size)
        {
            cout << "Can't multiply, Invalid dimensions";
            return;
        }

        mat->transpose();
        int apos, bpos;
  
        SparseMatrices<T>* result=new SparseMatrices(this->capacity+mat->capacity);
  
        for (apos = 0; apos < this->capacity;)
        {
            T r = this->matrix[0][apos];
  
            for (bpos = 0; bpos < mat->capacity;)
            {
                T c = mat->matrix[0][bpos];
  
                T tempa = apos;
                T tempb = bpos;
  
                T sum = 0;
  
                while (tempa < this->capacity && this->matrix[0][tempa] == r &&
                       tempb < mat->capacity && mat->matrix[0][tempb] == c)
                {
                    if (this->matrix[1][tempa] < mat->matrix[1][tempb])
  
                        tempa++;
  
                    else if (this->matrix[1][tempa] > mat->matrix[1][tempb])
                        tempb++;
                    else
                        sum += this->matrix[2][tempa++] * 
                             mat->matrix[2][tempb++];
                }
  

                if (sum != 0)
                    result->addElement(r, c, sum);
  
                while (bpos < mat->capacity && 
                       mat->matrix[0][bpos] == c)
 
                    bpos++;
            }
            while (apos < this->capacity && this->matrix[0][apos] == r)
 
                apos++;
        }
        result->print();
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
