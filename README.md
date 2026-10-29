# PIE-3D-Scanner

For mini-project 2, we were tasked with building a 2.5 dimension scanner using an arduino, two servo motors, and an IR sensor. The scanner had to use a pan and tilt mechanism to scan an object of known geometry, then transmit the sensor readings to create a visualisation of the object on software such as MATLAB or Python. The sensor used in this project was an infrared distance sensor. 

To accomplish this task, we created a pan and tilt mechanism on CAD and then 3D printed it using the Original Prusa MK4S 3D printers with PLA filament. Next, we calibrated the sensor by taking different distances and finding the assigned voltage to create a translation equation to find the distance. Then, we took the raw data of the translated distance, pan angle, and tilt angle and uploaded it to MATLAB. Using trigonometry, we were able to find the X, Y, and Z distances to actually plot the image.
