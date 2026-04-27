/*
	Napisati funkciju koja proverava da li je zadati broj manji, ve¢i ili jednak nuli i
	ispisati rezultat na konzoli
	▶ Koriste¢i if-else
	▶ Koriste¢i switch-case
*/

package main

import (
	"fmt"
)

func main(){

	var num int

	fmt.Println("Napisi broj: ")
	fmt.Scanln(&num)
	
	fmt.Println("\n")

	if num>0{
		fmt.Println("broj je veci od 0")
	}else if num<0{
		fmt.Println("broj je manji od 0")
	}else{
		fmt.Println("broj je 0")
	}

	fmt.Println("\n")

	switch {
	case num>0: fmt.Println("broj je veci od 0")
	case num<0: fmt.Println("broj je manji od 0")
	default: fmt.Println("broj je 0")
	}

}

