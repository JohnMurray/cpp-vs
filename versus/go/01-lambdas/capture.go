package main

func addX(x int) func(int) int {
	return func(n int) int {
		return n + x
	}
}

func main() {
	addFive := addX(5)

	addFive(10)
	// returns 15
}
