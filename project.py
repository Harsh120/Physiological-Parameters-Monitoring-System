import serial
import requests
import re
from urllib.request import urlopen
from time import sleep
#from rsaa import encrypt
from crypto import encryption

baud_rate = 9600; #In arduino, Serial.begin(baud_rate)
write_to_file_path = "output.txt";

    
output_file = open(write_to_file_path, "w+")
ser = serial.Serial('com4', 9600)
i=0
baseURLtemp = 'https://api.thingspeak.com/update?api_key=VVVT6G6HVKXUOO8J&field'
baseURLpulse = 'https://api.thingspeak.com/update?api_key=MS8P87GYK43D0U5Z&field'
baseURLmotion = 'https://api.thingspeak.com/update?api_key=27BD9ZQZDLWDAXEC&field'
while True:
    print(' ')
    line = ser.readline().decode('utf-8').strip()
    i=i+1
    if(i==1):
        temp = re.split(r'\s',line)
        temp = temp[2]
        tempEncrypt = (encryption(temp)).decode()
        url1 = baseURLtemp+'1='+tempEncrypt
        requests.get(url1)
        print(temp)
        sleep(5)
    elif(i==2):
        pulse = re.split(r'\s',line)
        pulse = pulse[2]
        pulseEncrypt = (encryption(pulse)).decode()
        url2 = baseURLpulse+'1='+pulseEncrypt
        requests.get(url2)
        print(pulse)
        sleep(5)
    elif(i==3):
        motion = re.split(r'\s',line)
        motion1 = motion[1]
        motionEncrypt = (encryption(motion1)).decode()
        url3 = baseURLmotion+'1='+motionEncrypt
        requests.get(url3)
        print(motion1)
        sleep(5)
    elif(i==4):
        i=0
            


