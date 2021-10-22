#include<iostream>
#include<string>
using namespace std;
bool dfs(char board[][100], int i,int j, int len,string word,int n){
        if(len==word.size()) return true;
        if(i<0 || j<0 || i>n-1 || j>n-1 || board[i][j]!=word[len]){
            return false;
        }
        char ch=board[i][j];
        board[i][j]=' ';
        bool b=dfs(board,i+1,j,len+1,word,n) || dfs(board,i,j+1,len+1,word,n) 
            || dfs(board,i-1,j,len+1,word,n) || dfs(board,i,j-1,len+1,word,n);
        
        board[i][j]=ch;
        return b;
}
bool helper(char board[][100], string word,int n) {
        int l,m; l=m=n;
        for(int i=0;i<l;i++){
            for(int j=0;j<m;j++){
                if(board[i][j]==word[0]){
                    if(dfs(board,i,j,0,word,n))
                        return true;
                }
            }
        }
        return false;
}
bool compare(string s1, string s2){
	int l=min(s1.size(),s2.size());
	for(int i=0;i<l;i++){
		if(s1[i]-'a'<s2[i]-'a')
			return true;
	}
	return s1.size()<s2.size();
}
void Sort(string arr[],int l){
	for(int i=1;i<l;i++){
		string str=arr[i];
		int j=i-1;
		for(;j>=0;j--){
			if(compare(str,arr[j])){
				arr[j+1]=arr[j];
			}
			else break;
		}
		arr[j+1]=str;
	}
}
int main(){
	int n; cin>>n;
	char board[100][100];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			char ch; cin>>ch;
			board[i][j]=ch;
		}
	}
	int l; cin>>l;
	string words[l];
	for(int i=0;i<l;i++){
		cin>>words[i];
	}
	string arr[100]; int j=0;
	for(int i=0;i<l;i++){
		if(helper(board,words[i],n)){
			arr[j++]=words[i];
		}
	}
	Sort(arr,j); 
	for(int i=0;i<j;i++){
		cout<<arr[i]<<endl;
	}
	return 0;
}
