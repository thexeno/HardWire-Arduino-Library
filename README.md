# HardWire Arduino Library V1.0.2

*Licensing information is attached on the header of each file.*

This is an I2C Arduino library, *completely equivalent* to the Arduino Wire lib, but with more functionality. This gives more control 
at the lower layer of the I2C protocol, without affecting the simplicity of the original library.


With the conventional Wire library, you can take action only after the STOP or when addressed as a  Slave Transmit. In Hard Wire,
the user can take a custom action in the following I2C states:

- Addressed in slave read mode
- Addressed in slave write mode
- ACK received after every byte sent
- NACK received after byte is sent
- ACK sent
- START
- STOP
- RESTART


As a result, the user can take action at each step, in real time, of the I2C bus cycle where an example is depicted here below:

   ![alt tag](https://enricosanino.files.wordpress.com/2016/11/command.gif)

## How to use it

The HardWire lib instantiates a **Wire** object, so that if in the code were previously used the Wire, no changes are required, except for the header, which shall be "HardWire.h" instead of "Wire.h".
When referring to the "data buffer" or "shared buffer", it is intended the buffer handled by the Wire, accessed only using the API from the Wire or HardWire library, which are the same.

Basically you can follow the official [Wire guide](https://www.arduino.cc/en/Reference/Wire), but also [another description of the HardWire here](https://enricosanino.wordpress.com/2016/11/19/hardwire-the-enhanced-arduino-wire-library/). 
Here will be described only the differences between the original *Wire* and the *HardWire*, everything else is compliant with the guide linked above to the Wire.

### Handlers
This "hardened" (or more "hardware", "hardwired") version also supports the following handlers assigned during the initialization (are listed also the official ones). **Note that the use of the additional HardWire handlers is *never*  mandatory.**

- ***Officials from original Wire***

 - **Wire.onReceive(myHandler)** -> handler takes the number of bytes received and returns void. In the handler the data buffer can be read, since the master has terminated the communication
 ```
 i.e.  void myHandler(int numBytes)
 ``` 
 - **Wire.onRequest(myHandler)** -> handler takes no parameters and returns void. It is called to notify the slave to prepare data to be sent using the standard Wire methods available, like read() and write()
 ```
 i.e. void myHandler()
 ```
- ***New in the HardWire***

 - **Wire.onReceiveData(myHandler)** -> handler takes as a parameter the last received byte and returns void. It is used for the slave runtime computation, but the data buffer is still filled with that byte, as the official Wire does this transparently
 ```
 i.e. void myHandler(unsigned char)
 ```
 - **Wire.onReceiveDataNack(handler)** -> handler takes no parameters and returns void. It is used to notify the slave, since this received byte shall not be used.
 ```
 i.e. void myHandler()
 ```
 - **Wire.onReceiveAdx(handler)** -> handler takes no parameters and returns void. The slave is notified to prepare itself to receive data in the next bus transaction, while in the official Wire it is done transparently since this mode is not exploited.
 ```
 i.e. void myHandler()
 ```
 - **Wire.onRequestData(handler)** -> handler returns a byte to be sent to the master and takes no arguments. This byte can be generated from the slave in the handler at runtime, or using the shared buffer. If not defined, the default behavior of the Wire is implemented (which automatically reads from the previously filled shared buffer).
 ```
 i.e. unsigned char myHandler()
 ```
 - **Wire.onRequestDataNack(handler)** -> handler takes not parameters and returns void. Used when the master still requires data which is not available from the shared buffer. It is done transparently in the official Wire.
 ```
 i.e. void myHandler()
 ```
 

### Initialization
 
 This version supports a particular mode that shall be notified in the init. If omitted, it is initialized as the normal Wire.

- ***New in the HardWire***

 - **Wire.begin(slaveAddress, mode)** -> join the bus as a Slave and
 
    -> if **mode = HARD_WIRE_MODE**, will be supported all the additional handlers, with an undefined (vitually infinite) number of read/write cycles, as any I2C slave device would do.
 
     -> if **mode = NORMAL_MODE**, will be supported all the additional handlers, but when the shared buffer is full, it needs to be flushed or read before accepting any new incoming byte: this behavior is the same as the Wire library.
     


- ***Officials from original Wire***

 - **Wire.begin()** -> join the bus as a Master
 - **Wire.begin(slaveAddress)** -> join the bus as a Slave (additional HardWire handlers are still supported as in **NORMAL_MODE**)
 
 
 
