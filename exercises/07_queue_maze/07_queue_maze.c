#include <stdio.h>
#include <string.h>

#define MAX_ROW 5
#define MAX_COL 5
#define N 110

typedef struct {
    int x;
    int y;
} PII;

PII q[N*N];
int d[N][N];
// 记录前驱节点，用于路径回溯
PII prev[N][N];

int hh, tt;


int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int dsf(){
	hh = 0, tt = 0;
	memset(d, -1, sizeof(d));
	d[0][0] = 0;
	q[tt++] = (PII){0, 0};

	int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

	while (hh < tt) {
        PII t = q[hh++];
        for (int i = 0; i < 4; i++) {
            int x = t.x + dx[i];
            int y = t.y + dy[i];

            // 判断：在地图内 + 可走 + 未访问
            if (x >= 0 && x < MAX_ROW && y >= 0 && y < MAX_COL && maze[x][y] == 0 && d[x][y] == -1) {
                // 更新距离
                d[x][y] = d[t.x][t.y] + 1;
                // 记录前驱节点
                prev[x][y] = t;
                // 新节点入队
                q[tt++] = (PII){x, y};
            }
        }
    }

	return d[MAX_ROW - 1][MAX_COL - 1];
}


int main(void)
{
    int dist = dsf();

    if (dist == -1) {
        printf("No path!\n");
        return 0;
    }

    // 回溯路径：从终点倒推回起点
    PII path[N * N];
    int path_len = 0;

    // 从终点开始
    PII cur = (PII){MAX_ROW - 1, MAX_COL - 1};
    while (cur.x != 0 || cur.y != 0) {
        path[path_len++] = cur;
        cur = prev[cur.x][cur.y];
    }
    // 添加起点
    path[path_len++] = (PII){0, 0};

    // 输出路径（从终点到起点）
    for (int i = 0; i < path_len; i++) {
        printf("(%d, %d)\n", path[i].x, path[i].y);
    }

    return 0;
}