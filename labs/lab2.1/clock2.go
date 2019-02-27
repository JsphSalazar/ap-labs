package main

import (
	"io"
	"log"
	"net"
	"time"
	"fmt"
	//"flag"
)

//var port = flag.Int("port", 8080, "listen port")

func handleConn(c net.Conn) {
	defer c.Close()
	for {
		_, err := io.WriteString(c, time.Now().Format("15:04:05\n"))
		if err != nil {
			return
		}
		time.Sleep(1 * time.Second)
	}
}

func main() {
	//flag.Parse()
	if len(os.Args) != 3 {
		log.Printf("Usage: clock2.go -port [port]\n");
		return
	}

	if os.Args[1] != "port" {
		log.Printf("2\n");
		return;
	}

	localhost := "localhost" + os.Args[2];
	listener, err := net.Listen("tcp", localhost)
	if err != nil {
		log.Fatal(err)
	}
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}
