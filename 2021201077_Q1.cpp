#include <bits/stdc++.h>
using namespace std;
class TrieNode {
   public:
    char data;
    TrieNode **children;
    bool isTerminal;
     

    TrieNode(char data) {
               this->data = data;
               children = new TrieNode *[26];
               for (int i = 0; i < 26; i++) {
                     children[i] = NULL;
               }
               isTerminal = false;

    }
};

class Trie {
    TrieNode *root;

   public:
    int count;

    Trie() {
            this->count = 0;
             root = new TrieNode('\0');
    }

    bool insertWord(TrieNode *root, string word) {
        // Base case
        if (word.size() == 0) {
            if (!root->isTerminal) {
                root->isTerminal = true;
                return true;
            }
           else {
                return false;
            }
        }

        int index = word[0] - 'a';
        TrieNode *child;
        if (root->children[index] != NULL) {
            child = root->children[index];
        } else {
            child = new TrieNode(word[0]);
            root->children[index] = child;
        }

        return insertWord(child, word.substr(1));
    }
	void insertWord(string word) {
        	 if (insertWord(root, word)) {
        	    this->count++;
        	}
	}
	bool search(TrieNode* root,string patt){
		    if(root->isTerminal) return true;
		    if(patt.size()==0) return false;
        	    int index=patt[0]-'a';
        	    if(root->children[index]) return search(root->children[index],patt.substr(1));
        	    return false;
	}
	bool search(string word){
        	return search(root,word);
	}
	void deleteWord(TrieNode *root, string word) {
        	if(word.size() == 0) {
        	    root -> isTerminal = false;
        	    return;
        	}
	
        	TrieNode *child;
        	int index =  word[0] - 'a';
        	if(root -> children[index] != NULL) {
        	    child = root -> children[index];
        	}
        	else {
        	    // Word not found
        	    return;
        	}
	
        	deleteWord(child, word.substr(1));
	
        	// Remove child Node if it is useless
        	if(child -> isTerminal == false) {
        	    for(int i = 0; i < 26; i++) {
        	        if(child -> children[i] != NULL) {
        	            return;
        	        }
        	    }
        	    delete child;
        	    root -> children[index] = NULL;
        	     }
    	}	
	
    void deleteWord(string word) {
            deleteWord(root, word);
    }
    TrieNode* findroot(TrieNode* root,string word){
        if(word.size()==0){
            return root;
        }
        int index=word[0]-'a';
        if(root->children[index]==NULL){
            return NULL;
        }
        return findroot(root->children[index],word.substr(1));
    }
    void print(TrieNode*root,string prefix,string out){
           if(root->isTerminal){
           	cout<<prefix<<out.substr(1)<<root->data<<endl;
           	out="";
           	return;
           }
           for(int i=0;i<26;i++){
           	if(root->children[i]!=NULL){
           		out+=root->data;
           		this->print(root->children[i],prefix,out);
           		out.pop_back();
           	}
           }
   }
   void autoComplete(TrieNode* root, vector<string> input, string pattern,string original){
   	if(pattern.size()==0){
   		this->print(root,original,"");
   	}
   	int index=pattern[0]-'a';
   	if(root->children[index]!=NULL){
   		this->autoComplete(root->children[index],input,pattern.substr(1),original);
   	}
   	
   }
    void autoComplete(vector<string> input, string pattern) {
		this->autoComplete(this->root,input,pattern,pattern);
        
    }


};
int edit_distance(string x, string y){
	int l1=x.size(); int l2=y.size();
	vector<vector<int>> dp;
        for(int i=0;i<=l1;i++){
            vector<int> v(l2+1,0);
            dp.push_back(v);
        }
	for(int i=0;i<=l1;i++){
		for(int j=0;j<=l2;j++){
			if(i==0) dp[i][j]=j;
			else if(j==0) dp[i][j]=i;
			else if(x[i-1]==y[j-1]) dp[i][j]=dp[i-1][j-1];
			else {
				dp[i][j]=1+min(dp[i-1][j-1],min(dp[i-1][j],dp[i][j-1]));
			}
		}
	}
	return dp[l1][l2];
}

int main(){
    int n;
    cin>>n;
    vector<string> v(n);
    Trie* dict=new Trie();
    for(int i=0;i<n;i++){
    	string str; cin>>str;
    	dict->insertWord(str);
    	v.push_back(str);
    }
    int testcase; string str;
    cin>>testcase>>str;
    if(testcase==1){
    	cout<<dict->search(str)<<endl;
    }
    else if(testcase==2){
    	dict->autoComplete(v,str);
    }
    else if(testcase==3){
    	vector<string> ans;
    	for(int i=0;i<v.size();i++){
    		if(edit_distance(v[i],str)<=3){
    			ans.push_back(v[i]);
    		}
    	}
    	sort(ans.begin(),ans.end());
    	for(int i=0;i<ans.size();i++){
    		if(ans[i].size()>0) cout<<ans[i]<<endl;
    	}
    }
    return 0;
}
