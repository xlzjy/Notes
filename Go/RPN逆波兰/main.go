package main

import (
	"fmt"
	"project/RPN逆波兰/calculate"
	"project/RPN逆波兰/expression"
	"project/RPN逆波兰/inputs"
	"project/RPN逆波兰/stack"
)

func main() {
	// 获取用户输入
	s := inputs.GetInputs()

	// 拼接数字,过滤掉空格
	var sHandle = inputs.Combine(s)

	// 根据用户输入的中缀表达式生成后缀表达式
	var markstack = stack.NewMarkStack()
	backExpression := expression.GenerateBackExpression(markstack, sHandle)
	fmt.Printf("后缀表达式为类型为: %T, 表达式为: %s\n", backExpression, backExpression)

	// 后缀表达式计算结果
	result := calculate.Calculate(backExpression)
	fmt.Printf("后缀表达式计算结果: %f\n", result)
}