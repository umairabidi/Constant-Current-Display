# Constant-Current-Display

A common tool used by electrical engineers is the electronic load - also known as a dummy load or a constant current load. The purpose is to draw a set amount of current from a circuit, usually to test power supplies or other circuitry. 

I made one such electronic load using only a few components. A resistor and an opamp in negative feedback operation allows us to apply a constant voltage to a power resistor. The current flowing through this resistor is being drawn from the external circuit that we are loading. By then measuring the voltage across that resistor (and knowing the value of the resistor), we can easily calculate that current. The resistor should be a power resistor type. You decide how much power it should be capable of dissipating, but at least 3 watts is a good starting point.

A MOSFET is also important if you want more than a few hundred milliamps. The MOSFET will be dissipating quite a bit of power, so it should be mounted on a heatsink. My current design has a CPU heatsink with a fan attached to it. This setup is good for probably 50 W or more, but it heavily depends on the MOSFET you use and the voltage of your external circuit. Important parameters are the power dissipation it can handle as well as its operating region (found in the datasheet). 

Two things must first be measured before you use the device. First is the voltage from the on-board voltage regulator which defines the reference voltage for the microcontroller. Assuming that each regulator has a slightly different offset from the ideal value, this only needs to be measured once. Small variations due to the supply voltage can probably be ignored.

More significantly, the value of the current sense resistor be measured. This is most easily done by using trusted power supply in constant current mode, and sending that current into the resistor. Measuring the voltage across the resistor can give a reasonably accurate value for its resistance. Of course, several measurements should be repeated to reduce inaccuracies.

The voltage across the resistor is controlled with a potentiometer. Therefore, we have a continuously adjustable constant-current electronic load. 

This program calculates the current flowing through the circuit based on these two parameters that must be inputted into the code. It then displays the current with three significant figures onto a 3 digit 7-segment display. 
