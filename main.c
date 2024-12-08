#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRID_SIZE 4
#define MAX_OBSTACLES 16

// 队列节点
typedef struct {
    int x, y, dist;
} Node;

// 队列实现
typedef struct {
    Node data[GRID_SIZE * GRID_SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = 0;
}

bool isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int x, int y, int dist) {
    q->data[q->rear].x = x;
    q->data[q->rear].y = y;
    q->data[q->rear].dist = dist;
    q->rear++;
}

Node dequeue(Queue *q) {
    return q->data[q->front++];
}

// 检查是否在网格范围内
bool isValid(int x, int y, int grid[GRID_SIZE][GRID_SIZE]) {
    return x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE && grid[x][y] != -1;
}

// 主函数：寻找路径并检测障碍物
int findPath(int grid[GRID_SIZE][GRID_SIZE], int startX, int startY, int endX, int endY) {
    // 方向向量（上下左右）
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // 记录访问过的点
    bool visited[GRID_SIZE][GRID_SIZE] = {false};

    // 障碍物数组
    int obstacles[MAX_OBSTACLES][2];
    int obstacleCount = 0;

    // 初始化队列
    Queue q;
    initQueue(&q);
    enqueue(&q, startX, startY, 0);
    visited[startX][startY] = true;

    int totalDistance = 0;

    while (!isEmpty(&q)) {
        Node node = dequeue(&q);
        int x = node.x;
        int y = node.y;
        int dist = node.dist;

        // 检测障碍物
        if (grid[x][y] == -1) {
            bool alreadyDetected = false;
            for (int i = 0; i < obstacleCount; i++) {
                if (obstacles[i][0] == x && obstacles[i][1] == y) {
                    alreadyDetected = true;
                    break;
                }
            }
            if (!alreadyDetected) {
                obstacles[obstacleCount][0] = x;
                obstacles[obstacleCount][1] = y;
                obstacleCount++;
            }
        }

        // 如果到达终点
        if (x == endX && y == endY) {
            totalDistance = dist;
            break;
        }

        // 扩展下一步
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (isValid(nx, ny, grid) && !visited[nx][ny]) {
                visited[nx][ny] = true;
                enqueue(&q, nx, ny, dist + 1);
            }
        }
    }

    // 输出障碍物信息
    printf("检测到的障碍物数量: %d\n", obstacleCount);
    for (int i = 0; i < obstacleCount; i++) {
        printf("障碍物位置: (%d, %d)\n", obstacles[i][0], obstacles[i][1]);
    }

    return totalDistance;
}

int main() {
    // 初始化网格
    int grid[GRID_SIZE][GRID_SIZE] = {
        {0, 0, 0, 0},
        {0, -1, 0, -1},
        {0, 0, 0, 0},
        {1, 0, 0, 2} // 1 表示起点，2 表示终点
    };

    // 起点和终点
    int startX = 3, startY = 0;
    int endX = 3, endY = 3;

    // 计算路径
    int totalDistance = findPath(grid, startX, startY, endX, endY);
    printf("总移动距离: %d\n", totalDistance);

    return 0;
}
