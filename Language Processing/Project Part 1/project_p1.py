from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.naive_bayes import GaussianNB
import pandas as pd
import numpy as np
import string
import re


# Function: load_as_list(fname)
# fname: A string indicating a filename
# Returns: Two lists: one a list of document strings, and the other a list of integers
#
# This helper function reads in the specified, specially-formatted CSV file
# and returns a list of documents (documents) and a list of binary values (label).
def load_as_list(fname):
    df = pd.read_csv(fname)
    documents = df['review'].values.tolist()
    labels = df['label'].values.tolist()
    return documents, labels


# Function: extract_user_info, see project statement for more details
# user_input: A string of arbitrary length
# Returns: name as string
def extract_user_info(user_input):
    name = r"((?:(?<=\s)|(?<=^))([A-Z][a-zA-Z.\-&']*(\s+)[A-Z][a-zA-Z.\-&']*(\s+)[A-Z][a-zA-Z.\-&']*(\s+)[A-Z][a-zA-Z.\-&']*)(?=\s|$))|" \
           r"((?:(?<=\s)|(?<=^))([A-Z][a-zA-Z.\-&']*(\s+)[A-Z][a-zA-Z.\-&']*(\s+)[A-Z][a-zA-Z.\-&']*)(?=\s|$))|" \
           r"((?:(?<=\s)|(?<=^))([A-Z][a-zA-Z.\-&']*(\s+)[A-Z][a-zA-Z.\-&']*)(?=\s|$))"

    found = re.search(name, user_input)

    if found != None:
        return found.group(0)
    else:
        return ""


# Function to convert a given string into a list of tokens
# Args:
#   inp_str: input string 
# Returns: token list, dtype: list of strings
def get_tokens(inp_str):
    return inp_str.split()


# Function: preprocessing, see project statement for more details
# Args:
#   user_input: A string of arbitrary length
# Returns: A string of arbitrary length
def preprocessing(user_input):
    removedWhite = get_tokens(user_input)

    removedPunc = []
    for word in removedWhite:
        if word not in string.punctuation:
            removedPunc.append(word)

    lowerTokens = [word.lower() for word in removedPunc]

    modified_input = ' '.join(lowerTokens)
    return modified_input


# Function: vectorize_train, see project statement for more details
# training_documents: A list of strings
# Returns: An initialized TfidfVectorizer model, and a document-term matrix, dtype: scipy.sparse.csr.csr_matrix
def vectorize_train(training_documents):
    # Initialize the TfidfVectorizer model and document-term matrix
    vectorizer = TfidfVectorizer()
    tfidf_train = None
    

    processedDocs = []
    for doc in training_documents:
        processed = preprocessing(doc)
        processedDocs.append(processed)

    tfidf_train = vectorizer.fit_transform(processedDocs)

    return vectorizer, tfidf_train


# Function: vectorize_test, see project statement for more details
# vectorizer: A trained TFIDF vectorizer
# user_input: A string of arbitrary length
# Returns: A sparse TFIDF representation of the input string of shape (1, X), dtype: scipy.sparse.csr.csr_matrix
#
# This function computes the TFIDF representation of the input string, using
# the provided TfidfVectorizer.
def vectorize_test(vectorizer, user_input):
    # Initialize the TfidfVectorizer model and document-term matrix
    tfidf_test = None

    processed = preprocessing(user_input)

    processed = [processed]

    tfidf_test = vectorizer.transform(processed)

    return tfidf_test


# Function: train_model(training_documents, training_labels)
# training_data: A sparse TfIDF document-term matrix, dtype: scipy.sparse.csr.csr_matrix
# training_labels: A list of integers (0 or 1)
# Returns: A trained model
def train_model(training_data, training_labels):
    # Initialize the GaussianNB model and the output label
    nb_model = GaussianNB()
    
    denseArray = training_data.toarray()
    nb_model.fit(denseArray, training_labels)

    return nb_model

# Function: get_model_prediction(nb_model, tfidf_test)
# nb_model: A trained GaussianNB model
# tfidf_test: A sparse TFIDF representation of the input string of shape (1, X), dtype: scipy.sparse.csr.csr_matrix
# Returns: A predicted label for the provided test data (int, 0 or 1)
def get_model_prediction(nb_model, tfidf_test):
    # Initialize the output label
    label = 0    

    denseArray = tfidf_test.toarray()
    label = nb_model.predict(denseArray)

    return label


if __name__ == "__main__":

    # Display a welcome message to the user, and accept a user response of arbitrary length
    user_input = input("Welcome to best chat bot ever invented! What's your name?:\n")

    # Extract the user's name
    name = extract_user_info(user_input)

    # Query the user for a response
    user_input = input(f"Thanks {name}!  What do you want to talk about today?\n")

    #Set things up ahead of time by training the TfidfVectorizer and Naive Bayes model
    documents, labels = load_as_list("dataset.csv")

    vectorizer, tfidf_train = vectorize_train(documents)
    nb_model = train_model(tfidf_train, labels)

    # Predict whether the user's sentiment is positive or negative
    tfidf_test = vectorize_test(vectorizer, user_input)

    label = get_model_prediction(nb_model, tfidf_test)
    if label == 0:
        print("Hmm, it seems like you're feeling a bit down.")
    elif label == 1:
        print("It sounds like you're in a positive mood!")
    else:
        print("Hmm, that's weird.  My classifier predicted a value of: {0}".format(label))
