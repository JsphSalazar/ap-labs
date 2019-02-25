package main

import(
	"io"
	"fmt"
	"bufio"
	"log"
	"net"
	"os"
	"strings"
	"time"
)

type clock struct{
	name, host string
}

func (c *clock) watch(w io.Writer, r io.Reader) {
	s := bufio.NewScanner(r)
	for s.Scan() {
		fmt.Printf(w,"%s: %s\n", c.name, s.Text())
	}
	fmt.Println(c.name, "Done")
	if s.Err() != nil {
		log.Printf("Can not read from %s: %s")
	}
}