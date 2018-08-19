package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	rand.Seed(time.Now().UnixNano())

	nums := make([]int, 4096)
	for i := range nums {
		nums[i] = rand.Intn(100)
	}

	results := make(chan int, 4)

	// divide into 1024 blocks
	from := 0
	to := 1024
	jobs := 0
	for to < len(nums) {
		go func() {
			results <- sum(nums[from:to])
		}()
		from += 1024
		to += 1024
		jobs += 1
	}

	// collect all of the results
	totalSum := 0
	for jobs > 0 {
		totalSum += <-results
		jobs -= 1
	}

	fmt.Printf("Total Sum: %d\n", totalSum)
}

func sum(nums []int) int {
	sum := 0
	for _, n := range nums {
		sum += n
	}
	return sum
}
