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

func main() {
	if len(os.Args) == 1 {
		fmt.Fprintln(os.Stderr, "Usage: clockWall NAME=HOST")
		os.Exit(1)
	}
	clocks := make([]*clock, 0)
	for _, a := range os.Args[1:] {
		fields := strings.Split(a, "=")
		if len(fields) != 2 {
			fmt.Fprintf(os.Stderr, "Bad arg: %s\n", a)
			os.Exit(1)
		}
		clocks = append(clocks, &clock{fields[0], fields[1]})
	}
	for _, c := range clocks {
		conn, err := net.Dial("TCP", c.host)
		if err != nil {
			log.Fatal(err)
		}
		defer conn.Close()
		go c.watch(os.Stdout, conn)
	}
	for {
		time.Sleep(time.Minute)
	}
}