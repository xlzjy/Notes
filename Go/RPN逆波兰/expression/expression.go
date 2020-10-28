package expression

import (
	"project/RPN逆波兰/stack"
	"strconv"
)

// 1*2-(3/4)*5+6
func GenerateBackExpression(s *stack.SqMarkStack, inputs []interface{}) []string {
	// 将后缀表达式放在字符串里,通过拼接获取表达式
	var result []string

	// 数据分为两类: uint8符号, float32数字
	for _, v := range inputs {
		switch v.(type) {
		case uint8: // 符号
			res := v.(uint8)
			switch res {
			case '+', '-': // + - 符号是优先级最低的,故会弹出当前栈中所有元素,并将此元素入栈
				res := v.(uint8)
				// 1.判断栈是否为空,若栈为空,则直接将当前元素压入栈,若栈不空,则继续比较
				// 2.循环获取栈顶元素,检查栈顶元素,分为三种情况
				// 2.1如果是 "(" ,那就停止
				// 2.2如果是 "*" "/", 那就弹出
				// 2.3如果是 "+" "-", 那也弹出
				// 2.4每次都要评判当前栈是否为空,如果为空,则暂停循环
				if !s.MarkIsEmpty() {
					for {
						top, _ := s.GetMarkTop()
						if top == '(' {
							break
						} else if top == '*' || top == '/' || top == '+' || top == '-' {
							resInner, _ := s.MarkPop()
							result = append(result, string(resInner))
							if s.MarkIsEmpty() {
								break
							}
						}
					}
				}
				s.MarkPush(res)
			case '*', '/': // * / 符号是除了括号以外的优先级最高的,如果碰到 * / 就弹出,碰到+ -则不管
				res := v.(uint8)
				// 1.判断栈是否为空,若栈为空,则直接将当前元素压入栈,若栈不空,则继续比较
				// 2.循环获取栈顶元素,检查栈顶元素,分为三种情况
				// 2.1如果是 "(" ,那就停止
				// 2.2如果是 "*" "/", 那就弹出
				// 2.3如果是 "+" "-", 不管
				// 2.4每次都要评判当前栈是否为空,如果为空,则暂停循环
				if !s.MarkIsEmpty() {
					for {
						top, _ := s.GetMarkTop()
						if top == '(' {
							break
						} else if top == '*' || top == '/' {
							resInner, _ := s.MarkPop()
							result = append(result, string(resInner))
							if s.MarkIsEmpty() {
								break
							}
						} else { // 遇到 + -
							break
						}
					}
				}
				s.MarkPush(res)
			case ')':
				for {
					top, _ := s.GetMarkTop()
					if top != '(' {
						res, _ := s.MarkPop()
						result = append(result, string(res))
					} else {
						s.MarkPop()
						break
					}
				}
			case '(':
				s.MarkPush('(')
			}
		case float32:
			res := v.(float32)
			result = append(result, strconv.FormatFloat(float64(res), 'f', -1, 32))
		}
	}

	// 最后检查栈是否为空,如果不为空,将内部元素逐个弹出
	for {
		if s.MarkIsEmpty() {
			break
		} else {
			top, _ := s.MarkPop()
			result = append(result, string(top))
		}
	}

	return result
}