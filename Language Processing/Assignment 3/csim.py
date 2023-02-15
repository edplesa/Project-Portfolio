import numpy as np
import numpy.linalg as npla


# Function to get cosine similarity see Equation 6.10 (Jurafsky & Martin v3) for reference
# Arguments:
# a: A numpy vector of size (x, )
# b: A numpy vector of size (x, )
# Returns: sim (float)
# Where, sim (float) is the cosine similarity between vectors a and b. x is the size of the numpy vector. Assume that both vectors are of the same size.
def cosine_similarity(a: np.ndarray, b: np.ndarray) -> float:
    cosine_sim = np.dot(a,b) / (npla.norm(a)*npla.norm(b))
    return cosine_sim


def main():
    # Initialize the vectors
    a = np.array([1, 2, 3])
    b = np.array([7, 8, 9])

    # We can print the vectors as 
    print("Vector a: {0}".format(a))
    print("Vector b: {0}".format(b))

    # We can see shape (and dimensions) of vectors as
    print("Vector a shape: {0}".format(a.shape))
    print("Vector b shape: {0}".format(b.shape))

    # Compute cosine similarity
    sim = cosine_similarity(a, b)
    print("Cosine similarity: {0:.2}".format(sim))



################ Do not make any changes below this line ################
if __name__ == '__main__':
    main()
