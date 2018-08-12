package main

func main() {
	addOne := func(x int) int {
		return x + 1
	}

	addOne(5)
	// returns 6

	// use lambda as a value
	v := []int{1, 2, 3, 4, 5}
	apply([]int{1, 2, 3, 4, 5}, addOne)
	// new value of 'v' is [2, 3, 4, 5, 6]
}
