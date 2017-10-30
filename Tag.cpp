//Tag.cpp
#include "Tag.h"
#include <sstream>

namespace AtXml {
    void Tag::AddAttribute(Attribute Attribute) {
        Attributes.push_back(Attribute);
    }

    void Tag::BrowseAttributes() {
        CurrentAttribute+=1;
        if (CurrentAttribute >= (signed)Attributes.size()) CurrentAttribute = -1;
    }

    Tag::Tag(std::string Name, int Trigger) {
        this->Name = Name;
        this->Trigger = Trigger;
        Text = "";
        CurrentAttribute = 0;
    }

    Attribute Tag::GetAttribute() {
        Attribute Attribute = Attributes[CurrentAttribute];
        BrowseAttributes();
        return Attribute;
    }

    std::string Tag::GetName() {
        return Name;
    }

    std::string Tag::GetText() {
        return Text;
    }

    int& Tag::GetTrigger() {
        return Trigger;
    }

    bool Tag::HasAttributes() {
        bool HasAttributes = false;
        if ((signed)Attributes.size() > 0 && CurrentAttribute >= 0) HasAttributes = true; else ResetAttributes();
        return HasAttributes;
    }

    bool Tag::operator==(std::string String) {
        if (Name == String) return true; else return false;
    }

    bool Tag::operator!=(std::string String) {
        if (Name != String) return true; else return false;
    }

    void Tag::ResetAttributes() {
        CurrentAttribute = 0;
    }

    Tag::~Tag() {
        Name = Text = "";
        Trigger = -1;
        CurrentAttribute = 0;
    }
}
