#include <stdio.h>
#include <stdlib.h> //包含rand生成随机数
#include <string.h> //包含strlen统计字符串长度

int main() {
    int registerType;//注册类型
    registerType = rand() % 3 + 1;//生成随机数并通过mod控制在1-3

    char userInput[100]; //简化代码并易于查看输入是否在规定范围内

    printf("Registration type: %d\n", registerType);

    //开始switch-case循环
    switch (registerType) {
    case 1:;//用户名注册（//报C23 Warning,暂且加一个空语句）
        printf("Please enter username (within 10 characters): ");
        scanf("%99s",userInput);//用户输入名字

        //检测是否10字节内
        int len1 = strlen(userInput);
        if (len1 <= 10) {
            printf("Registration Successful\n");
        } else {
            printf("Registration Failed\n");
        }
        break;
    case 2:;//手机注册
        printf("Please enter phone number (11 digits, starts with 13): ");
        scanf("%99s",userInput);//用户输入手机号

        //检测是否全为数字
        for(int i = 0; i <= 10; i++){
            if(userInput[i] !='0' && userInput[i] != '1' && userInput[i] != '2' && userInput[i] != '3' && userInput[i] != '4' && userInput[i]!= '5' && userInput[i] != '6' && userInput[i] != '7' && userInput[i] != '8' && userInput[i] != '9'){
              printf ("Registration Failed\n");
              return 0;
            }
        }
        int len2 = strlen(userInput);
        if (len2 == 11 && userInput[0] == '1' && userInput[1] == '3') {
            printf("Registration Successful\n");
        } else {
            printf("Registration Failed\n");
        }
        break;
    case 3:;//激活码注册
        printf("Please enter serial number (4-digit hexadecimal, starts with A): ");
        scanf("%99s", userInput);

        //检测是否输入为16进制数字
        for(int i = 0; i <= 3; i++){
            if(userInput[i] != '1' && userInput[i] != '2' && userInput[i] != '3' && userInput[i] != '4' && userInput[i] != '5' && userInput[i] != '6' && userInput[i] != '7' && userInput[i] != '8' && userInput[i] != '9' && userInput[i] != 'A' && userInput[i] != 'B' && userInput[i] != 'C' && userInput[i] != 'D' && userInput[i] != 'E' && userInput[i] != 'F' && userInput[i] != 'G'){
                printf("Registration Failed\n");
                return 0;
            }
        }
        
        int len3 = strlen(userInput);//计算长度
        if (len3 == 4 && (userInput[0] == 'A')) {
            printf("Registration Successful\n");
        } else {
            printf("Registration Failed\n");
        }
        break;
    }        
    return 0;
}
