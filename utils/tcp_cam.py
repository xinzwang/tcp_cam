# Github: https://github.com/xinzwang

import socket
import numpy as np
import cv2
import time

T = 1.2


at = time.time()


def tcp_frame():
    global at
    ct = time.time()
    if (at + T) > ct:
        time.sleep(at+T-ct)
    at = time.time()

    BUFFER_SIZE = 50*1024*1024

    TCP_TEST = bytes.fromhex('00')
    TCP_CAM_STOP = bytes.fromhex('01')
    TCP_CAM_START = bytes.fromhex('02')
    TCP_CAM_DATA = bytes.fromhex('03')
    TCP_ISP = bytes.fromhex('04')

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # s.connect(('FE80:0:0:0:20A:35FF:FEA0:102', 7))

    print("Try to connect ...", end='')
    s.connect(('10.104.9.156', 7))
    print("    conn success!")

    s.send(TCP_CAM_STOP)
    rsp = s.recv(BUFFER_SIZE)
    print(rsp)

    rsp_len = 0
    rsp_buffer = bytes(0)

    print("    start trans")
    while rsp_len < 1152000:
        req = bytearray(2)
        req[0] = 3
        req[1] = 0

        try:
            s.send(req)
            rsp = s.recv(BUFFER_SIZE)
        except Exception as e:
            print(e)

        rsp_len += len(rsp)
        rsp_buffer += rsp

        # print(f'sum_len:{rsp_len}  pkg_len:{len(rsp)}')
    print("trans frame finish")

    try:
        s.send(TCP_CAM_START)
        rsp = s.recv(BUFFER_SIZE)
        # print(rsp.decode())
    except Exception as e:
        print(e)
        print(rsp)
        exit(-1)

    img = np.frombuffer(rsp_buffer[0:1152000],
                        dtype=np.uint8).reshape(480, 800, 3)
    return img


cv2.VideoCapture()
while True:
    st = time.time()
    img = tcp_frame()
    et = time.time()

    print(f' IMG time:{et-st}')

    cv2.imshow('tcp camera', img)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        self.outVideo.release()
        self.cap.release()
        cv2.destroyAllWindows()
        break
        # continue
