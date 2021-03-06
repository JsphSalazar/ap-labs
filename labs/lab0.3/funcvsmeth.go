package main

import (
	"fmt"
)

type Point struct{x, y float64}

func(p Point) X() float64{
	return p.x
}

func(p Point) Y() float64{
	return p.y
}

func(p Point) printPoint(){
	fmt.Printf("%f, %f", p.X(), p.Y())
}

func main(){
	point := Point{1.5, 0.3}
	point.printPoint()
}