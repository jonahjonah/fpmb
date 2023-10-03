// will play MP3's from the root of an SD card, ignoring other files
// By XTronical, www.xtronical.com, use as you wish
// Based on work and on the audio library of schreibfaul1
// See github page : https://github.com/schreibfaul1/ESP32-audioI2S
// Also has volume control via a potentiometer attached to pin 13

#include "Arduino.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"

// Digital I/O used
#define SD_CS          5
#define SPI_MOSI      23    // SD Card
#define SPI_MISO      19
#define SPI_SCK       18

#define REED_SWITCH   21

#define I2S_DOUT      25
#define I2S_BCLK      27    // I2S
#define I2S_LRC       26

// #define VolPin        13

Audio audio;

// uint8_t Volume;                         // range is 0 to 21

File RootDir;

int reedSwitchState;

void setup() {
    pinMode(SD_CS, OUTPUT);    
    pinMode(REED_SWITCH, INPUT_PULLUP); // set ESP32 pin to input pull-up mode  
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    Serial.begin(115200);
    if(!SD.begin(SD_CS))
    {
      Serial.println("Error talking to SD card!");
      while(true);                  // end program
    }
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    RootDir = SD.open("/");
    PlayNextSong();                         // Play next song, which will be the first at this point
}

void loop()
{
  reedSwitchState = digitalRead(REED_SWITCH); // read state

   if (reedSwitchState == HIGH) {
    audio.loop(); 
    audio.setVolume(10);         // Check volume level and adjust if necassary
  } else {
    Serial.println("The box is closed");
  }
    
}


void audio_eof_mp3(const char *info){  //end of file
    PlayNextSong();
}

void PlayNextSong()
{  
  bool SongFound=false;
  bool DirRewound=false;
  
  while(SongFound==false)
  {
    File entry =  RootDir.openNextFile();
    if (!entry)      // no more files
    {
      if(DirRewound==true)              // If we've already rewound once then there are no songs to play in this DIR
      {
        Serial.println("No MP3 files found to play");
        entry.close();
        return;
      }
      //else we've reached the end of all files in this directory, just rewind back to beginning
      RootDir.rewindDirectory();           // reset back to beginning
      DirRewound=true;            // Flag that we've rewound
    }
    else
    {
      if (!entry.isDirectory())                // only enter this if not a DIR
      {
        if(MusicFile(entry.name()))                   // Only enter if one of the acceptable music files
        {  
          Serial.print("Playing ");Serial.println(entry.name());
          audio.connecttoSD(entry.name());                          // Play the file
          SongFound=true;
        }
      }
    }    
    entry.close();
  }
}


bool MusicFile(String FileName)
{
  // returns true if file is one of the supported file types, i.e. mp3,aac
  String ext;
  ext=FileName.substring(FileName.indexOf('.')+1);
  if((ext=="mp3")|(ext=="aac"))
    return true;
  else
    return false;
}


// uint8_t GetVolume()
// {
//   // looks at the ADC pin that the potentiometer is connected to.
//   // returns the value as a volume setting
//   // The esp32's ADC has linerality problems at top and bottom we will ignore them and only respond to values in the middle range
  
//   uint16_t VolumeSettingReading;
  
//   VolumeSettingReading=analogRead(VolPin);
//   if(VolumeSettingReading<25)  // because of problems mentioned above, anything below 25 will be 0 volume
//     return 0;
//   if(VolumeSettingReading>4000) // because of problems mentioned above, anything above 4000 will be 21 volume
//     return 21;
//   // If we get this far we are in the middle range that should be linear 500-4000
//   return uint8_t(((VolumeSettingReading-25)/190));  // this will give the correct 0-21 range
// }
