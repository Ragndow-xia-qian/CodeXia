# CodeXia

## 项目介绍

此项目用C++来实现一个编程语言

代码后缀名需要为cdx文件

## 示例代码

下面是一个打印helloworld的程序，`main.cdx`

```markdown
$
 HelloWorld程序
 非常的简单
$

@ 定义常量
immutable order Str string = "HelloWorld";

@ 主函数接口
call: interface: [

    @ 打印
    do: println("{}", {Str});

    @ 结束
    done;
]
```

更多具体的介绍请看 `document` 文件夹内的`语法.md`

注: 若在运行main.cc时不传入文件则会进入表达式识别功能，可以输入表达式，程序会输出表达式的结果
