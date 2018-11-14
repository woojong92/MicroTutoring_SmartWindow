#from __future__ import print_statement
import artikcloud
from artikcloud.rest import ApiException
from pprint import pprint
import serial
import time

ser=serial.Serial('/dev/ttyACM0',9600)

# Configure OAuth2 access token for authorization: 
artikcloud.configuration.access_token = 'cf6aabd72ee34bae9b61f669e2d81bc'

device_sdid='fec58c053b124de2b42ad940570c5fab'
ts=None


while True:
    ser_data=ser.readline()
    
    sp_data=ser_data.split("|")

    #dust=float(sp_data[1])+1
    #rain=sp_data[2]
    #gas=int(sp_data[3])+1
    #cds=(sp_data[4])+1

    message={'dust': float(sp_data[1]), 'rain': sp_data[2], 'gas': int(sp_data[3]), 'brightness': int(sp_data[4])}
    # create an instance of the API class
    api_instance = artikcloud.MessagesApi()
    data = artikcloud.Message(message, device_sdid, ts) # Message | Message object that is passed in the body

    try:
        # Send Message
        api_response = api_instance.send_message(data)
        pprint(api_response)
    except ApiException as e:
        print("Exception when calling MessagesApi->send_message: %s\n" % e)

    time.sleep(20)