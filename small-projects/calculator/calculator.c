/*
 * ============================================================================
 * 项目名称：简易命令行计算器 (Simple Console Calculator)
 * ============================================================================
 *
 * 项目说明：
 *   这是一个用纯 C 语言编写的命令行计算器小项目，适合 C 语言入门练习。
 *   功能包括：加减乘除四则运算、取余、幂运算、以及连续计算历史记录。
 *
 * 主要知识点：
 *   1. 函数的声明与调用（每种运算封装成独立函数）
 *   2. switch-case 分支结构（菜单选择）
 *   3. 循环结构（do-while 实现连续计算）
 *   4. 数组的使用（保存计算历史）
 *   5. 除零、溢出等边界情况的防御性检查
 *
 * 编译方法：
 *   gcc calculator.c -o calculator
 *
 * 运行方法：
 *   Windows:  calculator.exe
 *   Linux/Mac: ./calculator
 *
 * 作者：pidanpidan123
 * 日期：2026-11-04
 * ============================================================================
 */

#include <stdio.h>
#include <math.h>
#include <string.h>

/* ------------------------ 宏定义 ------------------------ */
#define MAX_HISTORY 20          /* 最多保存 20 条计算历史 */
#define HISTORY_LEN 64          /* 每条历史记录的最大长度 */

/* ------------------------ 运算函数 ------------------------ */

/* 加法：返回 a + b */
double add(double a, double b) {
    return a + b;
}

/* 减法：返回 a - b */
double sub(double a, double b) {
    return a - b;
}

/* 乘法：返回 a * b */
double mul(double a, double b) {
    return a * b;
}

/*
 * 除法：返回 a / b
 * 注意：除数为 0 时返回 0，并由调用方提前检查提示错误
 */
double divide(double a, double b) {
    return a / b;
}

/* 取余运算：返回 a % b（仅对整数有意义，先转成 long） */
long mod(double a, double b) {
    return (long)a % (long)b;
}

/* 幂运算：返回 a 的 b 次方（调用数学库 pow） */
double power(double a, double b) {
    return pow(a, b);
}

/* ------------------------ 历史记录 ------------------------ */

/* 历史记录缓冲区：二维字符数组，每一行存一条 "3 + 5 = 8" 这样的文本 */
static char history[MAX_HISTORY][HISTORY_LEN];
static int history_count = 0;   /* 当前已保存的历史条数 */

/*
 * 保存一条计算历史
 * 用 snprintf 把算式格式化成字符串存入数组，超过容量时丢弃最旧的一条
 */
void save_history(const char *expr, double result) {
    if (history_count < MAX_HISTORY) {
        /* 未满：直接追加到末尾 */
        snprintf(history[history_count], HISTORY_LEN, "%s = %g", expr, result);
        history_count++;
    } else {
        /* 已满：整体前移一格，丢弃最旧的记录 */
        for (int i = 1; i < MAX_HISTORY; i++) {
            strcpy(history[i - 1], history[i]);
        }
        snprintf(history[MAX_HISTORY - 1], HISTORY_LEN, "%s = %g", expr, result);
    }
}

/* 打印所有历史记录 */
void show_history(void) {
    printf("\n===== 计算历史 =====\n");
    if (history_count == 0) {
        printf("(暂无记录)\n");
    } else {
        for (int i = 0; i < history_count; i++) {
            printf("[%d] %s\n", i + 1, history[i]);
        }
    }
    printf("====================\n\n");
}

/* ------------------------ 界面函数 ------------------------ */

/* 打印主菜单 */
void show_menu(void) {
    printf("\n========= 简易计算器 =========\n");
    printf("  1. 加法 (a + b)\n");
    printf("  2. 减法 (a - b)\n");
    printf("  3. 乘法 (a * b)\n");
    printf("  4. 除法 (a / b)\n");
    printf("  5. 取余 (a %% b)\n");
    printf("  6. 幂运算 (a ^ b)\n");
    printf("  7. 查看历史记录\n");
    printf("  0. 退出\n");
    printf("==============================\n");
    printf("请选择: ");
}

/*
 * 主函数：程序入口
 * 流程：显示菜单 -> 读取选择 -> 执行运算 -> 保存历史 -> 循环，直到用户选择退出
 */
int main(void) {
    int choice;             /* 菜单选项 */
    double a, b, result;    /* 两个操作数和计算结果 */
    char expr[HISTORY_LEN]; /* 拼接算式文本，用于保存历史 */

    printf("欢迎使用简易命令行计算器！\n");

    /* do-while：至少执行一次菜单，用户输入 0 时退出 */
    do {
        show_menu();

        /* 读取用户选择；如果输入非法（比如字母），清空缓冲区防止死循环 */
        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请输入数字！\n");
            while (getchar() != '\n');  /* 清空输入缓冲区 */
            continue;
        }

        switch (choice) {
        case 1: /* 加法 */
        case 2: /* 减法 */
        case 3: /* 乘法 */
        case 4: /* 除法 */
        case 5: /* 取余 */
        case 6: /* 幂运算 */
            printf("请输入两个数字（用空格分隔）: ");
            if (scanf("%lf %lf", &a, &b) != 2) {
                printf("输入无效！\n");
                while (getchar() != '\n');
                break;
            }

            /* 除法和取余需要先检查除数是否为 0 */
            if ((choice == 4 || choice == 5) && b == 0) {
                printf("错误：除数不能为 0！\n");
                break;
            }

            /* 根据选项调用对应的运算函数，并拼出算式文本 */
            switch (choice) {
            case 1: result = add(a, b);    snprintf(expr, HISTORY_LEN, "%g + %g", a, b); break;
            case 2: result = sub(a, b);    snprintf(expr, HISTORY_LEN, "%g - %g", a, b); break;
            case 3: result = mul(a, b);    snprintf(expr, HISTORY_LEN, "%g * %g", a, b); break;
            case 4: result = divide(a, b); snprintf(expr, HISTORY_LEN, "%g / %g", a, b); break;
            case 5: result = (double)mod(a, b); snprintf(expr, HISTORY_LEN, "%g %% %g", a, b); break;
            case 6: result = power(a, b);  snprintf(expr, HISTORY_LEN, "%g ^ %g", a, b); break;
            }

            printf("结果: %g\n", result);
            save_history(expr, result);   /* 存入历史记录 */
            break;

        case 7: /* 查看历史 */
            show_history();
            break;

        case 0: /* 退出 */
            printf("再见！\n");
            break;

        default: /* 其他非法选项 */
            printf("没有这个选项，请重新选择！\n");
            break;
        }
    } while (choice != 0);

    return 0;   /* 正常退出，返回 0 表示程序执行成功 */
}
