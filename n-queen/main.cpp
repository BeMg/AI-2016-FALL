#include <bits/stdc++.h>
using namespace std;

const int MAX_TABLE_SIZE = 100;

struct table_for_dfs {
    int size;
    int table[MAX_TABLE_SIZE][MAX_TABLE_SIZE];
};

table_for_dfs mark_fail(table_for_dfs curr, int x, int y) {
    int size = curr.size;

    for(int i=0; i<size; i++) {
	curr.table[i][y] = -1;
	curr.table[x][i] = -1;
	if((x+i)<size && (y+i)<size)
	    curr.table[x+i][y+i] = -1;
	if((x-i)>=0 && (y-i)>=0)
	    curr.table[x-i][y-i] = -1;
	if((x+i)<size && (y-i)>=0)
	    curr.table[x+i][y-i] = -1;
	if((x-i)>=0 && (y+i)<size)
	    curr.table[x-i][y+i] = -1;
    }
    curr.table[x][y] = 1;

    return curr;
    
}

vector<int> tabletostring(table_for_dfs curr) {
    vector<int> result;
    int size = curr.size;
    for(int i=0; i<size; i++) {
	for(int j=0; j<size; j++) {
	    if(curr.table[i][j] == 1) {
		result.push_back(j);
		break;
	    }
	}
    }
    return result;
}

vector<int> DFS(table_for_dfs curr, int now_row) {
    int size = curr.size;

    if(now_row == size) {
	return tabletostring(curr);
    }

    for(int i=0; i<size; i++) {

	if(curr.table[now_row][i] == 0) {
	   table_for_dfs tmp = mark_fail(curr, now_row, i);
	   vector<int> ret = DFS(tmp, now_row+1);
	   if(!ret.empty()) return ret;
	}
    
    }
    vector<int> emp;
    return emp;
}

vector<int> solve_by_dfs(int size) {
    if(size>MAX_TABLE_SIZE) {
	cout << "Size MUST less than" << MAX_TABLE_SIZE << endl;
	cout << "DFS solve fail." << endl;
	vector<int> emp;
	return emp;
    }
    
    table_for_dfs s;

    s.size = size;
    memset(s.table, 0, sizeof(s.table));
    
    vector<int> result = DFS(s,0);
    
    return result;
}


int main() {
    
    int n;
    cin >> n;
    
    vector<int> ans = solve_by_dfs(n);

    for(auto i: ans) {
	cout << i << " ";
    }
    cout << endl;

    return 0;
}
