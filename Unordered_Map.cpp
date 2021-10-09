#include<iostream>
using namespace std;
template <typename T1,typename T2>
#include<string>
class Pair{
	public:
	T1 first;
	T2 second;
	Pair(T1 first,T2 second){
		this->first=first;
		this->second=second;
	}
};
template <typename K,typename V>
class Unordered_map{
	Pair<K,V>(* map);
	int size;
	public:
	Unordered_map(K key,V value){
		map=new Pair<K,V>(key,value);
		this->size=1009;
	}
	int helper(string str){
		int M=1000000007;
		int hash=0;
		for(int i=0;i<str.size();i++){
			hash=((hash%M)+(((str[i]-'0')%M)*((53^i)%M)%M)%M);
		}
		return hash%this->size;
	}
	void insert(K key,V value){
		string myKey=to_string(key);
		int hash=helper(myKey);
		this->map[hash].first=key;
		this->map[hash].second=value;
		//this->size++;
	}
	bool findKey(K key){
		string myKey=to_string(key);
		int hash=helper(myKey);
		if(this->map[hash].first==key) return true;
		return false;
	}
	void removeKey(K key){
		string myKey=to_string(key);
		int hash=helper(myKey);
		if(this->map[hash].first==key){
			this->map[hash].first=this->map[hash].second=0;
		}
		return ;
	}
	V findValue(K key){
		string myKey=to_string(key);
		int hash=helper(myKey);
		if(this->map[hash].first==key) return this->map[hash].second;
		return 0;
	}
	void print(){
		for(int i=0;i<this->size;i++){
			cout<<this->map[i].first<<" "<<this->map[i].second<<endl;
		}
		
	}
};
template <typename T1,typename T2>
#include<string>
class Pair{
	public:
	T1 first;
	T2 second;
	Pair<T1,T2> *next;
	Pair(T1 first,T2 second){
		this->first=first;
		this->second=second;
	}
};
template <typename K,typename V>
class Unordered_Map{
	Pair<K,V>** map;
	int size;
	public:
	Unordered_Map(K key,V value){
		map=new Pair<K,V>*[1000];
		this->size=1000;
	}
	int helper(string str){
		int M=1000000007;
		int hash=0;
		for(int i=0;i<str.size();i++){
			hash=((hash%M)+(((str[i]-'0')%M)*((53^i)%M)%M)%M);
		}
		return hash%this->size;
	}
	void insert(K key,V value){
		string myKey=to_string(key);
		int hash=helper(myKey);
		Pair<K,V> *p=this->map[hash];
		while(p!=NULL){
			if(p->first==key){
				p->second+=1;
				return ;
			}
			p=p->next;
		}
		Pair<K,V>* t=new Pair<K,V>(key,value);
		t->next=this->map[hash];
		this->map[hash]=t;
	}
	bool findKey(K key){
		string myKey=to_string(key);
		int hash=helper(myKey);
		Pair<K,V> *p=this->map[hash];
		bool b=false; 
		while(p!=NULL){
			if(p->first==key){
				b=true; break;
			}
			p=p->next;
		}
		return b;
	}
	void removeKey(K key){
		string myKey=to_string(key);
		int hash=helper(myKey);
		Pair<K,V> *p=this->map[hash];
		if(p->next==NULL){
			 p->first=p->second=-1;
		}
		while(p->next!=NULL){
			if(p->next->first==key){
				p->next=p->next->next;
				return;
			}
			p=p->next;
		}
		return ;
	}
	V findValue(K key){
		string myKey=to_string(key);
		int hash=helper(myKey);
		Pair<K,V>* p=this->map[hash];
		while(p!=NULL){
			if(p->first==key){
				return p->second;
			}
			p=p->next;
		}
		return 0;
	}
	void print(){
		for(int i=0;i<this->size;i++){
			Pair<K,V>* p=this->map[i]; bool b=false;
			while(p!=NULL){
				cout<<p->first<<" "<<p->second<<" ";
				p=p->next;
				b=true;
			}
			if(b) cout<<endl;
		}
		
	}
};
void solve(){
	int n,k; cin>>n>>k;
	int v[1000]={5};
	for(int i=0;i<n;i++) cin>>v[i];

	for(int j=0;j<=n-k;j++){
		Unordered_map<int,int>*m=new Unordered_map<int,int>(0,0);
		for(int i=0;i<k;i++){
                       if(m->findKey(v[i+j])){
				int value=m->findValue(v[i+j]);
		        	m->removeKey(v[i+j]);
		        	m->insert(v[i+j],value+1);	
			}
			else{
				m->insert(v[i+j],1);
			}			
		}
		int ans=0;
		for(int i=0;i<k;i++){
			if(m->findKey(v[i+j]) && m->findValue(v[i+j])!=-1){
				ans++;
				m->removeKey(v[i+j]);
			}
		}
		cout<<ans<<endl;
	}

}
int main(){
	Unordered_Map<int,int>* m=new Unordered_Map<int,int>(1,2);
	m->insert(1000,3);
	m->insert(1232,12);
	m->insert(11145,45);
	m->insert(1195,45);
	m->insert(125,45);
	m->insert(1345,45);
	m->insert(1745,45);
	m->insert(19045,45);
	m->insert(132,45);
	m->print();
	cout<<m->findKey(1195)<<endl;
	m->removeKey(1195);
	cout<<m->findKey(1195)<<endl;
	cout<<m->findValue(125)<<endl;
	solve();
	
	return 0;
}
