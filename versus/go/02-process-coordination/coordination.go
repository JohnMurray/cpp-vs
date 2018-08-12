package main

import (
	"fmt"
	"sync"
)

func main() {
	broadcastRegister := make(chan chan int, 1)
	broadcastIn := make(chan int, 5)
	go channelBroadcaster(broadcastRegister, broadcastIn)

	var wg sync.WaitGroup

	for i, c := range "Hello, World!" {
		workerIn := make(chan int, 20)
		broadcastRegister <- workerIn
		wg.Add(1)
		go coordinatedPrint(i, string(c), workerIn, broadcastIn, &wg)
	}

	broadcastIn <- -1
	wg.Wait()
}

func channelBroadcaster(register chan chan int, in chan int) {
	outs := make([]chan int, 0, 10)
	for {
		select {
		case out := <- register:
			outs = append(outs, out)
		case index := <- in:
			for _, out := range outs {
				out <- index
			}
		}
	}
}

func coordinatedPrint(index int, char string, in chan int,
					  out chan int, wg *sync.WaitGroup) {
	defer wg.Done()
	for {
		prev_i := <- in
		if (index - 1) == prev_i {
			fmt.Print(char)
			out <- index
			break
		}
	}
}