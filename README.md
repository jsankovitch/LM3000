# **Light Master 3000**

An open source remote control for your LIFX smart bulbs.

## README Contents:

*	Inspiration and Objectives
*	Parts List
*	Tools List
*	Instructions

## Inspiration and Objectives

My son loves it when we change the color of our LIFX bulbs with Alexa.  He jumps up and down and shouts out the next color he wants to see.  This is fine, except it doesn't give him the power to change the colors on his own.  As a toddler, he can't quite articulate "Alexa, turn the basement lights red."  This wouldn't be a problem if it didn't mean an adult unit is tied up relaying orders like the second in command of a submarine (apologies to any submariners, I don't know if you actually relay orders) so he can get his RGB fix.

While clearly articulating instructions to a voice assistant isn't his strong suit, my son can push buttons like no other and I knew a custom remote would be right up his alley.  A quick DuckDuckGo search later and I found that LIFX has a developer portal and an API available that would give me a way to bestow upon him the power over lighting he craved.  At the same time, I wouldn't be doing my parental duty if I didn't at least try to make this an educational experience as well.  I decided that this would be a good opportunity to start teaching him about primary colors and how mixing them create the secondary colors.

Finally, I wanted to actually finish this project (I have many projects just short of finished) and share it with the maker community.  

So, objectives for this build are as follows:

*	Fun and educational toy for my son.
*	Fun and educational build for myself.
*   Finish and publish the project.

## Parts List

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

## Tools List

*	3D Printer
*	Soldering Iron & Solder
*	Heat Gun

## Instructions

### Hardware Internals

If this is your first time using the Adafruit Feather HUZZAH ESP8266, I suggest following their excellent overview documentation located [here](https://learn.adafruit.com/adafruit-feather-huzzah-esp8266/) to get setup.  This will take you through the general features of the board, how to solder headers (you need male headers for this project), and getting your Arduino IDE configured to flash code.  Note: you can skip the section on NodeMCU Lua as it is not used in this project.

My other recommendation around hardware is to "pre-fit" the components and connect them according to the diagram below without soldering anything.  You can do this with a breadboard, breadboard jumpers, and alligator clips.  This way you can make sure everything works prior to making connections that are more difficult to remove/redo if you find you have a faulty component or misread the wiring diagram.

![Circuit diagram](http://jasonsankovitch.com/wp-content/uploads/2019/01/lm3000-curves_bb.png)

### Prep the Software

If you don't have one already, you will need to create a LIFX developer account (don't worry, it's free).  To do so, go to the [LIFX Developer Zone page](https://community.lifx.com/) and click on "Sign Up."  You will also need a LIFX Cloud account (I don't know why they are separate) through your LIFX app.  Once you've setup your Cloud account, log in [here](https://cloud.lifx.com/), click on your email address, and select Settings.  You should see a section called "Personal access tokens."  Click the button to "Generate New Token," type a descriptive name in the text field, and hit "Generate."  Copy and paste the string that pops up and save it to a secure location.  This collection of numbers and letters is your access token and you cannot get it again after you refresh or leave this page.  The only action you will be able to take with it at a later time is to revoke the token (which is why it's important to name it something appropriate).

Clone to this repository to a local working directory.  Rename lightMasterConfig-Sample.h to lightMasterConfig.h and add values for the following fields (do not remove the quotation marks):

* SSID - the SSID of the wifi network you want to connect to.
* SSID_PASSWORD - password for the above wifi network.
* AUTH_TOKEN - the access token you generated at the beginning of this section.
* LIFXSELECTOR - how you tell LIFX which light/s you want the LM3000 to control.  Documentation [here](https://api.developer.lifx.com/docs/selectors).

Once you've updated the values, load the lightMasterMain.ino file into the Arduino IDE you configured earlier and flash the code to your board.  If you've setup both the config file and hardware correctly, you should see the NeoPixel ring light up in red, green, and blue and then all white once it's connected to your specified wifi network.  If the ring is unable to connect to the specified wifi, the ring will not turn white.

Once the button ring has gone white, you're good to test.  Each of the color buttons (and the non-center white) will cause the ring in the center to change.  If the ring is white when a button is pressed, it will change to be that color.  If the center ring is a primary color and a different primary color is pressed, the ring will become the secondary color that results from mixing the primary colors.  If white is pressed, the center ring will reset.

To change the lights, you simply press the middle button when the ring is the color you want.

If everything is working as expected, you're good to move on to creating the enclosure.

### Printing the Enclosure

Printing the enclosure is pretty straight forward.  I used PLA for my build, but any rigid plastic should work.  I suggest using the material you are most comfortable working with as tolerances are fairly important in this build as the enclosure is held together by friction fit parts.

Parts are as follows:

* controller_sled_v1.stl - This is the part that holds the completed circuit board.
* grip_detail_v1.stl - Small pieces that make the grip thicker.  I made these separate parts so they could be printed in different colors.
* housing_base_v1.stl - This is the base of the device and holds the battery, power switch, and the circuit board via the controller sled.
* main_body_v1.stl - This is the upper part of the device.  The buttons and RGB ring are attached to this piece and it slides over the housing base.
* rgb_button_ring_v1.stl - This is the housing for the 16 LED Neopixel we'll use to indicate the color to be sent to LIFX.  It fits into the center of the main body.
* rgb_button_ring_spacer_v1_OPTIONAL.stl - This fits inside the RGB button ring AFTER you place the Neopixel inside if you need something to hold the Neopixel in place.  If the ring is secure without it, you don't have to print it.

All of these parts can be found in the /models directory of this repository as well as on Thingiverse.

I highly recommend printing the controller sled and RGB button ring at 100% infill.  The sled can be a tight fit on the protoboard and one wrong move can snap a part printed with even a fairly moderate level of infill.  The RGB ring will nicely diffuse the Neopixel when printed at 100%.  Any lower, and you'll see the pattern of the infill.

All other items can be printed without supports and at the infill level you prefer.  For my build, I chose 20-30% infill as my son can be rough with toys and I wanted it to survive a drop or two.

![Assembly](http://jasonsankovitch.com/wp-content/uploads/2019/01/LM3000-parts.png)

### Main Body Assembly
1. Super glue the grip detail pieces to the main body.
1. If you didn't already, solder the components to the protoboard, connect power and ground, and solder the three wires (digital in, power, and ground) to the NeoPixel.
1. Press the NeoPixel into the rbg button ring and then install said ring in the center hole leaving about 1/8-1/4 inch protruding from the top of the main body.
1. Solder and heat shrink wrap a wire to the positive lead of each arcade button.  The buttons will share a common ground and be wired in series.  Because of this, you need to wait for them to be installed into the enclosure before soldering.  Make sure you leave plenty of extra wire as you will want slack to enable you to solder the other ends of the wires to the protoboard.

    ![Buttons and wires!](http://jasonsankovitch.com/wp-content/uploads/2019/01/button_wires.jpeg)

1. Install the buttons into the four outer holes.  The color order does not matter.
1. Carefully install the second white arcade button into the RGB button ring.
1. Solder the ground of the buttons in series and then to the protoboard.
1. Solder the wires from steps 2 and 3 to the appropriate spot on the protoboard, making sure they line up with the correct pins on the Feather.
1. If you used buttons with LEDs inside, you can solder them together and then to power at this time.

### Housing Base Assembly
1. Slide the protoboard into the controller sled.  The slot should be closer to the "top" of the sled and the Feather should be visible from the top (see photo).  Be careful with this step - it is easy to break the sled.

    ![Board Installed](http://jasonsankovitch.com/wp-content/uploads/2019/01/board_installed.jpeg)

1. Secure the battery into the base of the enclosure using double sided tape with the wires closer to the middle of the base rather than the edge. 
1. Press the sled into the slots on the base making sure you run the battery wire through the opening behind the protoboard.
1. Connect the battery leads to the Feather board.
1. Press the power switch into the appropriate slots with the switch in the "off" position.
1. Solder the wires from the protoboard to the switch.

## Final Assembly and Testing
1. Plug the power supply into the 2.1mm barrel port and make sure the amber "battery charging" light comes on.
1. Slide the main body over the base, making sure the port openings align, and press together.
1. Turn on the main power switch and you should see the RGB ring light up in rainbow colors and then shift to white once connected to your access point.
1. Once connected, the lights you specified should automatically turn on (assuming they have power).  You should be good to go at this point!

### Lessons Learned

* The height of the buttons required the enclosure to be taller than I would have liked.  I would explore shorter buttons if I were to make this again.
* You can skip a lot of the soldering by using quick connect wires such as [these](https://www.adafruit.com/product/1152).  I would have gone this route were I patient enough to wait for them to arrive.  NOTE: if you leave the JST connectors attached, you will need to change the protoboard layout as it will not work.  I recommend snipping off the JST connectors for simplicity's sake.
* A heat gun will melt PLA.  Quickly.