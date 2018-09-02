package main

import (
	"sync"
)

type Stats struct {
	someStat  uint64
	otherStat uint64

	sync.Mutex
}

func updateSharedObject(obj *Stats) {
	obj.Lock()
	defer obj.Unlock()

	obj.someStat++
	obj.otherStat = obj.someStat / 2
}
