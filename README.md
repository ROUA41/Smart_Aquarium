# Smart_Aquarium
Design and creation of a Smart Aquarium for mobile app

The data flow occurs as follows: sensors collect environmental data, the DHT11 sensor captures the external temperature and humidity, the DS18B20 temperature sensor measures the water's internal temperature, the water level sensor detects the water level, the soil sensor captures the aquarium's soil moisture, and the LDR light sensor detects light. In case of darkness, it will turn on the LED, and the LCD display will show us the values captured by these sensors. The ESP32 retrieves this data and sends it via the Wi-Fi network to the Blynk server. The server stores the data in a database and makes it available for the mobile application. The application connects to the server to retrieve the data and provides a user-friendly interface for monitoring and controlling the smart aquarium.

![WhatsApp Image 2023-05-27 à 10 00 39](https://github.com/ROUA41/Smart_Aquarium/assets/147992127/c506ba65-7358-47b3-b31b-051d53b2738a)
![image](https://github.com/ROUA41/Smart_Aquarium/assets/147992127/5918a21c-193d-484f-9fad-30d8ee000a9a)
![image](https://github.com/ROUA41/Smart_Aquarium/assets/147992127/a5e54c12-08a9-4f83-8c15-14ccc5d93ec9)
![image](https://github.com/ROUA41/Smart_Aquarium/assets/147992127/a11415e7-d57a-43df-a6dc-52860ee507e2)



