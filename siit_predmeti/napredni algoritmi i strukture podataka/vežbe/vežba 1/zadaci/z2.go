/*
Kreirati slice integer-a i iteriranjem uz p omo ¢ for-range p etlje izdvojiti elemente
£ija je vrednost manja o d njihovog indeksa
*/

package main

import(
	"fmt"
)

func main(){
	a := [10]int{6,5,4,3,2,1,9,6}

	fmt.Println(a)

	slice := make([]int, 0, 10)
	iter:=0

	fmt.Println(slice)

	for i,v := range a{
		if v<i{
			slice = append(slice,v)
			// slice[iter+1]=v
			iter += 1
		}
	}

	fmt.Println(slice)

}