#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
int infinity=1000000000;
class Graph{
	// It stores adjacency list with edge, weight pair.
	vector<vector<pair<int,int>>> edges;
	int no_of_vertices;
	int no_of_edges;
	public:
	Graph(vector<vector<pair<int,int>>>& edges, int no_of_edges){
		this->edges=edges;
		this->no_of_vertices=edges.size();
		this->no_of_edges=no_of_edges;
	}
	
	int minimum(int a,int b){
		if(a<b) return a;
		return b;
	}
	
	vector<vector<int>> kShortestPaths(int k){
		vector<vector<int>> ans;
		for(int i=0;i<no_of_vertices;i++){
			vector<vector<int>> temp=pathsFromSource(i);
			for(int j=0;j<temp.size();j++){
				vector<int> t=temp[j];
				reverse(t.begin(),t.end());
				bool b=false;
				for(int k=0;k<ans.size();k++){
					if(t==ans[k]){
						b=true; break;
					}
				}
				if(t.size()>1 && !b) ans.push_back(temp[j]);
			}
		}
		//return ans;		
		return helper(ans,minimum(ans.size(),k));
	}
	
	bool static compare(pair<int,vector<int>> a, pair<int,vector<int>> b){
		if(a.first<b.first) return true;
		if(a.first>b.first) return false;
		int l;
		if(a.second.size()<b.second.size()) l=a.second.size();
		else l=b.second.size();
		for(int i=0;i<l;i++){
			if(a.second[i]<b.second[i]) return true;
			if(b.second[i]<a.second[i]) return false;
		}
		return a.second.size()<b.second.size();
	}
	vector<vector<int>> helper(vector<vector<int>> &paths,int k){
		vector<pair<int,vector<int>>> v(minimum(paths.size(),k));
		for(int i=0;i<paths.size();i++){
			int cost=0;
			for(int j=0;j<paths[i].size()-1;j++){
				vector<pair<int,int>> temp=edges[paths[i][j]];
				int x=paths[i][j+1]; bool b=false;
				for(int k=0;k<temp.size();k++){
					if(temp[k].first==x){
						cost+=temp[k].second;
						b=true;
						break;
					}
				}
				if(!b) cost=1e9;
			}
			/*cout<<cost<<": ";
			for(int j=0;j<paths[i].size();j++) cout<<paths[i][j]<<" ";
			cout<<endl;
			*/v.push_back(make_pair(cost,paths[i]));
		}
		sort(v.begin(),v.end(),compare);
		vector<vector<int>> ans;
		for(int i=0;i<v.size();i++){
			if(v[i].first==0) continue;
			ans.push_back(v[i].second);
			if(ans.size()==k) break;
		}
		return ans;
	}
	vector<vector<int>> pathsFromSource(int source){
		vector<vector<int>> ans;
		vector<vector<int>> v;
		for(int i=0;i<=no_of_vertices;i++){
			if(i!=source){
				vector<vector<int>> temp=findAllPaths(source,i);
				for(int j=0;j<temp.size();j++){
					reverse(temp[j].begin(),temp[j].end());
					v.push_back(temp[j]);
				}
				temp=helper(v,v.size());
				if(temp.size()>0) ans.push_back(temp[0]);
				v.clear(); 
			}
		}
		//return ans;
		return helper(ans,ans.size());
	}
	vector<vector<int>> findAllPaths(int s, int d)
	{
		vector<bool> vis(no_of_vertices);
 
    		vector<int> paths(no_of_vertices);
    		int index = 0; 
 
    		for (int i = 0; i < no_of_vertices; i++)
        		vis[i] = false;
        	vector<vector<int>> ans;
 
    		findPathshelper(s, d, vis, paths, index,ans);
    		return ans;
	}

	void findPathshelper(int u, int d, vector<bool> vis, vector<int>paths, int& index,vector<vector<int>> &ans){
    		vis[u] = true;
    		paths[index] = u;
    		index++;
    		if (u == d) {
    			vector<int> t;
        		for (int i = 0; i < index; i++){
            			t.push_back(paths[i]); 
            		}
            		ans.push_back(t);
    		}
    		else 
    		{
        		for (int i = 0; i != edges[u].size(); i++)
            			if (!vis[i])
                			findPathshelper(i, d, vis, paths, index,ans);
    		}
 
    		index--;
    		vis[u] = false;
	}	
};
class cell {
public:
    int x;
    int y;
    int cost;
    cell(int x, int y, int w){
    	this->x=x;
    	this->y=y;
    	this->cost=w;
    }
};
int bfs(char grid[][100], int N, int M,int sx,int sy)
{
    grid[1][0]='d';
    cell src(sx, sy, 0);
    bool vis[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
        {
            if (grid[i][j] == '#')
                vis[i][j] = true;
            else
                vis[i][j] = false;
	}
    }
    src.x=sx; src.y=sy;
    queue<cell> q;
    q.push(src);
    vis[src.x][src.y] = true;
    while (!q.empty()) {
        cell p = q.front();
        q.pop();
 
        if (grid[p.x][p.y] == 'd')
            return p.cost;

        if (p.x - 1 >= 0 && vis[p.x - 1][p.y] == false) {
            q.push(cell(p.x - 1, p.y, p.cost + 1));
            vis[p.x - 1][p.y] = true;
        }
 
        if (p.x + 1 < N && vis[p.x + 1][p.y] == false) {
            q.push(cell(p.x + 1, p.y, p.cost + 1));
            vis[p.x + 1][p.y] = true;
        }
 
        if (p.y - 1 >= 0 && vis[p.x][p.y - 1] == false) {
            q.push(cell(p.x, p.y - 1, p.cost + 1));
            vis[p.x][p.y - 1] = true;
        }
 
        if (p.y + 1 < M && vis[p.x][p.y + 1] == false) {
            q.push(cell(p.x, p.y + 1, p.cost + 1));
            vis[p.x][p.y + 1] = true;
        }
    }
    return 1e9;
}
int main(){

	int n,e;
	cin>>n>>e;
	vector<vector<pair<int,int>>> edges(n);
	for(int i=0;i<e;i++){
		int x,y,d; 
		cin>>x>>y>>d;
		edges[x].push_back(make_pair(y,d));
		edges[y].push_back(make_pair(x,d));
	} 
	Graph *g=new Graph(edges,2*e);
	int source=3;
	vector<vector<int>> ans=g->pathsFromSource(source);
	reverse(ans.begin(),ans.end());
	cout<<"The shortest paths to "<<source<<" are :"<<endl;
	for(int i=0;i<ans.size();i++){
		vector<int> t=ans[i];
		for(int j=0;j<t.size();j++){
			cout<<t[j]<<" ";
		}
		cout<<endl;
	}
	int k=3;
	vector<vector<int>> fans=g->kShortestPaths(k);
	cout<<"The K shortest paths are: "<<endl;
	for(int i=0;i<fans.size();i++){
		vector<int> t=fans[i];
		if(t.size()==0) continue;
		for(int j=0;j<t.size();j++){
			cout<<t[j]<<" ";
		}		
		cout<<endl;
	}
	int p,q; cin>>p>>q;
	char grid[100][100]; int sx; int sy;
	for(int i=0;i<p;i++){
		for(int j=0;j<q;j++){
			cin>>grid[i][j];
		}
	}
	vector<int> v;
	for(int i=0;i<p;i++){
		for(int j=0;j<q;j++){
			if(grid[i][j]=='R'){
				sx=i; sy=j;
				break;
			}		
		}
		int dist;
		if(sx!=0 && sy!=0) {dist=bfs(grid,p,q,sx,sy);		
				v.push_back(dist);
		}
	}bool b=false;
	for(int i=0;i<p;i++){
		for(int j=0;j<q;j++){
			if(grid[i][j]=='A'){
				sx=i; sy=j; b=true; break;
			}		
		}
		if(b) break;
	}
	int dist=bfs(grid,p,q,sx,sy);
	int maxi=1e9;
	for(int i=0;i<v.size();i++){
		if(v[i]==0) continue;
		if(dist>v[i]){cout<<"No"<<endl; return 0;}
	}
	cout<<"Yes"<<endl; cout<<dist<<endl;
	return 0;
}
