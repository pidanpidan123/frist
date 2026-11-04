# frist

我的第一个 Git 仓库，用来练习 Git 操作和存放 C 语言小项目。

## 小项目列表

| 项目 | 说明 | 技术点 |
|------|------|--------|
| [简易命令行计算器](small-projects/calculator/) | 加减乘除、取余、幂运算、计算历史 | 函数封装、switch-case、数组、字符串处理 |

## 目录结构

```
frist/
├── README.md                    # 本文件
└── small-projects/              # 小项目合集
    └── calculator/              # 简易命令行计算器
        ├── calculator.c
        └── README.md
```

## 使用方式

```bash
git clone https://github.com/pidanpidan123/frist.git
cd frist/small-projects/calculator
gcc calculator.c -o calculator -lm
./calculator
```

## 更新记录

- 2026-11-04 创建仓库，添加计算器小项目
