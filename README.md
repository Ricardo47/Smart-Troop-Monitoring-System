# Smart-Troop-Monitoring-System
This is a project which I submitted for the final semester of my engineering. 
This includes IoT platform BLYNK application for the final analytics of all the data coming from the individual NodeMCU E12.
The server file is the code for the server NodeMCU which first receives data from the station NodeMCU and then send both NodeMCU's data over to Blynk app.
The station file is the code for the station NodeMCU which sends data to the server NodeMCU over Wi-Fi through HTTP protocol.

Sensors interfaced with each NodeMCU: Pulse Sensor and DS18B20 temperature Sensor.

Note: This is a code for both server and station NodeMCUs with pulse and temperature sensor. Furthermore, a GPS module was interfaced with Server NodeMCU and an HTML page was created to track the location data real time and Google Maps API was used to see it on Google Maps. A push button was used with Vibration Motor to act as an alarm for some uncertainity when the button was pressed so that the soldier would have been notified.

Thank you.
