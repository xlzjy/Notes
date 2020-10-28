package calculate

import (
	"fmt"
	"os"
	"project/RPN逆波兰/stack"
	"strconv"
)

// 用栈实现后缀表达式的计算:
func Calculate(s []string) float32 {
	// s为字符串切片
	var oprStack = stack.NewOperStack()
	var res float32 = 0
	for _, v := range s { // 1.从左往右扫描下一个元素,直到处理完所有元素
		switch v { // 3.若扫描到运算符, 则弹出两个栈顶元素(先出栈的是右操作数), 执行相应运算, 运算结果压回栈顶, 回到1
		case "+":
			left, right := calc(oprStack)
			res = left + right
			oprStack.OperPush(res)
		case "-":
			left, right := calc(oprStack)
			res = left - right
			oprStack.OperPush(res)
		case "*":
			left, right := calc(oprStack)
			res = left * right
			oprStack.OperPush(res)
		case "/":
			left, right := calc(oprStack)
			res = left / right
			oprStack.OperPush(res)
		default: // 2.若扫描到操作数则压入栈,并回到1, 否则执行3
			res, err := strconv.ParseFloat(v, 32)
			if err != nil {
				fmt.Println("ParseFloat err: ", err)
				os.Exit(1)
			}
			if !oprStack.OperPush(float32(res)) {
				fmt.Println("操作数栈已满")
				os.Exit(1)
			}
		}
	}

	var ok bool
	// 将栈中元素弹出
	res, ok = oprStack.OperPop()
	if !ok {
		fmt.Println("计算错误")
		os.Exit(1)
	}

	return res
}

func calc(operStack *stack.SqOperStack) (float32, float32) {
	// 检查栈中的元素是否>=2个,如果不足两个,操作失败
	if operStack.OperStackLength() < 2 {
		fmt.Println("栈中不足2个元素, 操作失败: ")
		os.Exit(1)
	}

	// 栈中>=2个元素rightOper,先出栈的是右操作数
	rightOper, _ := operStack.OperPop()
	leftOper, _ := operStack.OperPop()
	return leftOper, rightOper
}