#include <iostream>
#include "Thermal.h"
#include "adalogo.h"
#include "adaqrcode.h"

#include "fb.h"

fb &_fb = fb::GetInstance();

int main() {
    Thermal printer("/dev/ttyUSB0");

    printer.begin(50);
/*
    // Test character double-height on & off
    printer.doubleHeightOn();
    printer.println("Double Height ON");
    printer.doubleHeightOff();

    // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
    printer.justify('R');
    printer.println("Right justified");
    printer.justify('C');
    printer.println("Center justified");
    printer.justify('L');
    printer.println("Left justified");

    // Test more styles
    printer.boldOn();
    printer.println("Bold text");
    printer.boldOff();

    printer.underlineOn();
    printer.println("Underlined text");
    printer.underlineOff();

    printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
    printer.println("Large");
    printer.setSize('M');
    printer.println("Medium");
    printer.setSize('S');
    printer.println("Small");

    printer.justify('C');
    printer.println("normal\nline\nspacing");
    printer.setLineHeight(50);
    printer.println("Taller\nline\nspacing");
    printer.setLineHeight(); // Reset to default
    printer.justify('L');

    // Barcode examples:
    // CODE39 is the most common alphanumeric barcode:
    printer.printBarcode("ADAFRUT", CODE39);
    printer.setBarcodeHeight(100);
    // Print UPC line on product barcodes:
    printer.printBarcode("123456789123", UPC_A);

    // Print the 75x75 pixel logo in adalogo.h:
    printer.printBitmap(adalogo_width, adalogo_height, adalogo_data);

    // Print the 135x135 pixel QR code in adaqrcode.h:
    printer.printBitmap(adaqrcode_width, adaqrcode_height, adaqrcode_data);
    printer.println("Adafruit!");
    printer.feed(2);

    printer.sleep();      // Tell printer to sleep
    sleep(3);         // Sleep for 3 seconds
    printer.wake();       // MUST wake() before printing again, even if reset
    printer.setDefault(); // Restore printer to defaults
    */

std::cout << "CACHSIZE: " << _fb.CACHSIZE << std::endl;

    _fb.OLED_DrawLine_fast(0,0,50,50,1);
    _fb.OLED_DrawLine_fast(50,0,0,50,1);
    _fb.OLED_DrawLine_fast(0,0,0,50,1);
    _fb.OLED_DrawLine_fast(0,0,50,0,1);
    _fb.OLED_DrawLine_fast(0,50,50,50,1);
    _fb.OLED_DrawLine_fast(50,0,50,50,1);

//    for(int x=0; x<128/8; x++) {
//        _fb.FBCache[x] = 0xff;
//    }

    printer.printBitmap(128, 64, _fb.FBCache);
//    printer.println("Test!!!");
//    printer.feed(2);





    std::cout << "Hello, World!" << std::endl;
    return 0;
}