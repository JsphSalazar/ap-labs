/*
REFERENCES:
	https://golang.org/pkg/path/filepath/#Walk
	https://golang.org/pkg/os/#Lstat
	https://golang.org/src/os/os_windows_test.go?m=text
	https://golang.org/src/os/os_test.go?m=text
	https://stackoverflow.com/questions/18062026/resolve-symlinks-in-go
*/

package main

import(
	"fmt"
	"os"
	"path/filepath"
) 

var directories int = 0
var symbolic int = 0
var others int = 0

func seek(dir string, fi os.FileInfo, err error) error {
	if fi.Mode()&os.ModeSymlink != 0 {
		symbolic++
		return nil;
	}
	if fi.IsDir() {
		directories++
		return nil;
	}
	if fi.Mode().IsRegular() {
		others++
		return nil;
	}
	return nil
}

// scanDir stands for the directory scanning implementation
func scanDir(dir string) error {
	err := filepath.Walk(dir, seek);
	return err
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>")
		os.Exit(1)
	}

	scanDir(os.Args[1])
	fmt.Printf("Path\t%s\n" + 
				"Directories:\t%d\n" +
				"Symbolic Links:\t%d\n" +
				"Other Files:\t%d\n",
				os.Args[1], 
				directories, 
				symbolic,
				others)
}