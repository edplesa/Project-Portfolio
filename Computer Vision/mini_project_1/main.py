import cv2
import numpy as np
import math


def meanKernel(size):
    kernel = np.ones((size,size), dtype=float)/(size**2)
    return kernel

def sharpeningKernel(size):
    kernel = np.zeros((size,size), dtype=float)
    kernel[int(size/2)][int(size/2)] = 2
    kernel = kernel - meanKernel(size)
    return kernel

def gaussianKernel(size):
    kernel = np.empty((0,size),dtype=float)

    for j in range(int(-size/2),int(size/2)+1):
        row = []
        for i in range(int(-size/2),int(size/2)+1):

            val = math.pow(math.e,-(pow(i,2)+pow(j,2))/2)/(2*math.pi)
            row.append(val)
        kernel = np.append(kernel, np.array([row]),axis=0)

    kSum = kernel.sum()
    kernel = kernel/kSum

    return kernel


def rotateKernel(kernel):
    size = kernel.shape[0]
    rotatedKernel = np.zeros((size, size), dtype=float)
    for i in range(size):
        for j in range(size):
            rotatedKernel[i, size - 1 - j] = kernel[size - 1 - i, j]

    return rotatedKernel


def convolution(im, kernel):
    kernel = rotateKernel(kernel)
    im_height, im_width, im_channels = im.shape
    kernel_size = kernel.shape[0]
    pad_size = int((kernel_size - 1) / 2)
    im_padded = np.zeros((im_height + pad_size * 2, im_width + pad_size * 2, im_channels))
    im_padded[pad_size:-pad_size, pad_size:-pad_size, :] = im

    im_out = np.zeros_like(im)
    for c in range(im_channels):
        for x in range(im_width):
            for y in range(im_height):
                im_patch = im_padded[y:y + kernel_size, x:x + kernel_size, c]
                new_value = np.sum(kernel * im_patch)
                new_value = (int)(min(max(0,new_value),255))
                im_out[y, x, c] = new_value

    return im_out


def median_filter(im,patch_size):
    im_height, im_width, im_channels = im.shape
    pad_size = int((patch_size - 1) / 2)
    im_padded = np.zeros((im_height + pad_size * 2, im_width + pad_size * 2, im_channels))
    im_padded[pad_size:-pad_size, pad_size:-pad_size, :] = im

    im_out = np.zeros_like(im)
    for c in range(im_channels):
        for x in range(im_width):
            for y in range(im_height):
                im_patch = im_padded[y:y + patch_size, x:x + patch_size, c]
                new_value = np.median(im_patch)
                new_value = (int)(min(max(0, new_value), 255))
                im_out[y,x,c] = new_value

    return im_out




# im = cv2.imread("lena.png")
# im = im.astype(float)
# for i in range(3,8,2):                                  # This chuck of code was used to generate
#     im_out = cv2.filter2D(im,-1,gaussianKernel(i))      # all the output images for question P3.
#     im_out = im_out.astype(np.uint8)                    # The output using the built in filter2D
#     fname = 'LenaFilter2DGauss'+str(i)+'.png'           # function looks pretty much like the output
#     cv2.imwrite(fname,im_out)                           # of the convolution function implemented here.
########################################################################################################
# im = cv2.imread("art.png")
# im = im.astype(float)
# for i in range(3,10,2):                                 # This chuck of code was used to generate
#     im_out = median_filter(im,i)                        # all the output images for question P2.
#     im_out = im_out.astype(np.uint8)
#     fname = 'ArtMedianFilter'+str(i)+'.png'
#     cv2.imwrite(fname, im_out)
#
#     im_out = convolution(im, meanKernel(i))
#     im_out = im_out.astype(np.uint8)
#     fname = 'ArtMeanFilter' + str(i) + '.png'
#     cv2.imwrite(fname, im_out)
########################################################################################################
# im = cv2.imread("lena.png")
# im = im.astype(float)
# for i in range(3,8,2):                                    # This chunk of code was used to generate
#     im_out = convolution(im,meanKernel(i))                # all the output images for question P1.
#     im_out = im_out.astype(np.uint8)
#     fname = 'LenaMeanKernelSize' + str(i) + '.png'
#     cv2.imwrite(fname, im_out)
#
#     im_out = convolution(im, sharpeningKernel(i))
#     im_out = im_out.astype(np.uint8)
#     fname = 'LenaSharpeningKernelSize' + str(i) + '.png'
#     cv2.imwrite(fname, im_out)
#
#     im_out = convolution(im, gaussianKernel(i))
#     im_out = im_out.astype(np.uint8)
#     fname = 'LenaGaussianKernelSize' + str(i) + '.png'
#     cv2.imwrite(fname, im_out)



