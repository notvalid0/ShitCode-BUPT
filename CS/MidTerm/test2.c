#include <stdio.h>

int main(void) {
    int row; //三角形层数

    //用户输入层数
    printf("Enter the number of rows of the triangle: ");
    scanf("%d", &row);

    // 绘制三角形
    for (int i = 1; i <= row; i++) {//外层for循环控制层数
        int star = 1;
        int blank = 1;
        int k = 10 - i;//空格数量
        while (blank <= k) {//输出空格
            printf(" ");
            blank++;
        }
        while (star <= i) {//输出星星
            printf("*");
            star++;
        }
        printf("\n");//换行
    }

    return 0;//退出程序
}
