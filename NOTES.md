# Development Notes

## 9/5/23

- Created the repo
- comitted initial fpmb.ino file
- updated using the multiple MP3's version from Xtronical
- Tried to get it to work with a root dir that isnt "/" but couldn't get it to work. I made a "short" dir and tried "/short/", "/short", "short/", "short". None of those worked.
  - [ ] Ask Em about this some time, or do some more googling

## 10/2/23

- Added code to work with reed switch

## 10/4/23

-Got board 2 working, tried updating code , and it stopped working

- it seems that this is the same issue that was happening with board 3? The serial monitor was showing an error

```
Playing gigibla.mp3
Guru Meditation Error: Core  1 panic'ed (LoadProhibited). Exception was unhandled.

Core  1 register dump:
PC      : 0x400ef7db  PS      : 0x00060030  A0      : 0x800ef8e0  A1      : 0x3ffb1fc0
A2      : 0x00000000  A3      : 0xffffffff  A4      : 0x0000002d  A5      : 0x3ffb1e50
A6      : 0x0000002d  A7      : 0x3ffb1e50  A8      : 0x8013f7b2  A9      : 0x3ffb1c10
A10     : 0x00000000  A11     : 0x3ffb1f50  A12     : 0x00000006  A13     : 0x00001000
A14     : 0x00000006  A15     : 0x3ffb1e74  SAR     : 0x00000004  EXCCAUSE: 0x0000001c
EXCVADDR: 0x00000010  LBEG    : 0x40087495  LEND    : 0x400874a5  LCOUNT  : 0xfffffffe


Backtrace: 0x400ef7d8:0x3ffb1fc0 0x400ef8dd:0x3ffb1ff0 0x400db5ed:0x3ffb2010 0x400ddb02:0x3ffb2030 0x400de1d5:0x3ffb21d0 0x400d2b75:0x3ffb21f0 0x400d2d9d:0x3ffb2240 0x400f5342:0x3ffb2290




ELF file SHA256: b4920975e88f86c4

Rebooting...
ets Jul 29 2019 12:21:46
```

- It seems that the code is trying to access an invalid memory address
- Asked Em what they think, leaving this alone for now, gonna work on some other components

# Build Notes

## Overall remaining stuff to build

- [x] Fix Breakout Board on Board 2 (is this done?)
  - [x] Test Board 2
- [x] Assemble 5 new BBs
- [ ] Modify new SD Readers (if needed)
  - [ ] Look into if this is needed
- [ ] Build 2 new boards
  - [x] Board 3 (built but not working)
    - [ ] Board isn't working, troubleshoot it
      - May be a code issue
  - [ ] Board 4
- [x] Solder wires to all speakers (6-9" of wire or so)
- [x] Solder 3 more Reed Switch assemblies (9-12" of wire or so)

## 10/2/23

- Built the remaining Breakout Boards, and tried to fix the wonky on
- Assembled Board 3
  - used the two better looking BBs on Board 3
- Hooked it up to the speakers and sent the code (without Reed Switch code) to the board
  - It didn't work
  - I tried adding a `Serial.println()` print statement, and didn't see it in the serial output. Maybe I didn't have the Serial Monitor set up right though...

### To Do

- **NOTE: it seems like this is a code issue. Asked Em what they think**
- [ ] Confirm new SD readers don't need voltage modification
- [ ] Check all solders on the bottom of the board, clean and redo any that look bad
  - [ ] Test board after this
- [ ] Check all the wire connections are wired correctly (to the right pins, etc)
- [ ] Confirm the SD card is setup correctly for this code
- [ ] Confirm code without Reed Switch code is correct (compare to previous commit)
- [ ] If none of this works, ask Em? Maybe go to their house and use their multimeter to try and see what's wrong

## 10/4/23

### Board 2 isn't working. Em suggested some things to try

- [x] Break copper traces wherever possible around BCLK (which is the one that seems to be causing the issues with the audio)
  - [x] Test if this helps
  - It worked!
- [ ] Add a 10ohm resistor between BCLK and GND (to act like my finger)
  - [ ] Test if this helps
- [x] Let Em know what did/didn't help

### Other stuff

- Made 3 more RS assemblies, and soldered 2 to the existing boards (all three existing boards now have a RS)
- Soldered wire to all speakers I have

### To do:

- [x] Buy 3 more speakers (one black 4o3w, two red 4o5w)
- Buy more solder
  - [ ] thick
    - Deciding which one I want. This is a contender https://www.amazon.com/gp/product/B00DE2QVIG/ref=ox_sc_saved_title_1?smid=AJ3PYHDIZANTK&psc=1
  - [x] fine

## 10/9/23

- Built board 4!

  - Tried to upload the code, but was getting an error saying `A fatal error occurred: Failed to connect to ESP32: No serial data received.`
  - ````
    Sketch uses 848333 bytes (64%) of program storage space. Maximum is 1310720 bytes.
    Global variables use 29608 bytes (9%) of dynamic memory, leaving 298072 bytes for local variables. Maximum is 327680 bytes.
    esptool.py v4.5.1
    Serial port /dev/cu.usbserial-0001
    Connecting......................................

    A fatal error occurred: Failed to connect to ESP32: No serial data received.
    For troubleshooting steps visit: https://docs.espressif.com/projects/esptool/en/latest/troubleshooting.html
    Failed uploading: uploading error: exit status 2```
    ````

  - Tried going into bootloader mode by holding `BOOT` and clicking `EN` but that didn't seem to work
  - Tried uploading and clicking `BOOT` several times during upload (`........` section) but that also didn't work
  - **Apparently this happens on some ESP32s, not sure what to do about it...**
    - [ ] Ask Ty? Maybe we can hop on a zoom some time?

- Tried testing older code on other boards, and all are still getting `Guru Meditation Error: Core  1 panic'ed (LoadProhibited). Exception was unhandled.` error
  - It seems like this is caused by memory running out and a memory location getting overwritten, and then incorrectly accessed
