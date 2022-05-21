#include <AtXml/AtXml.h>
#include <iostream>
using namespace std;

int main() {
    //Initialize variables
    string CharacterName[2] = {"", ""};
    string CharacterMap = "";
    int CharacterCoords[2] = {0, 0};
    int CharacterLevel = 0;
    string CharacterInventory = "";

    //Initialize a file
    AtXml::File File;
    string Location = "SaveGame.xml";

    //File parser returns 0 on failure, 1 on success.
    if (File.Parse(Location, "Save")) {
        //Tag loop
        while (File.HasTags()) {
            AtXml::Tag &Tag = File.GetTag();
            const string &Name = Tag.GetName();
            const int &Trigger = Tag.GetTrigger();
            const string Text = Tag.GetText();

            //Attribute loop
            while (Tag.HasAttributes()) {
                AtXml::Attribute &Attribute = Tag.GetAttribute();
                const string &AttributeName = Attribute.GetName();
                const string &AttributeValue = Attribute.GetValue();

                //Attribute Handler
                if (Name == "Save" && Trigger == AtXml::Trigger::Open) {
                    if (AttributeName == "Name") {
                        CharacterName[0] = AttributeValue;
                    } else if (AttributeName == "Surname") {
                        CharacterName[1] = AttributeValue;
                    }
                } else if (Name == "Location" && Trigger == AtXml::Trigger::OpenClose) {
                    if (AttributeName == "x") {
                        CharacterCoords[0] = AtXml::String2<int>(AttributeValue);
                    } else if (AttributeName == "y") {
                        CharacterCoords[1] = AtXml::String2<int>(AttributeValue);
                    }
                }
            }

            //Tag Handler
            if (Name == "Level" && Trigger == AtXml::Trigger::Open) {
                CharacterLevel = AtXml::String2<int>(Text);
            } else if (Name == "Map" && Trigger == AtXml::Trigger::Open) {
                CharacterMap = Text;
            } else if (Name == "Inventory" && Trigger == AtXml::Trigger::Open) {
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
