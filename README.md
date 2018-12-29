#**Light Master 3000**

##Folder Descriptions:

*	src - arduino code for this project
*	models - svg and stl files for the enclosure
*	docs - circuit diagrams, documentation, etc.

##README Contents:

*	Inspiration and Objectives
*	Parts List
*	Tools List
*	Instructions

##Inspiration and Objectives

My son loves it when we change the color of our LIFX bulbs with Alexa.  He jumps up and down and shouts out the next color he wants to see.  This is fine, except it doesn't give him the power to change the colors on his own.  As a toddler, he can't quite articulate "Alexa, turn the basement lights red."  This wouldn't be a problem if it didn't mean an adult unit is tied up relaying orders like the second in command of a submarine (apologies to any submariners, I don't know if you actually relay orders) so he can get his RGB fix.

While clearly articulating instructions to a voice assistant isn't his strong suit, my son can push buttons like no other and I knew a custom remote would be right up his alley.  A quick DuckDuckGo search later and I found that LIFX has a developer portal and an API available that would give me a way to bestow upon him the power over lighting he craved.  At the same time, I wouldn't be doing my parental duty if I didn't at least try to make this an educational experience as well.  I decided that this would be a good opportunity to start teaching him about primary colors and how mixing them create the secondary colors.

Finally, I wanted to actually finish this project (I have many projects just short of finished) and share it with the maker community.  

So, objectives for this build are as follows:

*	Fun and educational toy for my son.
*	Fun and educational build for myself.
*   Finish and publish the project.

##Parts List

*	[Adafruit Feather HUZZAH with ESP8266](https://www.adafruit.com/product/2821)
*	[NeoPixel Ring - 16 x 5050 RGB LED with Integrated Drivers](https://www.adafruit.com/product/1463)
*   [Arcade Button - 30mm Translucent Clear](https://www.adafruit.com/product/471)
*	[Arcade Button with LED - 30mm Clear](https://www.adafruit.com/product/3491)
*	[Arcade Button with LED - 30mm Red](https://www.adafruit.com/product/3489)
*	[Arcade Button with LED - 30mm Blue](https://www.adafruit.com/product/3490)
*	[Arcade Button with LED - 30mm Yellow](https://www.adafruit.com/product/3488)
*	[Lithium Ion Polymer Battery - 3.7v 2500mAh](https://www.adafruit.com/product/328)
*	[Breadboard-Friendly 2.1mm DC Barrel Jack](https://www.adafruit.com/product/373)
*	[5V 2A \(2000mA\) switching power supply - UL Listed](https://www.adafruit.com/product/276)
*	[Adafruit Perma-Proto Half-sized Breadboard PCB](https://www.adafruit.com/product/1609)
*	[22AWG Stranded Core Wire](https://www.adafruit.com/product/3111)
*	[Heat Shrink Tubing](https://www.microcenter.com/product/391381/black-assorted-sizes-6-heat-shrink-tubing-assortment)

##Tools List

*	3D Printer
*	Soldering Iron & Solder
*	Heat Gun

##Instructions

###Hardware Internals

If this is your first time using the Adafruit Feather HUZZAH ESP8266, I suggest following their excellent overview documentation located [here](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/) to get setup.  This will take you through the general features of the board, how to solder headers (you need male headers for this project), and getting your Arduino IDE configured to flash code.  Note: you can skip the section on NodeMCU Lua as it is not used in this project.

My other recommendation around hardware is to "pre-fit" the components and connect them according to the diagram below without soldering anything.  You can do this with a breadboard, breadboard jumpers, and alligator clips.  This way you can make sure everything works prior to making connections that are more difficult to remove/redo if you find you have a faulty component or misread the wiring diagram.

![Circuit diagram](http://jasonsankovitch.com/wp-content/uploads/2018/12/lm3000_fritz_diagram.png)

###Prep the Software

If you don't have one already, you will need to create a LIFX developer account (don't worry, it's free).  To do so, go to the [LIFX Developer Zone page](https://community.lifx.com/) and click on "Sign Up."  You will also need a LIFX Cloud account (I don't know why they are separate) through your LIFX app.  Once you've setup your Cloud account, log in [here](https://cloud.lifx.com/), click on your email address, and select Settings.  You should see a section called "Personal access tokens."  Click the button to "Generate New Token," type a descriptive name in the text field, and hit "Generate."  Copy and paste the string that pops up and save it to a secure location.  This collection of numbers and letters is your access token and you cannot get it again after you refresh or leave this page.  The only action you will be able to take with it at a later time is to revoke the token (which is why it's important to name it something appropriate).

Clone to this repository to a local working directory.  Rename lightMasterConfig-Sample.h to lightMasterConfig.h and add values for the following fields (do not remove the quotation marks):

* SSID - the SSID of the wifi network you want to connect to.
* SSID_PASSWORD - password for the above wifi network.
* AUTH_TOKEN - the access token you generated at the beginning of this section.
* LIFXSELECTOR - how you tell LIFX which light/s you want the LM3000 to control.  Documentation [here](https://api.developer.lifx.com/docs/selectors)

Once you've updated the values, load the lightMasterMain.ino file into the Arduino IDE you configured earlier and flash the code to your board.  If you've setup both the config file and hardware correctly, you should see the neopixel ring light up in red, green, and blue and then all white once it's connected to your specified wifi network.  If the ring is unable to connect to the specified wifi, the ring will not turn white.

![RGB Button at Startup](http://jasonsankovitch.com/wp-content/uploads/2018/12/rgbButtonStartup.gif)

Once the button ring has gone white, you're good to test.  Each of the color buttons (and the non-center white) will cause the ring in the center to change.  If the ring is white when a button is pressed, it will change to be that color.  If the center ring is a primary color and a different primary color is pressed, the ring will become the secondary color that results from mixing the primary colors.  If white is pressed, the center ring will reset.

Insert gif of the colors being demonstrated.

To change the lights, you simply press the middle button when the ring is the color you want.

Insert gif of light changing.

If everything is working as expected, you're good to move on to creating the enclosure.

###Printing the Enclosure

STL files in the models folder of this repo as well as on Thingiverse here.  Printed without supports.  20% infill for all but the translucent button which is 100% infill.

https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/using-arduino-ide

https://github.com/Microsoft/vscode-arduino



###Bringing it Together

##Lessons Learned

* Use the LED mini arcade buttons.