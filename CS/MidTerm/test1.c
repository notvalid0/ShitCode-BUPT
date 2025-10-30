#include<stdio.h>

int main(void){
  int num1, num2, num3, sum;//引入三个数字以及sum
  float average; //引入average
  int i = 0;//引入i控制循环次数
  
  do {
    //重置变量
    sum = 0;
    average = 0.0f;
    num1 = num2 = num3 = 0; //可以在此处直接int但是按照题意似乎不可

    printf("plz type 3 integers!\n");//输入提示

    //确保num1 num2 num3成功的输入
    if (scanf("%d %d %d",&num1,&num2,&num3) == 3) {
      sum = num1 + num2 + num3;
      average = sum/3.0;//计算SUM与AVERAGE
      printf("Sum:%d,Average:%.2f\n",sum,average);
      i ++;
    }
    else{
      printf ("Not valid input, Plz redo it!\n");//不计入次数
      while (getchar() != '\n'); // 清空输入缓冲区
    }
  }while (i < 3);
  return 0;//退出程序
}
