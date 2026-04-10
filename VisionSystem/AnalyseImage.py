import cv2
import numpy as np
import matplotlib.pyplot as plt
import time

kernel = np.ones((5,5), np.uint8)
for z in range(159,160,1):
    t1 = time.time()
    img = cv2.imread(f"./VisionSystem/zdjecia/zdjecie{z}.jpg", cv2.IMREAD_UNCHANGED)
    h = round(0.9 * img.shape[0])
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    img_arr_cut = img_gray[round(0.1 * img.shape[0]) : round(0.8 * img.shape[0]), 0 : img.shape[1]]
    ret, img_thres = cv2.threshold(img_arr_cut, 139, 255, cv2.THRESH_BINARY)
    img_morph = cv2.morphologyEx(img_thres, cv2.MORPH_CLOSE, kernel)
    s1 = [0] * img_morph.shape[1]
    s2 = [0] * img_morph.shape[0]
    # print(img_morph.shape)
    for i in range(img_morph.shape[0]):
            c = img_morph[i] < 11
            s2[i] = np.sum(c)
            for j in range(img_morph.shape[1]):
                    if img_morph[i][j] < 11:
                            s1[j]+=1
    sum1=0
    sum2=0
    for i in range(len(s1)):
            if (s1[i]>=101):
                    sum1+=1
    for i in range(len(s2)):
            if (s2[i]>=101):
                    sum2+=1
    t2 = time.time()

    if sum1/len(s1)>=0.6 and sum2/len(s2) >=0.6:
    # ser.write(bytearray("{\"result\": \"enemy\"}"))
        print("{\"result\": \"enemy\"}")
    elif sum1/len(s1)>=0.19 and sum2/len(s2) >=0.19:
        # ser.write(bytearray("{\"result\": \"can\"}"))
        print("{\"result\": \"can\"}")
    else:
        # ser.write(bytearray("{\"result\": \"None\"}"))
        print("{\"result\": \"None\"}")




    print(f"Zdjecie: {z}: {round(sum1/len(s1), 2)}\t Czas: {t2-t1}")
    print(f"Zdjecie: {z}: {round(sum2/len(s2), 2)}\t Czas: {t2-t1}")
    # if z==26:
    cv2.imshow(f"test{z}", img_morph)


# cv2.imshow("test1", img_morph)
# cv2.imshow("test2", img_thres)
# cv2.imshow("test3", img_morph)
cv2.waitKey(0)
cv2.destroyAllWindows()
# plt.figure()

# plt.imshow(img)
# plt.show()

