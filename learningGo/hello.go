package main

import (
	"fmt"
)

func main() {
	fmt.Println("Hello, world or 你好，世界 or καλημ ́ρα κóσμ or こんにちはせかい\n")

	var a int = 8
	fmt.Printf("a is %d\n", a)

	var c complex64 = 5 + 3i
	fmt.Printf("c is %v\n", c)

	s := "hello"
	h := " world"
	t := s + h
	fmt.Printf("%s\n", t)

	x := 12

	if x > 10 {
		fmt.Println("x is bigger than 10\n")
	} else {
		fmt.Println("x is less than 10\n")
	}

	sum := 0

	for i := 0; i < 10; i++ {
		sum += i
	}
	fmt.Printf("sum is %d\n", sum)

	interger := 6

	switch interger {
	case 4:
		fmt.Println("the interger is <=4")
	case 5:
		fmt.Println("the interger is <=5")
	case 6:
		fmt.Println("the interger is <=6")
	case 7:
		fmt.Println("the interger is <=7")
	case 8:
		fmt.Println("the interger is <=8")
	default:
		fmt.Println("default case")
	}
}

