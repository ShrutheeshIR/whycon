import cv2
import numpy as np
from whycon2 import *
import time
whyc = Whycon(1,0.038)

cap = cv2.VideoCapture(4);
cap.set(cv2.CAP_PROP_AUTOFOCUS, 0)
cap.set(28, 0) 
ctr = 0
out = []
while(1):
    ctr+=1
    ret, frame = cap.read()
    # print(frame.shape)
    t1 = time.time()
    # print(type(frame))
    if ctr>20:
        out = whyc.processimage(frame.copy())
    if len(out):
        print("DIST - ",out[0]['z'])
        if abs(out[0]['z'] - 0.92) > 0.02:
            print("\n\n\nWARNING\n\n")
        print(time.time()-t1)
    cv2.imshow('frame', frame)
    ch = cv2.waitKey(1)
    if ch == ord('q'):
        whyc.cleanmem()
        break

cv2.destroyAllWindows()