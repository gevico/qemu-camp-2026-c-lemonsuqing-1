#include <stdio.h>
#include <stdbool.h>

#define MAX_ROW 5
#define MAX_COL 5

int path_len = 0;
int path_x[100];
int path_y[100];

bool st[MAX_ROW][MAX_COL] = {false};
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int found = 0;

void dfs(int x, int y){
	if(found) return;

	path_x[path_len] = x;
	path_y[path_len] = y;
	path_len++;

	if(x == MAX_ROW-1 && y == MAX_COL-1){
		found = 1;
		for(int i = path_len - 1; i >= 0; i--){
			printf("(%d, %d)\n", path_x[i], path_y[i]);
		}
		return;
	}

	st[x][y] = true;

	for(int i = 0; i < 4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		if(nx >=0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && !st[nx][ny] && maze[nx][ny] == 0){
			dfs(nx, ny);
		}
	}

	path_len--;
	st[x][y] = false;
	return;
}

int main(void)
{
	dfs(0, 0);

	return 0;
}