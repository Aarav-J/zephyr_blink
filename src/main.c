#include <zephyr/kernel.h> 
#include <zephyr/device.h> 
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h> 

static const struct device *gpio_ct_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));


void main(void) { 
    if(!device_is_ready(gpio_ct_dev)) { 
        printk("GPIO device not found\n");
        return; 
    }
    int ret; 
    ret = gpio_pin_configure(gpio_ct_dev, 27, GPIO_OUTPUT_ACTIVE); 
    if (ret != 0) { 
        printk("Error configuring pin\n");
        return; 
    }
    while (true) { 
        printk("LED ON\n");
        ret = gpio_pin_set_raw(gpio_ct_dev, 27, 1); 
        if(ret!= 0) { 
            return; 
        }
        k_msleep(500); 
        ret = gpio_pin_set_raw(gpio_ct_dev, 27, 0); 
        if(ret!= 0) { 
            return; 
        }
        k_msleep(500);
    }
}
// #include <zephyr/kernel.h>
// #include <zephyr/device.h>
// #include <zephyr/drivers/gpio.h>
// #include <zephyr/sys/printk.h>

// #define LED_PIN 2  // DevKitC often has an onboard LED here (active-LOW on many revs)
// static const struct device *gpio0 = DEVICE_DT_GET(DT_NODELABEL(gpio0));

// void main(void) {
//     printk("booting...\n");

//     if (!device_is_ready(gpio0)) {
//         printk("gpio0 not ready\n");
//         return;
//     }

//     gpio_pin_configure(gpio0, LED_PIN, GPIO_OUTPUT);
//     gpio_pin_set(gpio0, LED_PIN, 1); // off if active-LOW

//     while (1) {
//         gpio_pin_toggle(gpio0, LED_PIN);
//         printk("alive\n");
//         k_msleep(1000);
//     }
// }