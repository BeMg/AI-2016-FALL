#include <bits/stdc++.h>
using namespace std;

const int MAX_TABLE_SIZE = 100;

struct table_for_dfs {
    int size;
    int table[MAX_TABLE_SIZE][MAX_TABLE_SIZE];
};

int DFS(table_for_dfs curr, int now_row) {
    int size = curr.size;

    if(now_row == size) {
	return 1;
    }


    for(int i=0; i<size; i++) {

	if(curr[now_row][i] == 0) {
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
