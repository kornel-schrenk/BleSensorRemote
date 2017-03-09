# BleSensorRemote

For more information please see this blog [post](http://www.schrenk.hu)!

## Description

The [Adafruit Feather 32u4 Bluefruit LE](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/overview) development board provides an easy way to expose physical sensor data to remote devices like mobile phones over the Bluetooth Low Energy (BLE) network.

The Arduino sketch in this repository contains an example about how to make the [SparkFun Pressure Sensor Breakout - MS5803-14BA](https://www.sparkfun.com/products/12909) remotely accessible. In short it works like this:

1. Based on the breadboard view wire the [Pressure Sensor](https://www.sparkfun.com/products/12909) to the [Feather 32u4 Bluefruit LE](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/overview) development board
2. Install the [Adafruit Bluefruit LE Connect](https://play.google.com/store/apps/details?id=com.adafruit.bluefruit.le.connect) app onto your mobile phone
3. Enable Bluetooth on the phone and launch the app
4. Search for the **BleSensor** named bluetooth device
5. Click *Connect*
6. Select *UART* as a connection mode
7. Now you can use the **Communication API** described below to obtain the following sensor data:
  * Temperature in celsius
  * Pressure in millibar
  * Battery charge level in volts

Of course this way other sensors can be attached to the [Adafruit Feather 32u4 Bluefruit LE](https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le/overview) development board. 

## Breadboard view

![alt text](../master/BleSensorRemote_bb.png "Fritzing breadboard view")

## Communication API

```javascript
IN  <-: @TEMP# - Ask for the current temperature
OUT ->: @23.4# - The temperature in celsius

IN  <-: @PRES# - Ask for the current ambient pressure
OUT ->: @1010.3# - The pressure in millibar

IN  <-: @BAT# - Ask for the current battery charge
OUT ->: @4.14# - The current battery charge in volts

IN  <-: @ALL# - Ask for all information
OUT ->: @1009.80,26.07,4.32# - The pressure in millibar, the temperature in celsius and the battery charge in volts
```

Every inbound and outbound message starts with the **@** and ends with the **#** character. 

## Repository Owner 

* [Kornel Schrenk](http://www.schrenk.hu/about/)

## License

This software is available under [MIT](../master/LICENSE) license.
