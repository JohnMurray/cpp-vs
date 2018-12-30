package main

import (
	"fmt"
	"math/rand"
)

func sendEmail(to string, from string, subject string,
               message string,
               successCb func(string),
               failureCb func(string)) {
	if rand.Float32() >= 0.5 {
		successCb(to)
	} else {
		failureCb(to)
	}
}

func main() {
	sendEmail("you@your_domain.com", "me@my_domain.com",
		"Very Important Email",
		"TODO: remember to write email body. :-D",
		func(to string) {
			fmt.Printf("Successful email sent to: %s\n", to)
		},
		func(to string) {
			fmt.Printf(
				"OH NO! Very important email not sent to %s\n",
				to)
		})

}
