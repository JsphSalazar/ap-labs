package main

import (
	"fmt"
	"os"
	"io"
	"log"
	"net"
	"time"
	"bufio"
	"strings"
)

type Clock struct {
	name, host string
}

func (c *Clock) getHour(reader io.Reader, writer io.Writer) {
	scanner := bufio.NewScanner(reader)
	for scanner.Scan() {
		fmt.Fprintf(writer, "%s: %s\n", c.name, scanner.Text())
	}

	if scanner.Err() != nil {
		log.Printf("There's an error with %s: %s", c.name, scanner.Err())
	}
}

func main() {
	if len(os.Args) <= 1 {
		fmt.Fprintln(os.Stderr, "Usage: ./clockWall City=localhost:# [...]")
		os.Exit(1)
	}

	clocks := make([]*Clock, 0)
	inputCities := os.Args[1:]

	for _, input := range inputCities {
		fields := strings.Split(input, "=")
		if len(fields) != 2 {
			fmt.Fprintf(os.Stderr, "The argument is wrong (please use as marked on usage) %s\n", input)
			os.Exit(1)
		}
		clocks = append(clocks, &Clock{fields[0], fields[1]})
	}

	for _, c := range clocks {
		userInput, _ := net.Dial("tcp", c.host)

		defer userInput.Close()
		go c.getHour(userInput, os.Stdout)
	}

	for {
		time.Sleep(time.Minute)
	}
}
