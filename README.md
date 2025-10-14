# PCnunchuck
A full start-end 3d printing project for a nunchuck using an arduino micro.
![Image of a Nintendo Switch Themed Arduino-PowerdNunchuck](https://github.com/MassiveZappy/PCnunchuck/blob/main/img.jpg?raw=true)
- Weekly - Bi-weekly updates! (Don't quote me on this!)

# Models Exported from Blender-3.3
- Models are all very unrefined. Dremmel/sanding REQUIRED.
- Mileage/quality WILL VARRY!
- Printed on a X1C from bambu labs using Bambu labs red and green pla and matt blue.

## Parts:
- Hot glue gun
- PS3 joystick (More info avalible later)
- arduino micro
- USB-B/C to USB-B Micro cord (no, this gets used too, not just for programming arduinos)
- Two push buttons (I salvaged mine from a broken mouse) [M187](https://www.logitech.com/en-us/products/mice/m187-mini-wireless-mouse.910-005360.html) might work
- 170 pin for arduino micro Breadboard, 17x5x2
- 3 LEDS (Green, Yellow, Red)
- 220 Ohm Resistor
- One of each printed part. Look

### For The buttons:
You will need to print many of these in different scales. It varrys greatly. Sorry! Some sizes that worked for me:
- C button ~110%
- Z button ~97%

## How to put together:
You may need to dissconnect and reconnect manny things while doing this.
1. Hot hot glue top push button in place on right half.
2. Hot hot glue bottom push button in place on left half.
3. Thread the top cable up and to the verry top of the casing and behind the joystick.
4. Put the [breadboard](#Breadboard) in the right half and glue/stick/both it in place. make sure that the USB connection is facing the hole in the back. also pu this far enough forward so that you can bend the usb cable into the 5mm hole in the back of the shell. If your cabble is thicker/don't bend, sand the model down untill it exits the back.
5. Thread the bottom cable through the bottom hole on the right half.
6. Connect everything.
7. Glue the joystick in place on the Left half. Try you best to center the holes in the model with the joystick.
8. Connect the micro to your computer via the usb cable. Upload the Check.ino sketch! If everything works (buttons, joystick, leds) you did it right!
9. Keep the arduino connected and slowly close the casing. Leave about a centimeter of clearance before closing it.
10. Put the two button caps (Z and C) into place and use hot glue to hold them to the left side of the model temporarily. Make sure this is on the OUTSIDE of the shell!
11. Making sure the usb is till connected to the micro thred it through the hole in the back and glue it in place. 
12. Put glue on the joystick's oppisite side where it will cotact the model and seal it shut. 
13. Sand and dremmel any extra hot glue off the keycaps. Verrify they move and feel "clicky"
14. Glue the split arround the edge if the model.
15. Sand and dremmel any extra hot glue off the model. refine the look
16. Upload the nunchuckMicro.ino to it.
17. DONE! Submit a pull request to conttribute to the code and check back every so often for any firmware updates! You should now have a mouse/keyboard as a wii nunchuck!
### Breadboard
- Arduino uno in the center
- Connect these to these pins
    * Joystick:
        * joystick xPos --> A0
        * joystick yPos --> A1
        * joystick SW --> pin 4
        * Joystick VCC --> 5v
        * Joystick GND --> GND
    * Buttons:
        * button Z lead 1 --> pin 2
        * button Z  lead 2 --> GND
        * button C lead 1 --> pin 3
        * button C lead 2 --> GND
    * LEDS:
        * LED postive (long) leads (+):
            * Green LED --> 10
            * Yellow LED --> 11
            * Red LED --> 12
        * LED negative (short) leads (-):
        * 220 Ohm Resistor on one side
    *  220 Ohm Resistor connects one end to GND and other to all 3 LEDS

