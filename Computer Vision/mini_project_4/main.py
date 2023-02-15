import numpy as np
import cv2
import math


def rotate(point, angle):
    orig_point = np.array([point[0], point[1]])
    angle = math.radians(angle)
    rotation_matrix = np.array([[math.cos(angle), -math.sin(angle)], [math.sin(angle), math.cos(angle)]])
    newp = np.matmul(rotation_matrix, orig_point).astype(np.uint8)
    return (newp[0], newp[1])


def rotate_around_point(point1, point2, angle):
    angle = math.radians(angle)

    translation_matrix_back = np.array([[1, 0, -point2[0]],
                                        [0, 1, -point2[1]],
                                        [0, 0, 1]])

    translation_matrix_for = np.array([[1, 0, point2[0]],
                                       [0, 1, point2[1]],
                                       [0, 0, 1]])

    rotation_matrix = np.array([[math.cos(angle), -math.sin(angle), 0],
                                [math.sin(angle), math.cos(angle), 0],
                                [0, 0, 1]])

    newp = np.matmul(translation_matrix_back, np.array([point1[0], point1[1], 1]))

    newp = np.matmul(rotation_matrix, newp)

    newp = np.matmul(translation_matrix_for, newp).astype(np.uint8)

    return (newp[0], newp[1])


#
#   This chunk of code was used to generate the image for question P1.
#
# arr = np.full((500, 500, 3), 255)
# arr = arr.astype(np.uint8)
#
# point_a = (100, 40)
# cv2.circle(arr, point_a, 10, (0, 0, 255), -1)
#
# point_b = rotate(point_a, 60)
# cv2.circle(arr, point_b, 10, (0, 255, 0), -1)
#
# point_c = (100, 100)
# cv2.circle(arr, point_c, 10, (0, 0, 0), -1)
#
# point_d = rotate_around_point(point_a, point_c, 60)
# cv2.circle(arr, point_d, 10, (255, 0, 0), -1)
#
# cv2.imwrite("Geometric Transforms.png", arr)
########################################################################################################################
#
#   This chunk of code was used to generate the images for question P2.
#
# img = cv2.imread('lena.png')
#
# height, width, ch = img.shape
#
# center = (int(height / 2), int(width / 2))
#
# first = np.float32([[1, 0, 100],
#                     [0, 1, 200]])
#
# second = np.float32([[-1, 0, width - 1],
#                      [0, 1, 0]])
#
# third = np.float32([[math.cos(math.radians(45)), -math.sin(math.radians(45)), 0],
#                     [math.sin(math.radians(45)), math.cos(math.radians(45)), 0]])
#
# fourth1 = np.float32([[1, 0, -center[0]],
#                       [0, 1, -center[1]]])
#
# fourth2 = np.float32([[1, 0, center[0]],
#                       [0, 1, center[1]]])
#
#
# # first_transform = cv2.warpAffine(img, first, (width, height))
# #
# # second_transform = cv2.warpAffine(img, second, (width, height))
# #
# # third_transform = cv2.warpAffine(img, third, (width, height))
# #
# # cv2.imwrite("lena_first_transform.png", first_transform)
# # cv2.imwrite("lena_second_transform.png", second_transform)
# # cv2.imwrite("lena_third_transform.png", third_transform)
#
# fourth_transform = cv2.warpAffine(img, fourth1, (width, height))
# fourth_transform = cv2.warpAffine(fourth_transform, third, (width, height))
# fourth_transform = cv2.warpAffine(fourth_transform, fourth2, (width, height))
#
# cv2.imwrite("lena_fourth_transform.png", fourth_transform)





