package stack

import "fmt"

const OperMaxSize = 100

type SOperType float32

// 定义一个存操作数的栈
type SqOperStack struct {
	data [OperMaxSize]SOperType
	top  int // 指向存储数据的位置(没有数据为-1)
}

// 创建一个新栈
func NewOperStack() *SqOperStack {
	return &SqOperStack{
		top: -1,
	}
}

// 判断栈是否为空
func (s SqOperStack) OperIsEmpty() bool {
	if s.top == -1 {
		return true
	}

	return false
}

// 置为空栈
func (s *SqOperStack) ClearOperStack() bool {
	s.top = -1
	return true
}

// 返回栈的元素个数,即栈的长度
func (s SqOperStack) OperStackLength() int {
	return s.top + 1
}

// 若栈不空,则返回S的栈顶元素
func (s SqOperStack) GetOperTop() (float32, bool) {
	if s.top == -1 {
		return 0, false
	}

	return float32(s.data[s.top]), true
}

// 插入元素e为新的栈顶元素
func (s *SqOperStack) OperPush(e float32) bool {
	if s.top == MaxSize-1 {
		return false
	}

	s.top++
	s.data[s.top] = SOperType(e)

	return true
}

// 若栈不空,则删除s的栈顶元素,用e返回值
func (s *SqOperStack) OperPop() (float32, bool) {
	if s.top == -1 {
		return 0, false
	}

	var e float32
	e = float32(s.data[s.top])
	s.top--

	return e, true
}

// 遍历栈的元素
func (s SqOperStack) OperStackTraverse() bool {
	if s.top == -1 {
		return false
	}

	var i = 0

	for i <= s.top {
		visitOper(s.data[i])
		i++
	}
	fmt.Println()

	return true
}

func visitOper(e SOperType) {
	fmt.Printf("%v ", e)
}