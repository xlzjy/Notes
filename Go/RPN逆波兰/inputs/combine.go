package inputs

import (
	"strings"
)

// 切片是引用传递
func Combine(s []byte) []interface{} {
	// 去除所有空格、换行符、制表符
	s = []byte(strings.Replace(string(s), " ", "", -1))
	s = []byte(strings.Replace(string(s), "\n", "", -1))
	s = []byte(strings.Replace(string(s), "\t", "", -1))
	var data []interface{}
	var flag = false
	var count = 0
	l := len(s)

	// (10.21+21.387)/33.32189-45.41*56.412+68.41/79.8392
	// 1.23 * (2.34 - 34.5) / 456 + 0.1
	// 1 * (2 - 1.1)/3.12
	// 数字拼接
	for i := 0; i < l; i++ {
		// 如果是数字或者小数点
		if (s[i] >= '0' && s[i] <= '9') || s[i] == '.' {
			flag = true
			count++
		} else
		{
			// 前面有数字
			if flag {
				var dot = false
				var dotpos = -1
				var temp float32 = 0.0
				// 如果有.那就找到.所在位置
				for t := count; t > 0; t-- {
					if s[i-t] == '.' {
						dot = true
						dotpos = t
					}
				}

				// 有.的情况
				if dot {
					// 分成两半解决,此时s[i-dotpos]就是.的位置
					// 左边为整数值,范围在 i-count <=x < i-dotpos
					// 右边为小数值,范围在 i-dotpos < x < i
					for left := i - count; left < i-dotpos; left++ {
						temp += float32(s[left]-'0') * float32(multiple(count-dotpos-1))
						count--
					}
					count-- // 除去.
					// 剩下的count用于除法
					for right := 1; right <= count; right++ {
						temp += float32(s[i-dotpos+right]-'0') * float32(divide(right))
					}
					dot = false
					count = 0
				} else {
					// 无点的情况
					for count > 0 {
						temp += float32(s[i-count]-'0') * float32(multiple(count-1))
						count--
					}
				}

				flag = false
				data = append(data, temp)
				data = append(data, s[i]) // 当前符号
			} else
			{
				// 前面没有数字和小数点
				data = append(data, s[i])
			}
		}
	}

	// 对于最后一个数字,count = 数字长度+标点
	for count > 0 {
		var lastTemp float32 = 0.0
		var lastPos = 0
		var find = false
		// 1.寻找.
		for i := 0; i < count-1; i++ {
			if s[l-1-i] == '.' {
				lastPos = l - 1 - i
				find = true
			}
		}

		if find {
			// 分成.前和.后
			// .前: l-count <= t < lastPos
			// .后: lastPos < t <= l-1
			var tt = 0
			for left := l - count; left < lastPos; left++ {
				lastTemp += float32(s[left]-'0') * float32(multiple(lastPos-1-left))
				tt++
			}
			count = count - tt - 1

			tt = 1
			for right := lastPos + 1; right <= l-1; right++ {
				lastTemp += float32(s[right]-'0') * float32(divide(tt))
				tt++
			}
		} else { // 没有小数点
			for left := l - count; left <= l-1; left++ {
				lastTemp += float32(s[left]-'0') * float32(multiple(count-1))
				count--
			}
		}
		count = 0
		data = append(data, lastTemp)
	}

	return data
}

func multiple(count int) float32 {
	var time float32 = 1
	for i := 0; i < count; i++ {
		time *= 10
	}

	return time
}

func divide(count int) float32 {
	var divi float32 = 1
	for i := 0; i < count; i++ {
		divi /= 10
	}

	return divi
}