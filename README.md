<h1>
  Nucleo-F401RE C Bare-Metal Library
</h1>
Library to add a layer of abstraction over bare-metal Nucleo F401RE programming, 
by creating a set of functions to operate on the registers of the micro-controller.
This library is for personal and didactical uses.



<h2>Setup</h2>
<p>
  For this library to work, other CMSIS files must be included at build which are not on the repository.
  </br>
  They are the following:
  </br>
<code>cmsis_compiler.h
mpu_armv7.h
system_stm32f4xx.c
cmsis_gcc.h
stm32f401xe.h
system_stm32f4xx.h
cmsis_version.h
core_cm4.h
stm32f4xx.h</code>

They can be obtained in here:
<br>
[CMSIS Device F4](https://github.com/STMicroelectronics/cmsis-device-f4)
<br>
[CMSIS-5](https://github.com/arm-software/cmsis_5)
</p>

<h2>
  Functionalities
</h2>
<ul>
  <li>DMA</li>
  <li>ADC</li>
  <li>GPIO</li>
  <li>USART</li>
</ul>

<h2>Sample code</h2>
<p>
  The folder <code>Src/Samples</code> contains multiple files that demonstrate examples of 
  usage of these functions and their usefulness.
</p>

<h2>
  Incomming functionalities
</h2>
<ul>
  <li>SPI</li>
  <li>I2C</li>
</ul>
