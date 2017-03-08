# BleSensorRemote

For more information please see this blog [post](http://www.schrenk.hu)!

## Description

TODO

## Breadboard view

TODO

## Communication API

```javascript
IN  <-: @TEMP# - Ask for the current temperature
OUT ->: @23.4# - The temperature in celsius

IN  <-: @PRES# - Ask for the current ambient pressure
OUT ->: @1010.3# - The pressure in milliBar

IN  <-: @BAT# - Ask for the current battery charge
OUT ->: @4.14# - The current battery charge in volts
```

Every inbound and outbound message starts with the **@** character and ends with a **#**. 

## Repository Owner 

* [Kornel Schrenk](http://www.schrenk.hu/about/)

## License

This software is available under [MIT](../master/LICENSE) license.
