package stack

import "fmt"

const MaxSize = 100

type SMarkType uint8

// 定义一个存符号的栈
type SqMarkStack struct {
	data [MaxSize]SMarkType
	top  int // 指向存储数据的位置(没有数据为-1)
}

// 创建一个新栈
func NewMarkStack() *SqMarkStack {
	return &SqMarkStack{
		top: -1,
	}
}

// 判断栈是否为空
func (s SqMarkStack) MarkIsEmpty() bool {
	if s.top == -1 {
		return true
	}

	return false
}

// 置为空栈
func (s *SqMarkStack) ClearMarkStack() bool {
	s.top = -1
	return true
}

// 返回栈的元素个数,即栈的长度
func (s SqMarkStack) MarkStackLength() int {
	return s.top + 1
}

// 若栈不空,则返回S的栈顶元素
func (s SqMarkStack) GetMarkTop() (uint8, bool) {
	if s.top == -1 {
		return 0, false
	}

	return uint8(s.data[s.top]), true
}

// 插入元素e为新的栈顶元素
func (s *SqMarkStack) MarkPush(e uint8) bool {
	if s.top == MaxSize-1 {
		return false
	}

	s.top++
	s.data[s.top] = SMarkType(e)

	return true
}

// 若栈不空,则删除s的栈顶元素,用e返回值
func (s *SqMarkStack) MarkPop() (uint8, bool) {
	if s.top == -1 {
		return 0, false
	}

	var e uint8
	e = uint8(s.data[s.top])
	s.top--

	return e, true
}

// 遍历栈的元素
func (s SqMarkStack) MarkStackTraverse() bool {
	if s.top == -1 {
		return false
	}

	var i = 0

	for i <= s.top {
		visit(s.data[i])
		i++
	}
	fmt.Println()

	return true
}

func visit(e SMarkType) {
	fmt.Printf("%v ", e)
}