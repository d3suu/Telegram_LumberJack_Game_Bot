import cv2
import numpy as np
from PIL import ImageGrab
import time
from pyautogui import press
import keyboard

ver = 2

# Ekran:
# https://stackoverflow.com/questions/49479552/imagegrab-grabbbox-and-image-getpixel-used-together
# https://www.pyimagesearch.com/2021/01/20/opencv-getting-and-setting-pixels/

# Klawiatura:
# https://stackoverflow.com/posts/43567521/revisions

# Tylko Red dla sprawdzenia czy jest galaz
galaz = 56
galaz = 161 # bez filtra (Blue)
darkGalaz = 136 # bez filtra (Blue)

keyboardSleep = 0.0406 # Ver 3
keyboardSleep = 0.06
stepSleep = 0.107 # Ver 3
stepSleep = 0.12

nextStep = ['l','r']

# Poprawne koordynaty dla ekranu 1680x1050 na windowsie
# bbox=((1680/2)-100,(1050/2)-25,(1680/2)+100,(1050/2)-20)

# Zaczekaj na focus na okno
if ver>0:
    img = ImageGrab.grab(bbox=((1680/2)-100, 50,(1680/2)+100,(1050/2)+100))
    img_np = np.array(img)
    cv2.imshow("test", img_np)
    cv2.waitKey(1)
    print("Czekam na focus...")
    time.sleep(7)
    print("3...")
    time.sleep(1)
    print("2...")
    time.sleep(1)
    print("1...")
    time.sleep(1)

# Poczatkowo dwa razy gdziekolwiek
#press("left")
#press("left")
while ver == 1:
    # Pobierz obraz
    time.sleep(0.1)
    img = ImageGrab.grab(bbox=((1680/2)-100,(1050/2)-25,(1680/2)+100,(1050/2)-20))
    img_np = np.array(img)
    img_new = cv2.cvtColor(img_np, cv2.COLOR_BGR2RGB)
    #cv2.imshow("test", img_new)
    #cv2.waitKey(1)
    #print("Left: " + str(img_new[0,0+20]) + " Right: " + str(img_new[0,200-1-20]))
    # Sprawdz strone
    if(img_new[0,0+20][0] == galaz):
        print("Galaz po lewej stronie")
        nextStep[0] = nextStep[1]
        nextStep[1] = 'r'
    else:
        print("Galaz po prawej stronie")
        nextStep[0] = nextStep[1]
        nextStep[1] = 'l'
    # Wydaj polecenie
    if nextStep[0] == 'l':
        #press("left")
        #press("left")
        keyboard.press_and_release('left')
        time.sleep(0.05)
        keyboard.press_and_release('left')
        time.sleep(0.05)
    else:
        #press("right")
        #press("right")
        keyboard.press_and_release('right')
        time.sleep(0.05)
        keyboard.press_and_release('right')
        time.sleep(0.05)

while ver == 2:
    # Pobierz obraz
    time.sleep(stepSleep)
    img = ImageGrab.grab(bbox=((1680/2)-100, 50,(1680/2)+100,(1050/2)+100))
    img_new = np.array(img)
    #img_new = cv2.cvtColor(img_np, cv2.COLOR_BGR2RGB)
    #cv2.imshow("test", img_new)
    #cv2.waitKey(1)
    # Skanowanie
    galezie = [img_new[50-1, 155-1][0],
               img_new[150-1, 155-1][0],
               img_new[250-1, 155-1][0],
               img_new[350-1, 155-1][0],
               img_new[450-1, 155-1][0],
               img_new[550-1, 155-1][0]]
    for x in galezie[::-1]:
        if x == galaz:
            #print("Galaz po prawej")
            #press("left")
            #press("left")
            keyboard.press_and_release('left')
            time.sleep(keyboardSleep)
            keyboard.press_and_release('left')
            time.sleep(keyboardSleep)
        else:
            #print("Galaz po lewej")
            #press("right")
            #press("right")
            keyboard.press_and_release('right')
            time.sleep(keyboardSleep)
            keyboard.press_and_release('right')
            time.sleep(keyboardSleep)

while ver == 3:
    # ~~Srednia wartosc z boxow na drzewach~~
    # Znajdz galaz jeszcze podczas animacji opadania
    # Pobierz obraz
    time.sleep(stepSleep)
    img = ImageGrab.grab(bbox=((1680/2)-100, 50,(1680/2)+100,(1050/2)+100))
    img_new = np.array(img)
    #img_new = cv2.cvtColor(img_np, cv2.COLOR_BGR2RGB)

    cv2.imshow("test", img_new)
    #cv2.waitKey(10000)
    cv2.waitKey(1)
    # Skanowanie
    base = 47
    offset = 0
    for x in range(0,80):
        if img_new[base-x-1, 155-1][0] == galaz or img_new[base-x-1, 155-1][0] == darkGalaz or img_new[base-x-1, 40-1][0] == galaz or img_new[base-x-1, 40-1][0] == darkGalaz:
            offset = x
            break
        
    galezie = [img_new[base-offset-1, 155-1][0],
               img_new[100+base-offset-1, 155-1][0],
               img_new[200+base-offset-1, 155-1][0],
               img_new[300+base-offset-1, 155-1][0],
               img_new[400+base-offset-1, 155-1][0],
               img_new[500+base-offset-1, 155-1][0]]
    
    # DEBUG - Pokaz wartosc podczas wywalenia sie na przelocie
    #print("DEBUG: " + str(img_new[47-1, 40-1][0]) + " " + str(img_new[47-1, 155-1][0]))
    print("DEBUG: " + str(offset))
    
    for x in galezie[::-1]:
        if x == galaz or x == darkGalaz:
            #print("Galaz po prawej")
            #press("left")
            #press("left")
            keyboard.press_and_release('left')
            time.sleep(keyboardSleep)
            keyboard.press_and_release('left')
            time.sleep(keyboardSleep)
        else:
            #print("Galaz po lewej")
            #press("right")
            #press("right")
            keyboard.press_and_release('right')
            time.sleep(keyboardSleep)
            keyboard.press_and_release('right')
            time.sleep(keyboardSleep)

while ver == -1:
    # Centrowanie
    time.sleep(0.06)
    img = ImageGrab.grab(bbox=((1680/2)-100, 50,(1680/2)+100,(1050/2)+100))
    img_new = np.array(img)
    #img_new = cv2.cvtColor(img_np, cv2.COLOR_BGR2RGB)
    cv2.imshow("test", img_new)
    cv2.waitKey(1)
    # Skanowanie
    galezie = [img_new[50-1, 155-1][0],
               img_new[150-1, 155-1][0],
               img_new[250-1, 155-1][0],
               img_new[350-1, 155-1][0],
               img_new[450-1, 155-1][0],
               img_new[550-1, 155-1][0]]
    for x in galezie:
        print(x)
        if x == galaz:
            print("Galaz po prawej")
        else:
            print("Galaz po lewej")
    time.sleep(60)
