#include <stdio.h>
#include <stdlib.h>

#define N 4
#define INF 10000

// 四个方向：上、下、左、右
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point pt;
    int dist;
} QueueNode;

typedef struct {
    QueueNode* data;
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->data = (QueueNode*)malloc(N * N * sizeof(QueueNode));
    q->front = q->rear = 0;
}

int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void enqueue(Queue* q, QueueNode node) {
    q->data[q->rear++] = node;
}

QueueNode dequeue(Queue* q) {
    return q->data[q->front++];
}

int isValid(int x, int y, int grid[N][N], int visited[N][N]) {
    return x >= 0 && x < N && y >= 0 && y < N && grid[x][y] != 1 && !visited[x][y];
}

// 用于记录每个点的前驱
int bfs(int grid[N][N], Point start, Point end, int prev[N][N]) {
    int visited[N][N] = {0};
    Queue q;
    initQueue(&q);
    enqueue(&q, (QueueNode){start, 0});
    visited[start.x][start.y] = 1;

    while (!isEmpty(&q)) {
        QueueNode current = dequeue(&q);

        // 如果到达终点，跳出循环
        if (current.pt.x == end.x && current.pt.y == end.y) {
            return current.dist;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current.pt.x + dx[i];
            int newY = current.pt.y + dy[i];
            if (isValid(newX, newY, grid, visited)) {
                visited[newX][newY] = 1;
                prev[newX][newY] = current.pt.x * N + current.pt.y; // 存储当前点的前驱节点
                enqueue(&q, (QueueNode){{newX, newY}, current.dist + 1});
            }
        }
    }
    return -1; // 如果没有找到路径
}

// 回溯路径并存储到数组
int printPath(Point start, Point end, int prev[N][N], Point path[N * N]) {
    int pathLen = 0;
    int x = end.x, y = end.y;

    // 回溯路径
    while (x != start.x || y != start.y) {
        path[pathLen++] = (Point){x, y};
        int prevIndex = prev[x][y];
        x = prevIndex / N;
        y = prevIndex % N;
    }
    path[pathLen++] = start; // 添加起点

    // 逆序打印路径
    for (int i = pathLen - 1; i >= 0; i--) {
        if (i == pathLen - 1)
            printf("(%d, %d)", path[i].x, path[i].y);
        else
            printf(" -> (%d, %d)", path[i].x, path[i].y);
    }
    printf("\n");

    return pathLen;
}

int main() {
    int grid[N][N] = {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 1},
            {0, 0, 0, 0}
    };

    Point start = {0, 0};
    Point end = {3, 3};

    int prev[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            prev[i][j] = -1; // 初始化前驱数组
        }
    }

    int result = bfs(grid, start, end, prev);

    if (result == -1) {
        printf("no path\n");
    } else {
        Point path[N * N];
        int pathLen = printPath(start, end, prev, path);
        printf("path length: %d\n", pathLen);
    }

    return 0;
}
