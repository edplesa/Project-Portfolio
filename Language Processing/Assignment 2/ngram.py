import re

# Function to split a piece of text into sentences
# Arguments:
# text: A string containing input text
# Returns: sents (list)
# Where, sents (list) is a list of sentences that the text is split into
def get_sents(text):
	sents = re.split("[\n\.!?]", text)
	sents = list(filter(len, [s.strip() for s in sents]))
	return sents


# Function to split a sentence into a list of words
# Arguments:
# sent: A string containing input sentence
# Returns: words (list)
# Where, words (list) is a list of words that the sentence is split into
def get_words(sent):
	words = re.split(r"[^A-Za-z0-9-]", sent)
	words = list(filter(len, words))
	return words


# Function to get unigram counts
# Arguments:
# text: A string containing input text (may have multiple sentences)
# Returns: unigrams (dict)
# Where, unigrams (dict) is a python dictionary countaining lower case unigrams (words) as keys and counts as values
def get_unigram_counts(text):
	dict = {}
	sents = get_sents(text)

	for sent in sents:
		words = get_words(sent)
		for word in words:
			word = word.lower()
			if dict.get(word) == None:
				dict.setdefault(word,1)
			else:
				dict[word] += 1

	return dict


# Function to get bigram counts
# Arguments:
# text: A string containing input text (may have multiple sentences)
# Returns: bigrams (dict)
# Where, unigrams (dict) is a python dictionary countaining lower case bigrams as keys and counts as values.
def get_bigram_counts(text):
	dict = {}
	sents = get_sents(text)

	for sent in sents:
		words = get_words(sent)
		for i in range(len(words)-1):
			bigram = words[i].lower() + '_' + words[i+1].lower()
			if dict.get(bigram) == None:
				dict.setdefault(bigram,1)
			else:
				dict[bigram] += 1

	return dict


def main():

	f1 = open('A Room with a View by E. M. Forster.txt', 'r', encoding='utf-8')
	f2 = open('Middlemarch by George Eliot.txt', 'r', encoding='utf-8')

	text1 = f1.read()
	text2 = f2.read()

	f1.close()
	f2.close()

	with open("A Room unigrams.txt", "w") as text_file:
		d = get_unigram_counts(text1)
		sorted_d = dict(sorted(d.items(),key=lambda item: item[1],reverse=True)) #Sort dict by values in descending order

		text_file.write(str(sorted_d))

	with open("A Room bigrams.txt", "w") as text_file:
		d = get_bigram_counts(text1)
		sorted_d = dict(sorted(d.items(), key=lambda item: item[1], reverse=True)) #Sort dict by values in descending order

		text_file.write(str(sorted_d))

	with open("Middlemarch unigrams.txt", "w") as text_file:
		d = get_unigram_counts(text2)
		sorted_d = dict(sorted(d.items(), key=lambda item: item[1], reverse=True)) #Sort dict by values in descending order

		text_file.write(str(sorted_d))

	with open("Middlemarch bigrams.txt", "w") as text_file:
		d = get_bigram_counts(text2)
		sorted_d = dict(sorted(d.items(), key=lambda item: item[1], reverse=True)) #Sort dict by values in descending order

		text_file.write(str(sorted_d))


	return 0


################ Do not make any changes below this line ################
if __name__ == '__main__':
	exit(main())
