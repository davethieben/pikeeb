# pikeeb
minimal app to run a keyboard from a raspberry pi

### Setup

First configure your Pi as a HID gadget; I used the tutorial here:
https://randomnerdtutorials.com/raspberry-pi-zero-usb-keyboard-hid/

Then you should be able to compile `pikeeb` on your Pi using gcc (or cmake if you have it installed). Currently the app is hard-coded for a 3x3 macropad, but it could be extended to support whatever you need. You will need to run with `sudo` or you will get a `Segmentation Fault`.

