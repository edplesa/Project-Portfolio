import numpy as np
import cv2
import math


def calculate_hs_histogram(img_list, bin_size):
    max_h = 179
    max_s = 255
    hs_hist = np.zeros((math.ceil((max_h + 1) / bin_size), math.ceil((max_s + 1) / bin_size)))

    for img in img_list:
        height, width, _ = img.shape
        img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        for i in range(height):
            for j in range(width):
                h = img_hsv[i, j, 0]
                s = img_hsv[i, j, 1]
                hs_hist[math.floor(h / bin_size), math.floor(s / bin_size)] += 1
        hs_hist /= hs_hist.sum()
    return hs_hist


def color_segmentation(img, hs_hist, bin_size, threshold):
    height, width, _ = img.shape
    hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
    mask = np.zeros((height, width, 1))
    for i in range(height):
        for j in range(width):
            h = hsv[i, j, 0]
            s = hsv[i, j, 1]
            if hs_hist[math.floor(h / bin_size), math.floor(s / bin_size)] > threshold:
                mask[i, j, 0] = 1
    return mask


def get_observations(img_list):
    observs = []
    for img in img_list:
        height, width, _ = img.shape
        img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        for i in range(height):
            for j in range(width):
                h = img_hsv[i, j, 0]
                s = img_hsv[i, j, 1]
                row = [h, s]
                observs.append(row)

    observs = np.array(observs)

    return observs


def get_sample_mean_vector(observations):
    obs_height, _ = observations.shape
    sample_mean_vector = [(np.sum(observations[:, 0]) / obs_height),
                          (np.sum(observations[:, 1]) / obs_height)]

    return np.array(sample_mean_vector)

#
# Code was referenced from https://stackoverflow.com/questions/60992887/computing-covariance-matrix-without-using-numpy
#
def get_sample_covariance(observations, sample_mean):
    Cov_matrix = []
    for j in range(len(sample_mean)):
        covs = []
        for k in range(len(sample_mean)):
            terms = ((observations[i][j] - sample_mean[j]) * (observations[i][k] - sample_mean[k]) for i in
                     range(len(sample_mean)))
            covariance = sum(terms) / (len(sample_mean) - 1)
            covs.append(covariance)
        Cov_matrix.append(covs)

    Cov_matrix = np.array(Cov_matrix)
    return Cov_matrix

#
#   Code here was referenced from: https://scipython.com/blog/visualizing-the-bivariate-gaussian-distribution/
#
def gaussian_dist(img, mu, sigma):
    height, width, _ = img.shape
    dist = np.zeros((height, width, 1))

    for i in range(height):
        for j in range(width):
            x = np.array(img[i,j,0],img[i,j,1])

            n = mu.shape[0]
            Sigma_det = np.linalg.det(sigma)
            Sigma_inv = np.linalg.inv(sigma)
            N = np.sqrt((2 * np.pi) ** n * Sigma_det)

            fac = np.einsum('...k,kl,...l->...', x - mu, Sigma_inv, x - mu)
            dist[i,j] = np.exp(-fac / 2) / N

    return dist


def get_mask(prob, thresh):
    height, width, _ = prob.shape
    mask = np.zeros((height,width,1))

    for i in range(height):
        for j in range(width):
            if (prob[i,j] > thresh):
                mask[i,j] = 1

    return mask


# #
# #  This chunk of code was used to generate the segmentation result for question P1.
# #
# # Training
# img_list = []
# for i in range(1,11):
#     path = "training" + str(i) + ".png"
#     img_train = cv2.imread(path)
#     img_list.append(img_train)
#
# bin_size = 20
# hs_hist = calculate_hs_histogram(img_list, bin_size)
#
# # Testing
# img_test = cv2.imread("testing_image.bmp")
#
# threshold = 1E-10
# mask = color_segmentation(img_test, hs_hist, bin_size, threshold)
#
# img_seg = img_test * mask
# img_seg = img_seg.astype(np.uint8)
#
# # cv2.imshow("Input", img_test)
# # cv2.imshow("Mask", (mask*255).astype(np.uint8))
# cv2.imwrite("Segmentation result.png", img_seg)
# #cv2.waitKey()
########################################################################################################################
# #
# #   This check of code was used to generate the images for question P2.
# #
# img_list = []
# for i in range(1, 11):
#     path = "training" + str(i) + ".png"
#     img_train = cv2.imread(path)
#     img_list.append(img_train)
#
# img = cv2.imread("testing_image.bmp")
# img_hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
#
# observations = get_observations(img_list)
# mean_vector = get_sample_mean_vector(observations)
# covariance_matrix = get_sample_covariance(observations, mean_vector)
#
# probabilities = gaussian_dist(img_hsv, mean_vector,covariance_matrix)
#
# mask = get_mask(probabilities, 0.000001)
#
#
# img_seg = img * mask
# img_seg = img_seg.astype(np.uint8)
# cv2.imwrite("gaussian testing_image.bmp", img_seg)
########################################################################################################################
# #
# #   This chunk of code was used to generate the images for question P3.
# #
# img = cv2.imread('checkerboard.png')
# img2 = cv2.imread('toy.png')
#
# gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
# gray2 = cv2.cvtColor(img2,cv2.COLOR_BGR2GRAY)
#
# gray = np.float32(gray)
# gray2 = np.float32(gray2)
#
# dst = cv2.cornerHarris(gray,2,3,0.04)
# dst2 = cv2.cornerHarris(gray2,2,3,0.04)
#
# #result is dilated for marking the corners, not important
# dst = cv2.dilate(dst,None)
# dst2 = cv2.dilate(dst2,None)
#
# # Threshold for an optimal value, it may vary depending on the image.
# img[dst>0.01*dst.max()]=[0,0,255]
# img2[dst2>0.01*dst2.max()]=[0,0,255]
#
# cv2.imwrite('checkboard with harris corner detection.png',img)
# cv2.imwrite('toy with harris corner detection.png',img2)
########################################################################################################################
