// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 241.

// Crawl2 crawls web links starting with the command-line arguments.
//
// This version uses a buffered channel as a counting semaphore
// to limit the number of concurrent calls to links.Extract.
//
// Crawl3 adds support for depth limiting.
//

// REFERENCES:
// GO Programming Language Chapter 5 - findlinks

package main

import (
	"fmt"
	"log"
	"flag"

	"gopl.io/ch5/links"
)

//!+sema
// tokens is a counting semaphore used to
// enforce a limit of 20 concurrent requests.
var tokens = make(chan struct{}, 20)
var depth int

func crawl(url string, actualDepth int) []string {
	fmt.Println(url)
	if actualDepth >= depth {
		return nil
	}
	tokens <- struct{}{} // acquire a token
	list, err := links.Extract(url)
	<-tokens // release the token

	if err != nil {
		log.Print(err)
	}
	return list
}

//!-sema

//!+
func main() {
	worklist := make(chan []string)
	var n int // number of pending sends to worklist
	depthCounter := 0

	// Start with the command-line arguments.
	n++
	flag.IntVar(&depth, "depth", 1, "Max crawl depth") //1 as default
	flag.Parse()
	//go func() { worklist <- os.Args[1:] }()
	go func() { worklist <- flag.Args()} ()
	
	// Crawl the web concurrently.
	seen := make(map[string]bool)
	for ; n > 0; n-- {
		list := <-worklist
		for _, link := range list {
			if !seen[link] {
				seen[link] = true
				n++
				go func(link string) {
					depthCounter++
					worklist <- crawl(link, depthCounter)
				}(link)
			}
		}
	}
}

//!-
