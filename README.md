<h1>Raspberry Pi Smart Light Controller</h1>
<h6>By: Ben Hastings</h6>
<h2>Overview</h2>
The goal of this project was to create a custom smart light controller to work in my room. I wanted to use what 
I've learned in class to control my lights over the wifi so I used a Raspberry Pi to accomplish this. I hosted a 
web server on the Raspberry Pi and created a light controller in C to manage the GPIO pins. To manage the server 
I wrote shell scripts to check the server and ensure it is properly running.
<h2>Usage</h2>
The website is straightforward to use, click the colored buttons to change the colors of the lights. You can also set a timer at the bottom 
of the page to have the lights automatically turn off after the amount of time.
<h2>Setup</h2>
After adding the Raspberry Pi to your home wifi, you must find the IP, this can be done by running <tt>ifconig</tt> in the terminal. Now after plugging the Raspberry Pi 
in and giving it about two minutes to boot and properly load the server, you can search <tt>127.0.0.1:5566</tt> but instead of the localhost address input the public IP found 
for your Raspberry Pi.</br>
<h3>Hardware</h3>
I'm currently working on drafting the schematic for the hardware for this project but it will be found here so you can replicate it.
<h3>Crontab</h3>
The following commands must be added to your Raspberry Pi's crontab by using <tt>sudo crontab -e</tt> the sudo makes sure 
the task is added with the proper permissions.
</br><tt>@reboot /home/pi/raspberry_pi_sockets/boot_script.sh /home/pi/raspberry_pi_sockets</tt></br>
<tt>* * * * * /home/pi/raspberry_pi_sockets/initalize_server.sh /home/pi/raspberry_pi_sockets</tt>
