package telephoneDirectory

import (
	"bufio"
	"os"
	"strings"
)

type Directory struct {
	First, Last, Telephone string
}

func initDir(Directories *[]Directory) {
	file, err := os.Open("directories.txt")

	if err == nil {
		defer file.Close()

		scanner := bufio.NewScanner(file)
		var line string

		for scanner.Scan() {
			line = scanner.Text()

			parsedLine := strings.Fields(line)

			directory := new(Directory)
			directory.First = parsedLine[0]
			directory.Last = parsedLine[1]
			directory.Telephone = parsedLine[2]

			*Directories = append(*Directories, *directory)
		}
	}

}

/*func AddEntry(firstName, lastName, telephoneNumber string) error {

}

func RemoveEntry(firstName, lastName string) error {

}*/
