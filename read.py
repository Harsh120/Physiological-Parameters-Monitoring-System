import requests
import re
import json
import urllib.request
#from rsaa import decrypt
from crypto import decryption

def decrypt(list):
    new_list = []
    for i in list:
        encoded = i.encode()
        a = decryption(encoded)
        new_list.append(a)
    return new_list

try:
    temp_data= urllib.request.urlopen("https://api.thingspeak.com/channels//fields/1.json")
    pulse_data = urllib.request.urlopen("https://api.thingspeak.com/channels//fields/1.json")
    motion_data = urllib.request.urlopen("https://api.thingspeak.com/channels//fields/1.json")
except:
    print("Check your Internet Connection")

x = temp_data.read().decode('utf-8')
y = pulse_data.read().decode('utf-8')
z = motion_data.read().decode('utf-8')

temp_data = json.loads(x)
pulse_data = json.loads(y)
motion_data = json.loads(z)

last_entry = pulse_data['channel']['last_entry_id']
i = last_entry

temp_feeds = temp_data['feeds']
temp_feeds = temp_feeds[::-1]
temp = []

pulse_feeds = pulse_data['feeds']
pulse_feeds = pulse_feeds[::-1]
pulse = []

motion_feeds = motion_data['feeds']
motion_feeds = motion_feeds[::-1]
size = len(motion_feeds)
motion = []

for i in range(size):
    if last_entry-10>i:
        break
    temp.append(temp_feeds[i]['field1'])
    pulse.append(pulse_feeds[i]['field1'])
    motion.append(motion_feeds[i]['field1'])
    

temp = decrypt(temp)
pulse = decrypt(pulse)
motion = decrypt(motion)

print("Temperature (in Celcius) ",temp)
print("Pulse (in BPM) ",pulse)
print("Motion (lower the value, lower the motion) ",motion)
    
