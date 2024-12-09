#include <stdio.h>
#include <stdlib.h>

#define N 4
#define INF 10000
int ob_x[]={-1,-1,-1,-1,-1,-1,-1};
int ob_y[]={-1,-1,-1,-1,-1,-1,-1};
int ob_count=0;
int Max_count=3;
int final_x=-1;
int final_y=-1;
int count[4][4]={
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}

};
int grid1[N][N] = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 1,0}
};
// 四个方向：上、下、左、右
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int is_valid(int x,int y){
    return x>=0&&x<N&&y>=0&&y<N;
}
void sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // 交换 arr[j] 和 arr[j+1]
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void find_obstacle(int x,int y,int grid[N][N] ){
    printf("current x=%d,y=%d\n",x,y);
    if(ob_count==Max_count){
        final_x=x;
        final_y=y;
        return;
    }
    count[x][y]+=1;
    for (int i = 0; i < N; ++i) {
        int next_x=x+dx[i];
        int next_y=y+dy[i];
        if(is_valid(next_x,next_y)){
            if(grid[next_x][next_y]==1){
                int flag=0;
                for (int j = 0; j < ob_count; ++j) {
                    if(next_x==ob_x[j]&&next_y==ob_y[j]){
                        flag=1;
                    }
                }
                if(flag==1){
                    continue;
                }
                ob_x[ob_count]=next_x;ob_y[ob_count]=next_y;
                ob_count++;
            }
        }
    }
    int up_x=x-1;int up_y=y;
    int down_x=x+1;int down_y=y;
    int left_x=x;int left_y=y-1;
    int right_x=x;int right_y=y+1;
    int up_value = 1000000, down_value = 1000000, left_value = 1000000, right_value = 1000000;
    if(is_valid(up_x,up_y)&&grid[up_x][up_y]!=1){
        up_value=count[up_x][up_y];
    }
    if(is_valid(down_x,down_y)&&grid[down_x][down_y]!=1){
        down_value=count[down_x][down_y];
    }
    if(is_valid(left_x,left_y)&&grid[left_x][left_y]!=1){
        left_value=count[left_x][left_y];
    }
    if(is_valid(right_x,right_y)&&grid[right_x][right_y]!=1){
        right_value=count[right_x][right_y];
    }
    int arr[4]={up_value,right_value,down_value,left_value};
    int min=200000000;
    int ss=5;
    for (int i = 0; i < 4; ++i) {
        if(arr[i]<min){
            ss=i;
            min=arr[i];
        }
    }
    if(ss==0){
        find_obstacle(up_x,up_y,grid1);
    }
    else if(ss==1){
        find_obstacle(right_x,right_y,grid1);
    }
    else if(ss==2){
        find_obstacle(down_x,down_y,grid1);
    }
    else if(ss==3){
        find_obstacle(left_x,left_y,grid1);
    }


}
int main(){
    int obstacle_count=6;

    int start_x=3; int start_y=0;
    find_obstacle(start_x,start_y,grid1);
    for (int i = 0; i <Max_count; ++i) {
        printf("obstacle find at x=%d,y=%d\n",ob_x[i],ob_y[i]);
    }
    printf("final point: x=%d,y=%d\n",final_x,final_y);
    return 0;
}
