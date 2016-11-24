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

int DFS(table_for_dfs curr, int now_row) {
    int size = curr.size;

    if(now_row == size) {
	return 1;
    }

    for(int i=0; i<size; i++) {

	if(curr.table[now_row][i] == 0) {
	   table_for_dfs tmp = mark_fail(curr, now_row, i);
	   int ret = DFS(tmp, now_row+1);
	   if(ret) return 1;
	}
    
    }
    return 0;
}


int main() {


    return 0;
}
