package factorial

import (
	"bufio"
	"fmt"
	"math/big"
	"os"
	"strconv"
)

func factorial(x *big.Int) *big.Int {
	n := big.NewInt(1)

	if x.Cmp(big.NewInt(0)) == 0 {
		return n
	}

	return n.Mul(x, factorial(n.Sub(x, n)))
}

func runFactorialProg() {
	scanner := bufio.NewScanner(os.Stdin)
	fmt.Println("Enter a number to find it's factorial, or any characater to exit.")
	for scanner.Scan() {
		intVal, err := strconv.Atoi(scanner.Text())

		x := big.NewInt(int64(intVal))

		if err == nil {
			fmt.Println("Factorial of", x, "is:", factorial(x), "\n")
		} else {
			break
		}

		fmt.Println("Enter a number to find it's factorial, or any character to exit.")
	}
}
