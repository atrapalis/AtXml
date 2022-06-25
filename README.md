# antXml 

An XML parser written in C++.

This library is no longer in development but was used to parse and interpret data such as User Interface structures stored in XML for my C++ projects.

## Compiling
To compile the source code, it is recommended to use the Code::Blocks project included in this repository. This library has only been tested in Windows environments. 

## Documentation
Documentation can be found in the [GitHub pages](https://atrapalis.github.io/antXml/) for this project.

## Example Usage

In this example, this library is used to initialise a set of settings from an XML file.

*Settings.xml*
```
<?xml version="1.0" encoding="UTF-8"?>
<Settings>
	<Fullscreen />
	<Resolution>800x600</Resolution>
	<BitsPerPixel>32</BitsPerPixel>
	<GameSpeed>25</GameSpeed>
	<FrameSkip>5</FrameSkip>
</Settings>
```

*Main.cpp*
```
#include <AtXml/AtXml.h>
#include <iostream>
using namespace std;

int main() {
    //Initialize variables
    bool Fullscreen = false;
    int Width = 0;
    int Height = 0;
    int BitsPerPixel = 0;
    int Speed = 0;

    //Initialize a file
    AtXml::File File;
    string Location = "Settings.xml";

    //File parser returns 0 on failure, 1 on success.
    if (File.Parse(Location, "Settings")) {
        //Tag loop
        while (File.HasTags()) {
            AtXml::Tag &Tag = File.GetTag();
            const string &Name = Tag.GetName();
            const int &Trigger = Tag.GetTrigger();
            const string &Text = Tag.GetText();

            //Tag Handler
            if (Name == "Fullscreen" && Trigger == AtXml::Trigger::OpenClose) {
                Fullscreen = true;
            } else if (Name == "BitsPerPixel" && Trigger == AtXml::Trigger::Open) {
                BitsPerPixel = AtXml::String2<int>(Text);
            } else if (Name == "Resolution" && Trigger == AtXml::Trigger::Open) {
                Width = AtXml::String2<int>(Text, 'x');
                Height = AtXml::String2<int>(Text, 'x', AtXml::Trigger::Open);
            } else if (Name == "GameSpeed" && Trigger == AtXml::Trigger::Open) {
                Speed = AtXml::String2<int>(Text);
            }
        }

        //Verify results
        if (Fullscreen) {
            cout << "Launch game in fullscreen mode" << endl;
        } else {
            cout << "Launch game in window mode." << endl;
        }

        cout << "Rendering resolution: " << Width << "x" << Height << endl;
        cout << "Bits per pixel: " << BitsPerPixel << endl;
        cout << "Game speed: " << Speed << endl;
    }
    return 0;
}
```
