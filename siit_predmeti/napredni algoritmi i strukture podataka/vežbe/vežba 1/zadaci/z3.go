/*
Napisati funkciju koja za zadati ulaz n vra¢a n-ti prost broj. Druga p ovratna
vrednost funkcije treba da bude indikator gre²ke. Pravilno obraditi slu£aj kada je
vrednost argumenta funkcije manja o d 1. (Vi²e o radu sa gre²kama)
*/

package main

import (
	"fmt"
	"math"
)

func is_prime (n int) bool {
	if n<=1{
		return false
	} 
	if n<=3 {
		return true
	} 
	if n%2==0 {
		return false
	}
	if n%3==0 {
		return false;
	}

	var i int = 0;
	var sqrt float64 = math.Sqrt(float64(n))
    
	for i=5;i<=int(sqrt);i+=2{
		if (n%i==0){
			return false
		}
	}
	return true

}

func nadji_prosti (n int) int {
	var x int = 0
	var i int = 0

	for i<n {
		x++
		if is_prime(x){
			i++
		}
	}
	return x
}

func main(){

	var n int = 0;

	fmt.Println("unesi redni broj prostog broja: ")
	fmt.Scanln(&n)

	fmt.Println("\nProsti broj na toj poziciji je ", nadji_prosti(n))

}