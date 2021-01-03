# galvo scanner

setup for displaying a still images

<img src="/img/electronics.jpg" style="width:20%;">
<img src="/img/happy new year.jpg" style="width:20%;">

[<img src="https://img.youtube.com/vi/ha9n86Zofew/maxresdefault.jpg" width="20%">](https://youtu.be/ha9n86Zofew)

the scanner is composed of a power supply, two mirror galvanometers and their control units ordered from china. the control units are controled with an differential Signal with +/-5V max. \
this signal is generated from an analog signal using one inverting op-amp to generate the negative output and one op-amp as a voltage buffer for the original signal for each axis. \
the actual analog signal is stored as a 12bit value on an arduino nano and communicated to two mcp4725 DACs over I2C. \
the image is by rederecting a laser pointer by the galvo mirrors and turning the laser pointer on and off on Pin D13.

the following programs are supplied:
- a short sketch to run the galvo scanner with use of arduino libraries "galvo"
- a faster version by directly controling the registers on the atmega328p "galvo_lowlevel"
- the faster version with line tracing by a predefined step size instead of directly jumping between stored points "galvo_lowlevel_trace"


the procedure to generate coordinate points form any svg is as follows:
- in inkscape set svg size to 1inch x 1inch and export it as graphics.hpgl with 4095dpi x 4095dpi, this generated the coordinates
- run script "convert.py" to convert the graphics.hpgl file to graphics.cpp, this reformats the coordinate points into three arrays for the x/y-coordinated and if the laser has to be on/off at that particular coordinates (the separate steps and their output are visualized in hpgl to hex.ipynb)
an example is stored in the folder "svg to coordinates"

## issues
my galvo does respond quite slowly and not linear even after calibration. when using the first two scripts ("galvo" & "galvo_lowlevel") long straight lines get distorted and the image can only be displayed if an additional delay between each coordinate change is set. The third script circumvents this issues by tracing long lines with many small steps. there is a tradeoff between the step size and the frame rate, such that the path has either distinct sharp steps or is only observable in a long exposure with a camera.
