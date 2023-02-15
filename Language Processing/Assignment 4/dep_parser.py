from nltk.parse.corenlp import CoreNLPDependencyParser
import requests


# Function: get_dependency_parse(input)
# This function accepts a raw string input and returns a CoNLL-formatted output
# string with each line indicating a word, its POS tag, the index of its head
# word, and its relation to the head word.
# Parameters:
# input - A string containing a single text input (e.g., a sentence).
# Returns:
# output - A string containing one row per word, with each row containing the
#          word, its POS tag, the index of its head word, and its relation to
#          the head word.
def get_dependency_parse(input: str):
    # Make sure your server is running!  Otherwise this line will not work.
    dep_parser = CoreNLPDependencyParser(url="http://localhost:9000")

    iter = dep_parser.raw_parse(input)
    
    return next(iter).to_conll(4)


def main():
    output = get_dependency_parse("I love NLP!")
    print(output)



################ Do not make any changes below this line ################
if __name__ == '__main__':
    main()
