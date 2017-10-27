#include <XMLReader/XMLReader.h>
#include <iostream> //cout Function
using namespace std;

int main() {
    //Initialize variables
    bool Fullscreen = false;
    int Width = 0;
    int Height = 0;
    int BitsPerPixel = 0;
    int Speed = 0;

    //Initialize a file
    XMLReader::File File;
    string Location = "Settings.xml";

    //File parser returns 0 on failure, 1 on success.
    if (File.Parse(Location, "Settings")) {
        //Tag loop
        while (File.HasTags()) {
            XMLReader::Tag &Tag = File.GetTag();
            const string &Name = Tag.GetName();
            const int &Trigger = Tag.GetTrigger();
            const string &Text = Tag.GetText();

            //Tag Handler
            if (Name == "Fullscreen" && Trigger == 2) {
                Fullscreen = true;
            } else if (Name == "BitsPerPixel" && Trigger == 1) {
                BitsPerPixel = XMLReader::String2<int>(Text);
            } else if (Name == "Resolution" && Trigger == 1) {
                Width = XMLReader::String2<int>(Text, 'x');
                Height = XMLReader::String2<int>(Text, 'x', 1);
            } else if (Name == "GameSpeed" && Trigger == 1) {
                Speed = XMLReader::String2<int>(Text);
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
