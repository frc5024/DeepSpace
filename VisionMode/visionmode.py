#! /usr/bin/python3

from cscore import CameraServer, VideoSource
from networktables import NetworkTablesInstance
import cv2
import json
import sys
import numpy as np
import datetime
import time as pytime

camera = None
cvsink = None
outputStreamStd = None


# Config
height = 480
width = 640

cutoff = 50

source = np.zeros(shape=(height, width, 3), dtype=np.uint8)
output = np.zeros(shape=(height, width, 3), dtype=np.uint8)

def centrePoint(box):
    x, y, w, h = box
    return (round(x + w / 2), round(y + h / 2))

def midPoint(box1, box2):
    x1, y1 = centrePoint(box1)
    x2, y2 = centrePoint(box2)

    return ( round((x1 + x2)/2), round((y1 + y2)/2) )


def init(config):
    global camera
    global cvsink
    global outputStreamStd
    
    camera = CameraServer.getInstance().startAutomaticCapture(name="Vision", path=config["path"])
    camera.setResolution(height, width)

    cvsink = CameraServer.getInstance().getVideo()
    outputStreamStd = CameraServer.getInstance().putVideo("Gray", height, width)

def run():
    global cvsink
    global source
    global output
    global outputStreamStd

    # Read frame from camera
    time, source = cvsink.grabFrame(source)


    if time == 0:
        # outputStreamStd.notifyError(cvsink.getError())
        return
    # cv2.cvtColor(source, output, cv2.COLOR_BGR2GRAY)

    # hsv = cv2.cvtColor(source, cv2.COLOR_BGR2HSV)

    # lower_green = np.array([0, 89, 190])
    # upper_green = np.array([180, 255, 255])

    # mask = cv2.inRange(hsv, lower_green, upper_green)

    # res = cv2.bitwise_and(source, source, mask=mask)
    output = source

    # # Convert to hsl
    # hsl = cv2.cvtColor(source, cv2.COLOR_BGR2HLS)

    # # Green
    # # 35 0   50
    # # 80 255 255

    # # From ChickenVision
    # lower_green = np.array([40, 75, 75])
    # upper_green = np.array([96, 255, 255])

    # # lower_green = np.array([63, 55, 168])
    # # upper_green = np.array([96, 161, 255])

    # mask = cv2.inRange(hsl, lower_green, upper_green)

    # # raw_cnts = cv2.bitwise_and(source, source, mask=mask)
    # _, cnts, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

    # boxes = []

    # for cnt in cnts:
    #     # cv2.drawContours(output, cnt, -1, (255, 0, 0), 3)
    #     boxes.append(cv2.boundingRect(cnt))
    
    # boxes = sorted(boxes, key=lambda x: (x[2] + x[3]), reverse=True)
    # boxes = boxes[:2]

    # for box in boxes:
    #     x, y, w, h = box
    #     if w+h < cutoff:
    #         continue
    #     cv2.rectangle(output, (x, y), (x + w, y + h), (0, 0, 0), 5)
    
    # # Draw line and target
    # if len(boxes) >= 2:
    #     cv2.line(output, centrePoint(boxes[0]), centrePoint(boxes[1]), (255, 0, 0), 3)
    #     midx, midy = midPoint(boxes[0], boxes[1])
    #     cv2.line(output, (midx, midy - 10), (midx, midy + 10), (0,0,255), 1)
        

    # # Display crosshair
    # cv2.line(output, (round(width / 2), round((height / 2) - 20)), (round(width / 2), round((height / 2) + 20)), (0, 255, 00), 3)  # centre
    # cv2.line(output, (round(width / 2) - 30, round((height / 2) - 10)), (round(width / 2) - 30, round((height / 2) + 10)), (255, 0, 00), 3)  # centre
    # cv2.line(output, (round(width / 2) + 30, round((height / 2) - 10)), (round(width / 2) + 30, round((height / 2) + 10)), (255, 0, 00), 3) # centre
    # # cv2.line(output, (round((width / 2) - 20), round(height / 2)), (round((width / 2) + 20), round(height / 2)), (0, 255, 00), 3) 


    # # Display time in bottom left
    # # clock = str(datetime.timedelta(seconds=pytime.time())).split(", ")[1].split(".")[0]
    # clock = pytime.strftime("%I:%M:%S")
    # cv2.putText(output, clock, (10, height - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    
    

    # Send frame over network
    outputStreamStd.putFrame(output)

if __name__ == "__main__":
    config_path = "/boot/frc.json"

    if len(sys.argv) == 2:
        config_path = sys.argv[1]

    config = json.load(open(config_path))
    init(config["cameras"][0])

    while True:
        run()