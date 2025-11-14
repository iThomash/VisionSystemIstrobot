import cv2
import numpy as np
import matplotlib.pyplot as plt
import time

kernel = np.ones((5,5), np.uint8)
for z in range(1,19,1):
    t1 = time.time()
    img = cv2.imread(f"./VisionSystem/zdjecia/zdjecie{z}.jpg", cv2.IMREAD_GRAYSCALE)
    h = round(0.9 * img.shape[0])
    img_arr_cut = img[0 : h, 0 : img.shape[1]]
    # img_blurred = cv2.medianBlur(img, (5,5))
    ret, img_thres = cv2.threshold(img_arr_cut, 160, 255, cv2.THRESH_BINARY)
    img_morph = cv2.morphologyEx(img_thres, cv2.MORPH_CLOSE, kernel)
    s1 = [0] * img_morph.shape[1] # Array of zeros
    s2 = [0] * img_morph.shape[0] # Array of zeros
    # print(img_morph.shape)
    for i in range(img_morph.shape[0]):
        c = img_morph[i] < 50
        s2[i] = np.sum(c)
        for j in range(img_morph.shape[1]):
            if img_morph[i][j] < 50:
                s1[j]+=1
    sum1=0
    sum2=0
    for i in range(len(s1)):
        if (s1[i]>=100):
            sum1+=1
    for i in range(len(s2)):
        if (s2[i]>=100):
            sum2+=1
    t2 = time.time()

    if sum1/len(s1)>=0.6 and sum2/len(s2) >=0.6:
    # ser.write(bytearray("{\"result\": \"enemy\"}"))
        print("{\"result\": \"enemy\"}")
    elif sum1/len(s1)>=0.18 and sum2/len(s2) >=0.18:
        # ser.write(bytearray("{\"result\": \"can\"}"))
        print("{\"result\": \"can\"}")
    else:
        # ser.write(bytearray("{\"result\": \"None\"}"))
        print("{\"result\": \"None\"}")




    # print(f"Zdjecie: {z}: {round(sum1/len(s1), 2)}\t Czas: {t2-t1}")
    # print(f"Zdjecie: {z}: {round(sum2/len(s2), 2)}\t Czas: {t2-t1}")
    # if z==5:
    #     cv2.imshow("test5", img_morph)

# img_dilated = cv2.dilate(img, np.ones((7,7), np.uint8))
# img_blurred = cv2.medianBlur(img_dilated, 21)
# img_diff = 255 - cv2.absdiff(img, img_blurred)
# img_norm = img_diff.copy()
# cv2.normalize(img_diff, img_norm, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_8UC1)
# _, img_thresh = cv2.threshold(img_norm, 128, 255, cv2.THRESH_BINARY)
# cv2.normalize(img_thresh, img_thresh, alpha=0, beta=255, norm_type=cv2.NORM_MINMAX, dtype=cv2.CV_8UC1)

cv2.imshow("test1", img_morph)
# cv2.imshow("test2", img_thres)
# cv2.imshow("test3", img_morph)
cv2.waitKey(0)
cv2.destroyAllWindows()
# plt.figure()

# plt.imshow(img)
# plt.show()

