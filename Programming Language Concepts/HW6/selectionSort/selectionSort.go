package selectionSort

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func selectionSort(lower int, upper int, arr []int) {
	var slice []int = arr[lower:upper]
	if lower < 0 || lower > len(arr) || upper > len(arr) || upper < 0 {
		fmt.Println("Out of bounds")
		fmt.Println()
	}

	for i := 0; i < len(slice)-1; i++ {
		var min = i
		for j := i; j < len(slice); j++ {
			if slice[j] < slice[min] {
				min = j
			}
		}
		slice[i], slice[min] = slice[min], slice[i]
	}
	fmt.Println(arr)
	fmt.Println()
}

func runSelectionSortProg() {
	numsFromCMD := os.Args[1:]

	var numArray []int

	for i := 0; i < len(numsFromCMD); i++ {
		val, err := strconv.Atoi(numsFromCMD[i])
		if err == nil {
			numArray = append(numArray, val)
		}

	}

	fmt.Println(numArray)
	scanner := bufio.NewScanner(os.Stdin)
	for {
		var low, high int
		fmt.Print("Enter lower bound for slice: ")
		scanner.Scan()
		low, _ = strconv.Atoi(scanner.Text())

		fmt.Print("Enter upper bound for slice: ")
		scanner.Scan()
		high, _ = strconv.Atoi(scanner.Text())

		selectionSort(low, high, numArray)
	}
}
