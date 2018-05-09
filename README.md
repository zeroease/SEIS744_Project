# SEIS744_Project
SEIS 744-01 Antonio DiTommaso Class Project
Project NAME: Safety Bear DATE: 05/09/18
There are many Kids that get abducted today, it said that almost 20 thousand children are kidnapped. With the growing number of children that are taken, there must be a solution, the solution is IOT. With IOT, you can create and market a device that can track your location of your child, if he gets abducted, or if you just want to know their location. Safety bear is that IOT solution. It uses a Particle Photon as its core, with added GPS location devices. Although, it is a great idea, the current build is not marketable, it is currently very costly and bulky, and is only available currently on WIFI. Cellular option can be added later, but cost do go up, about .40cent per megabyte. This is my attempt to create a basic idea of an IOT class, I research many topics, and I reference most my code comes from two websites: 

https://www.particle.io/products/hardware/asset-tracker/
https://www.hackster.io/Richa1/kid-tracker-1b58c9

How the Project works:
There are two interfaces, a web app that allows you to click on a radio button that send a specific value to the particle. In this example, SafetyBearWebapp.html, it allows you to send to commands, one that turns on the GPS, and flashes red, and one to turn off the GPS, and flashes green. The next interface is a button that is connected to D5 on the particle, by clicking this, it starts the GPS, and flashes red.

Materials needed:

Particle Maker Kit

Eztronics Corp Ublox NEO-6M GPS Module Aircraft Flight Controller

Adafruit 12 RGB LED Neopixel Ring

Taoglas PC104.07.0165C High Performance Cellular

Bear Bookbag

