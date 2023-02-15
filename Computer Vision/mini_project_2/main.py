import math
import cv2
import numpy as np
import matplotlib.pyplot as plt


def convolution(im, kernel):
    kernel = np.flip(np.flip(kernel, axis=0), axis=1)
    im_height, im_width = im.shape
    kernel_size = kernel.shape[0]
    pad_size = int((kernel_size - 1) / 2)
    im_padded = np.zeros((im_height + pad_size * 2, im_width + pad_size * 2))
    im_padded[pad_size:-pad_size, pad_size:-pad_size] = im

    im_out = np.zeros_like(im)
    for x in range(im_width):
        for y in range(im_height):
            im_patch = im_padded[y:y + kernel_size, x:x + kernel_size]
            new_value = np.sum(kernel * im_patch)
            im_out[y, x] = new_value
    return im_out


def get_gaussian_kernel(kernel_size, sigma):
    kernel_x = np.linspace(-(kernel_size // 2), kernel_size // 2, kernel_size)
    for i in range(kernel_size):
        kernel_x[i] = np.exp(-(kernel_x[i] / sigma) ** 2 / 2)
    kernel = np.outer(kernel_x.T, kernel_x.T)

    kernel *= 1.0 / kernel.sum()
    return kernel


def compute_gradient(im):
    sobel_filter_x = np.array([[1, 0, -1], [2, 0, -2], [1, 0, -1]])
    sobel_filter_y = np.array([[1, 2, 1], [0, 0, 0], [-1, -2, -1]])
    gradient_x = convolution(im, sobel_filter_x)
    gradient_y = convolution(im, sobel_filter_y)

    magnitude = np.sqrt(np.square(gradient_x) + np.square(gradient_y))
    magnitude *= 255.0 / magnitude.max()
    direction = np.arctan2(gradient_y, gradient_x)
    direction *= 180 / np.pi
    return magnitude, direction


def nms(magnitude, direction):
    height, width = magnitude.shape
    res = np.zeros(magnitude.shape)
    direction[direction < 0] += 180  # (-180, 180) -> (0, 180)

    for y in range(1, height - 1):
        for x in range(1, width - 1):
            current_direction = direction[y, x]
            current_magnitude = magnitude[y, x]
            if (0 <= current_direction < 22.5) or (157.5 <= current_direction <= 180):
                p = magnitude[y, x - 1]
                r = magnitude[y, x + 1]

            elif 22.5 <= current_direction < 67.5:
                p = magnitude[y + 1, x + 1]
                r = magnitude[y - 1, x - 1]

            elif 67.5 <= current_direction < 112.5:
                p = magnitude[y - 1, x]
                r = magnitude[y + 1, x]

            else:
                p = magnitude[y - 1, x + 1]
                r = magnitude[y + 1, x - 1]

            if current_magnitude >= p and current_magnitude >= r:
                res[y, x] = current_magnitude

    return res


def hysteresis_threshold(im, high, low):
    strong_val = 255 # white color
    weak_val = 150 # gray color
    noise_val = 30 # very dark gray color

    height, width = im.shape

    strong_map = np.zeros(im.shape)
    weak_map = np.zeros(im.shape)
    noise_map = np.zeros(im.shape)
    full_map = np.zeros(im.shape)


    for x in range(width):
        for y in range(height):
            if im[y,x] > high:
                full_map[y,x] = strong_val
                strong_map[y,x] = strong_val

            elif im[y,x] < low:
                full_map[y, x] = noise_val
                noise_map[y,x] = noise_val

            else:
                full_map[y, x] = weak_val
                weak_map[y,x] = weak_val

    return full_map,strong_map,weak_map,noise_map


def edge_link(im):
    strong_val = 255  # white color
    weak_val = 150  # gray color
    noise_val = 30  # very dark gray color

    height, width = im.shape

    res = np.array(im)

    for x in range(width):
        for y in range(height):
            if res[y,x] == weak_val:
                if ((res[y-1,x-1] == strong_val) or (res[y-1,x] == strong_val) or (res[y-1,x+1] == strong_val) or
                    (res[y,x-1] == strong_val) or (res[y,x+1] == strong_val) or
                    (res[y+1,x-1] == strong_val) or (res[y+1,x] == strong_val) or (res[y+1,x+1] == strong_val)):
                   res[y,x] = strong_val
                else:
                    res[y,x] = noise_val

    return res


def HoughTransform(edge_map):
    theta_values = np.deg2rad(np.arange(-90.0, 90.0))
    height, width = edge_map.shape
    diagonal_length = int(round(math.sqrt(width * width + height * height)))
    rho_values = np.linspace(-diagonal_length, diagonal_length, diagonal_length * 2 + 1)

    accumulator = np.zeros((len(rho_values), len(theta_values)), dtype=int)
    y_coordinates, x_coordinates = np.nonzero(edge_map)

    for edge_idx in range(len(x_coordinates)):
        x = x_coordinates[edge_idx]
        y = y_coordinates[edge_idx]
        for theta_idx in range(len(theta_values)):
            theta = theta_values[theta_idx]
            rho = int(round(x * np.cos(theta) + y * np.sin(theta)))
            accumulator[rho + diagonal_length, theta_idx] += 1
        # print("%d out of %d edges have voted" % (edge_idx+1, len(x_coordinates)))
        # cv2.imshow("Accumulator", (accumulator*255/accumulator.max()).astype(np.uint8))
        # cv2.waitKey(0)
    return accumulator, theta_values, rho_values

def suppress_hough_lines(lines, acc, size):
    res = []
    for line in lines:
        patch_x = int(line[0] - size // 2)
        patch_y = int(line[1] - size // 2)
        patch = acc[patch_x:patch_x+size, patch_y:patch_y+size]

        maxima = np.unravel_index(np.argmax(patch), patch.shape)

        if (maxima[0] == size // 2) and (maxima[1] == size // 2):
            res.append([line[0],line[1]])

    return res



#
# # This chunk of code was used to generate the images for question P4.
# #
# lena = cv2.imread('lena.png')
# lena = cv2.cvtColor(lena, cv2.COLOR_BGR2GRAY)
# lena_edges = cv2.Canny(lena,110,150)
#
#
# shape = cv2.imread('shape.bmp')
# paper = cv2.imread('paper.bmp')
#
#
# shape_edges = cv2.Canny(shape,110,150)
# paper_edges = cv2.Canny(paper,110,150)
#
#
# shape_lines = cv2.HoughLines(shape_edges,1,np.pi/180,45)
# paper_lines = cv2.HoughLines(paper_edges,1,np.pi/180,50)
#
# if shape_lines is not None:
#         for i in range(0, len(shape_lines)):
#             rho = shape_lines[i][0][0]
#             theta = shape_lines[i][0][1]
#             a = math.cos(theta)
#             b = math.sin(theta)
#             x0 = a * rho
#             y0 = b * rho
#             pt1 = (int(x0 + 1000*(-b)), int(y0 + 1000*(a)))
#             pt2 = (int(x0 - 1000*(-b)), int(y0 - 1000*(a)))
#             cv2.line(shape, pt1, pt2, (0,0,255), 2, cv2.LINE_AA)
#
# if paper_lines is not None:
#         for i in range(0, len(paper_lines)):
#             rho = paper_lines[i][0][0]
#             theta = paper_lines[i][0][1]
#             a = math.cos(theta)
#             b = math.sin(theta)
#             x0 = a * rho
#             y0 = b * rho
#             pt1 = (int(x0 + 1000*(-b)), int(y0 + 1000*(a)))
#             pt2 = (int(x0 - 1000*(-b)), int(y0 - 1000*(a)))
#             cv2.line(paper, pt1, pt2, (0,0,255), 2, cv2.LINE_AA)
#
# cv2.imwrite("lena cv2 Canny.png", lena_edges)
# cv2.imwrite("paper cv2 HoughLines.bmp", paper)
# cv2.imwrite("shape cv2 HoughLines.bmp", shape)
####################################################################################################################
# #
# # This chunk of code was used to generate the images for question P3.
# #
# shape_im = cv2.imread('shape.bmp')
# paper_im = cv2.imread('paper.bmp')
#
# shape_im_gray = cv2.cvtColor(shape_im, cv2.COLOR_BGR2GRAY)
# paper_im_gray = cv2.cvtColor(paper_im, cv2.COLOR_BGR2GRAY)
#
# shape_edge_map = cv2.Canny(shape_im_gray, 70, 150)
# paper_edge_map = cv2.Canny(paper_im_gray, 70, 150)
#
# shape_accumulator, shape_theta_values, shape_rho_values = HoughTransform(shape_edge_map)
# paper_accumulator, paper_theta_values, paper_rho_values = HoughTransform(paper_edge_map)
#
# shape_lines = np.argwhere(shape_accumulator > 30)
# paper_lines = np.argwhere(paper_accumulator > 46)
#
# new_shape_lines = suppress_hough_lines(shape_lines,shape_accumulator,3)
# new_paper_lines = suppress_hough_lines(paper_lines,paper_accumulator,3)
#
# # print(len(shape_lines),len(new_shape_lines)) # These lines show the difference the suppress_hough_lines fxn makes
# # print(len(paper_lines),len(new_paper_lines))
#
# height, width = shape_im_gray.shape
# for line in new_shape_lines:
#     rho = shape_rho_values[line[0]]
#     theta = shape_theta_values[line[1]]
#     slope = -np.cos(theta)/np.sin(theta)
#     intercept = rho/np.sin(theta)
#     x1, x2 = 0, width
#     y1 = int(slope*x1 + intercept)
#     y2 = int(slope*x2 + intercept)
#     cv2.line(shape_im, (x1, y1), (x2, y2), (0, 0, 255), 2)
#
# height, width = paper_im_gray.shape
# for line in new_paper_lines:
#     rho = paper_rho_values[line[0]]
#     theta = paper_theta_values[line[1]]
#     slope = -np.cos(theta)/np.sin(theta)
#     intercept = rho/np.sin(theta)
#     x1, x2 = 0, width
#     y1 = int(slope*x1 + intercept)
#     y2 = int(slope*x2 + intercept)
#     cv2.line(paper_im, (x1, y1), (x2, y2), (0, 0, 255), 2)
#
#
# cv2.imwrite("shape reduced hough lines.png", shape_im)
# cv2.imwrite("paper reduced hough lines.png", paper_im)
####################################################################################################################
# im = cv2.imread("lena.png", 0)
# im = im.astype(float)
#
# gaussian_kernel = get_gaussian_kernel(9, 3)
# im_smoothed = convolution(im, gaussian_kernel)
#
# gradient_magnitude, gradient_direction = compute_gradient(im_smoothed)
#
# edge_nms = nms(gradient_magnitude, gradient_direction)
#
#
# # Creating the strong, weak, and noise maps for 3 different sets of high and low thresholds
# # for Question P1.
#
# full_map1, strong_map1, weak_map1, noise_map1 = hysteresis_threshold(edge_nms, 100, 50)
# full_map2, strong_map2, weak_map2, noise_map2 = hysteresis_threshold(edge_nms, 50, 30)
# full_map3, strong_map3, weak_map3, noise_map3 = hysteresis_threshold(edge_nms, 30, 15)
#
# cv2.imwrite('lena strong 100 50 threshold.png', strong_map1.astype(np.uint8))
# cv2.imwrite('lena weak 100 50 threshold.png', weak_map1.astype(np.uint8))
# cv2.imwrite('lena noise 100 50 threshold.png', noise_map1.astype(np.uint8))
#
# cv2.imwrite('lena strong 50 30 threshold.png', strong_map2.astype(np.uint8))
# cv2.imwrite('lena weak 50 30 threshold.png', weak_map2.astype(np.uint8))
# cv2.imwrite('lena noise 50 30 threshold.png', noise_map2.astype(np.uint8))
#
# cv2.imwrite('lena strong map 30 15 threshold.png', strong_map3.astype(np.uint8))
# cv2.imwrite('lena weak map 30 15 threshold.png', weak_map3.astype(np.uint8))
# cv2.imwrite('lena noise map 30 15 threshold.png', noise_map3.astype(np.uint8))
#
#
# # Linking the edges in the edge map for Question P2.
#
# edge_linked1 = edge_link(full_map1)
# edge_linked2 = edge_link(full_map2)
# edge_linked3 = edge_link(full_map3)
#
#
# cv2.imwrite('lena linked edges 100 50 threshold.png', edge_linked1.astype(np.uint8))
# cv2.imwrite('lena linked edges 50 30 threshold.png', edge_linked2.astype(np.uint8))
# cv2.imwrite('lena linked edges 30 15 threshold.png', edge_linked3.astype(np.uint8))