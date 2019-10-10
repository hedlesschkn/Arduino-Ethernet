# Arduino-Ethernet
connecting an arduino to the internet at Brandeis  
By Tim Hebert  

using EtherenetGet program
talking to pushingbox.com's API system
limited to 100 API requests per day
option 1:
  1440 minutes per day, send one request per minute
  don't send data when all 0's, assume always at least 7.33 hours of down time daily (library closed)
  problem: if a sensor false triggers, we can't track more than 1000 requests and may lose valueable data
  if we want to grow the system and send data with sensors that matter outside of human hours (temp, gas, smoke) we lose data

option 2:
  1440 minutes per day, send one request every 2 minutes = 720 daily requests
  example API message: http://api.pushingbox.com/pushingbox?devid=v9A1CFE5F18FECCE&humidityData=33&celData=44&fehrData=111&hicData=22&hifData=77
  60 chars for api and device id
  & sensorname = is a minimum of 3 chars, realistically allow 3 chars for just the name is 5 chars per sensor
  data for a PIR sensor (boolean) polled once per second over a 2 minute period is 120 bits BINARY, 16 chars HEX
    total 125 binary chars, 21 HEX chars per sensor
  URL limit is about 2000 chars - 60 = 1940
  1940/125 = 15 bool sensors
  1940/21 = 92 bool sensors

2 2d arrays 
one is 3*4 which is name of each sensor 3 strings of 4 sensors each
next is a 12 by 4 array
  12 sensors each with 4 32 bit unsigned longs to make up 120 bits
  convert to HEX which is a byte per char
  use sprintf to convert to a string to then send to pushingbox.
