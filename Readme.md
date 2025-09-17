# Setting up Zephyr # 

## File Tree ## 
```
Blink is my project folder with all of the sibling files and folders being necessary to build and flash to the esp32

./
├── blink
├── bootloader
├── modules
├── tools
├── zephyr
├── zephyr-sdk-0.17.4
├── zephyr-sdk-0.17.4_macos-aarch64_minimal.tar.xz
└── zephyr-venv
```
## Install the necessary packages from brew ##

```bash 
brew install cmake ninja gperf python3 ccache qemu dtc libmagic wget openocd
```

## Setting up workspace ## 
``` bash 
mkdir zephyr_setup && cd zephyr_setup
python3 -m venv zephyr-venv
source sephyr-venv/bin/activate
```

## Install west and zephyr dependencies ## 
This command took around 20 minutes for me to run
``` bash 
pip install west
west init -m https://github.com/zephyrproject-rtos/zephyr -m main 
west update
west zephyr-export
pip install ./zephyrproject/zephyr/scripts/requirements.txt
```

## Intall the zephyr sdk ## 
Ensure you are in the parent directory. For apple silicon choose aarch otherwise if on mac, x86_64. Full list over here: [https://github.com/zephyrproject-rtos/sdk-ng/tags](https://github.com/zephyrproject-rtos/sdk-ng/tags)
``` bash 
wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.17.4/zephyr-sdk-0.17.4_macos-aarch64_minimal.tar.xz
tar xvf zephyr-sdk-0.17.4_macos-aarch64_minimal.tar.xz # replace the file name after xvf with the folder created after wget
```

## Setting up environment variables ## 
These will be ../ as we will be in the project fold(blink in my case) but the necessary files are in the parent folder
```bash 
export ZEPHYR_SDK_INSTALL_DIR=../zephyr-sdk-0.17.4 # replace with sdk folder nam
export ZEPHYR_BASE = ../zephyrproject/zephyr
```
## Create a new project folder ## 
``` bash
mkdir blink && cd blink 
git pull https://github.com/Aarav-J/zephyr_blink.git
```

## Building and flashing to the board ## 

First lets ensure the board is plugged in. 

### MacOS ### 
``` bash
ls /dev/cu.*
```

This should return something like this: 
``` bash 
/dev/cu.Bluetooth-Incoming-Port /dev/cu.debug-console  /dev/cu.usbserial-0001
```
/dev/cu.usbserial-0001 or any format like that is the esp32 and it is sucesfully plugged in. 

## Build and Flash ## 
This is for the esp32 dev kitv1 wroom
``` bash
west build --pristine=always -b esp32_devkitc/esp32/procpu ./
west flash 
west espressif monitor
```

# Code explanation #

This block of code sets pin 27 as a GPIO output pin which means electricity can be sent to that pin. The built in pin is 2. I had a led connected to pin 27. 
```  c
ret = gpio_pin_configure(gpio_ct_dev, 27, GPIO_OUTPUT_ACTIVE);
```

``` c
ret = gpio_pin_set_raw(gpio_ct_dev, 27, 1); // Turn the led on 
ret = gpio_pin_set_raw(gpio_ct_dev, 27, 0); // Turn the led off
```


