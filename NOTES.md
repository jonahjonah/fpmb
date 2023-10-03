# Development Notes

## 9/5/23

- Created the repo
- comitted initial fpmb.ino file
- updated using the multiple MP3's version from Xtronical
- Tried to get it to work with a root dir that isnt "/" but couldn't get it to work. I made a "short" dir and tried "/short/", "/short", "short/", "short". None of those worked.
  - [ ] Ask Em about this some time, or do some more googling

## 10/2/23

- Added code to work with reed switch

# Build Notes

## Overall remaining stuff to build

- [ ] Fix Breakout Board on Board 2 (is this done?)
  - [ ] Test Board 2
- [x] Assemble 5 new BBs
- [ ] Modify new SD Readers (if needed)
  - [ ] Look into if this is needed
- [ ] Build 2 new boards
  - [x] Board 3 (built but not working)
    - [ ] Board isn't working, troubleshoot it
  - [ ] Board 4
- [ ] Solder wires to all speakers (6-9" of wire or so)
- [ ] Solder 3 more Reed Switch assemblies (9-12" of wire or so)

## 10/2/23

- Built the remaining Breakout Boards, and tried to fix the wonky on
- Assembled Board 3
  - used the two better looking BBs on Board 3
- Hooked it up to the speakers and sent the code (without Reed Switch code) to the board
  - It didn't work
  - I tried adding a `Serial.println()` print statement, and didn't see it in the serial output. Maybe I didn't have the Serial Monitor set up right though...

### To Do

- [ ] Confirm new SD readers don't need voltage modification
- [ ] Check all solders on the bottom of the board, clean and redo any that look bad
  - [ ] Test board after this
- [ ] Check all the wire connections are wired correctly (to the right pins, etc)
- [ ] Confirm the SD card is setup correctly for this code
- [ ] Confirm code without Reed Switch code is correct (compare to previous commit)
- [ ] If none of this works, ask Em? Maybe go to their house and use their multimeter to try and see what's wrong
