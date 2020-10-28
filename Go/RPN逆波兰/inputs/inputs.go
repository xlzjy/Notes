package inputs

import (
	"fmt"
	"io/ioutil"
	"os"
)

func GetInputs() (s []byte) {
	content, err := ioutil.ReadFile("./test.txt")
	if err != nil {
		fmt.Println("read file failed, err: ", err)
		os.Exit(1)
	}

	s = content
	return
}