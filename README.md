# AtXml 

Custom XML Parser library. Developed using only C++ standard libraries. Some examples can be found in the 'docs' folder.

This library is no longer in development but served its purpose to parse and interpret data such as User Interface structures stored in XML for other C++ projects.

## Classes
- **Tag:** Used to describe a tag as defined in an XML document, e.g.
```
<Tag>Content</Tag>
<Tag />
```
- **Attribute:** Used to describe attributes as defined in an XML tag, e.g.
```
<Tag Attribute="value" />
```
- **File:** Used to parse XML documents, and store data to memory using Tag/Attribute classes, e.g.
```
<Tag Attribute1="false">
  <NestedTag1 Attribute2="true" />
  <NestedTag2>Content</NestedTag2>
</Tag>
```

## Dependencies
- None

## Example

In this simple example, this library is used to load a set of settings from an XML file into memory.

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
