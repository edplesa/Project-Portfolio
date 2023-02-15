import re

# Sample function which returns a regex to represent a set of strings containing only the capital letters
# Note that it returns a raw python string (preceded by r) which saves us from the backslash plague
# More details here https://docs.python.org/3.7/howto/regex.html#the-backslash-plague
def capital_letters():
	# ^ signifies the start of string and $ signifies end of string
	# [A-Z] indicates all capital letters
	# [A-Z]+ indicates one or more capital letters
	return r"^[A-Z]+$"


# Q1(a): The set of strings that contain only vowels or only digits, but not both (and no strings may contain non-vowels or non-digits);
# Returns: regex as a valid python string
def vowels_digits():
	return r"^([aeiouAEIOU]+)$|^([0-9]+)$"


# Q1(b): The set of strings containing a person’s name (simplified as First Last in	the context of this assignment), with the following constraints: the last
# name must immediately follow the first name, both parts of the name must consist only of alphabet characters, the first and last name must
# start with capital letters, followed by lowercase letters, and the first and last name must be separated by a single space
#
# Returns: regex as a valid python string
def person_name():
	return r"\bFirst Last\b"


# Q1(c): The set of all English past perfect tense phrases, under the simplifying
# assumption that all past perfect tense phrases are constructed using the
# word “had” followed by a word ending in d or ed with a single space
# between “had” and the following word
#
# Returns: regex as a valid python string
def past_perfect():
	return r"^had [a-zA-Z]+(d|ed)$"


# Q1(d): The set of email addresses formatted as username@domain.com, with the following constraints:
# username can be a string of lowercase letters or digits, starting with a lowercase letter and ending with a digit, of any
# length >= 2, and domain can be either gmail or yahoo;
#
# Returns: regex as a valid python string
def email_address():
	return r"^[a-z][a-z0-9]*[0-9]@(yahoo\.com|gmail\.com)$"


# Q1(e): The set of strings containing only monetary values, formatted as $ followed
# by digits, optionally followed by a decimal point (.) and two more digits
#
# Returns: regex as a valid python string
def monetary_values():
	return r"^\$[0-9]+(|\.[0-9]{2})$"


# Q1(f): The set of all strings matching the valid date (mm/dd/yyyy) where valid month will be only those with 31 days and
# the only valid years will be in the range 2000−2022, including 2000 and 2022
#
# Return: regex as a valid python string
def valid_date():
	return r"^(0[13578]|1[02])/([012][1-9]|3[01])/20([01][0-9]|2[012])$"


# Q1(g): The set of all strings that end with a single full  stop (.), question  mark(?),
# or exclamation mark (!), with the constraint that these punctuation marks are only allowed at the end of the string
#
# Return: regex as a valid python string
def punctuation():
	return r"^[^.?!]*[.?!]$"


# Q1(h): The set of all strings that have the exact words "fall" and "autumn" in them, in any order,
# repeated any number of times
#
# Return: regex as a valid python string
def fall_autumn():
	return r"((^|.*\s+)(fall)(\s+|\s.+\s+)(autumn)($|\s+.*))|((^|.*\s+)(autumn)(\s+|\s.+\s+)(fall)($|\s+.*))"


# Q1(i): The set of all natural numbers, with commas optionally inserted preceding successive groups of three integers (e.g., 1000000 and 1,000,000 are both valid);
#
# Return: regex as a valid python string
#[1-9][0-9]*
def num_commas():
	return r"^[1-9]((\d*)|\d{0,2}(,\d{3})*)$"


# Q1(j): The set of all strings that have an apostrophe (') in them
#
# Return: regex as a valid python string
def apostrophe():
	return r"^.*'.*$"



# Sample code is provided to assist with the assignment,
# feel free to change/remove it. If you want, you may run the code from terminal as:
# python regex.py
# It should produce the following output:
# 		$ python3 regex.py 
# 		Match: HELLOWORLD
# 		No Match: HELLO WORLD

def main():
	# Get the regex from function
	regex = num_commas()

	# Compile the regex
	p = re.compile(regex)

	# Let us test our regex with a valid string
	test = ''
	match = p.match(test)
	if match is None:
		print(f'No Match: {test}')
	else:
		print(f'Match: {test}')
	
	# Let us test our regex with an invalid string.
	# Why is it invalid?
	test = ''
	match = p.match(test)
	if match is None:
		print(f'No Match: {test}')
	else:
		print(f'Match: {test}')



################ Do not make any changes below this line ################
if __name__ == '__main__':
    main()
