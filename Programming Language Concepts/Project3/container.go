package main

import "fmt"

/*
	Author: Edward Plesa
	Fall 2021
	Project 3: Containers and Interfaces in Go
*/

type Container interface {
	begin() Iterator
	append(v interface{})
}

type Iterator interface {
	Next() Iterator
	IsEnd() bool
	Deref() interface{}
}

type Vector struct {
	arr  []interface{}
	size int
}

type VectorIterator struct {
	index int
	size  int
	arr   []interface{}
}

type Node struct {
	elem interface{}
	next *Node
}

type List struct {
	head *Node
	size int
}

type ListIterator struct {
	headRef *Node
}

func (list *List) append(v interface{}) {
	newNode := Node{}
	newNode.elem = v

	if list.size == 0 {
		list.head = &newNode
		list.size += 1
	} else {
		cur := list.head
		for i := 0; i < list.size; i++ {
			if cur.next == nil {
				cur.next = &newNode
				list.size += 1
				return
			}
			cur = cur.next
		}
	}
}

func (vec *Vector) append(v interface{}) {
	vec.arr = append(vec.arr, v)
	vec.size += 1
}

func (vec *Vector) begin() Iterator {
	return &VectorIterator{index: 0, size: vec.size, arr: vec.arr}
}

func (vecIter *VectorIterator) Next() Iterator {
	if vecIter.index < len(vecIter.arr) {
		vecIter.index += 1
		return vecIter
	}
	return nil
}

func (vecIter *VectorIterator) IsEnd() bool {
	if vecIter.index < len(vecIter.arr) {
		return false
	}
	return true
}

func (vecIter *VectorIterator) Deref() interface{} {
	return vecIter.arr[vecIter.index]
}

func (list *List) begin() Iterator {
	return &ListIterator{headRef: list.head}
}

func (listIter *ListIterator) Next() Iterator {
	if listIter.headRef != nil {
		listIter.headRef = listIter.headRef.next
		return listIter
	}
	return nil
}

func (listIter *ListIterator) IsEnd() bool {
	if listIter.headRef == nil {
		return true
	}
	return false
}

func (listIter *ListIterator) Deref() interface{} {
	return listIter.headRef.elem
}

func SumInt(c Container) int {
	sum := 0
	it := c.begin()

	for !it.IsEnd() {
		val, good := it.Deref().(int)
		if good {
			sum += val
		}
		it.Next()
	}

	return sum
}

func SumFloat64(c Container) float64 {
	sum := 0.0
	it := c.begin()

	for !it.IsEnd() {
		val, good := it.Deref().(float64)
		if good {
			sum += val
		}
		it.Next()
	}

	return sum
}

func vecTest() {
	myList := Vector{}
	myList.append(1)
	myList.append(2.1)
	myList.append(3)
	myList.append("Random string")
	myList.append(4.1)
	myList.append(5)
	myList.append(6.1)

	fmt.Println("vectTest SumInt returned:", SumInt(&myList))         // should return 1+3+5 = 9
	fmt.Println("vectTest SumFloat64 returned:", SumFloat64(&myList)) // should return 2.1+4.1+6.1 = 12.3
}

func listTest() {
	myList := List{}
	myList.append(1)
	myList.append(2.1)
	myList.append(3)
	myList.append("Random string")
	myList.append(4.1)
	myList.append(5)
	myList.append(6.1)

	fmt.Println("listTest SumInt returned:", SumInt(&myList))         // should return 1+3+5 = 9
	fmt.Println("listTest SumFloat64 returned:", SumFloat64(&myList)) // should return 2.1+4.1+6.1 = 12.3
}

func main() {
	vecTest()
	fmt.Println()
	listTest()
}
