#include <XMLReader/XMLReader.h>
#include <iostream> //cout Function
using namespace std;

int main() {
    //Initialize variables
    string CharacterName[2] = {"", ""};
    string CharacterMap = "";
    int CharacterCoords[2] = {0, 0};
    int CharacterLevel = 0;
    string CharacterInventory = "";

    //Initialize a file
    XMLReader::File File;
    string Location = "SaveGame.xml";

    //File parser returns 0 on failure, 1 on success.
    if (File.Parse(Location, "Save")) {
        //Tag loop
        while (File.HasTags()) {
            XMLReader::Tag &Tag = File.GetTag();
            const string &Name = Tag.GetName();
            const int &Trigger = Tag.GetTrigger();
            const string Text = Tag.GetText();

            //Attribute loop
            while (Tag.HasAttributes()) {
                XMLReader::Attribute &Attribute = Tag.GetAttribute();
                const string &AttributeName = Attribute.GetName();
                const string &AttributeValue = Attribute.GetValue();

                //Attribute Handler
                if (Name == "Save" && Trigger == 1) {
                    if (AttributeName == "Name") {
                        CharacterName[0] = AttributeValue;
                    } else if (AttributeName == "Surname") {
                        CharacterName[1] = AttributeValue;
                    }
                } else if (Name == "Location" && Trigger == 2) {
                    if (AttributeName == "x") {
                        CharacterCoords[0] = XMLReader::String2<int>(AttributeValue);
                    } else if (AttributeName == "y") {
                        CharacterCoords[1] = XMLReader::String2<int>(AttributeValue);
                    }
                }
            }

            //Tag Handler
            if (Name == "Level" && Trigger == 1) {
                CharacterLevel = XMLReader::String2<int>(Text);
            } else if (Name == "Map" && Trigger == 1) {
                CharacterMap = Text;
            } else if (Name == "Inventory" && Trigger == 1) {
                CharacterInventory = Text;
            }
        }

        //Verify results
        cout << "Character Name: " << CharacterName[0] << " " << CharacterName[1] << endl;
        cout << "Level: " << CharacterLevel << endl;
        cout << "Location: " << CharacterMap << " (" << CharacterCoords[0] << ", " << CharacterCoords[1] << ")" << endl;
        cout << "Inventory: " << CharacterInventory << endl;
    }
    return 0;
}
