//Tag.cpp
#include "Tag.h"
#include <sstream>

namespace antXml {
    /// Adds specified Attribute to the list of attributes.
    void Tag::AddAttribute(Attribute Attribute) {
        Attributes.push_back(Attribute);
    }

    /// Increments index `CurrentAttribute` by 1.
    void Tag::BrowseAttributes() {
        CurrentAttribute+=1;
        if (CurrentAttribute >= (signed)Attributes.size()) CurrentAttribute = -1;
    }

    /// Constructor with optional parameters.
	/** @param Name Initialises the Name member of the tag.
        @param Trigger Initialises the type of the tag. */
    Tag::Tag(std::string Name, int Trigger) {
        this->Name = Name;
        this->Trigger = Trigger;
        Text = "";
        CurrentAttribute = 0;
    }

    /// Returns the next attribute from the list and increments index `CurrentAttribute`.
    Attribute Tag::GetAttribute() {
        Attribute Attribute = Attributes[CurrentAttribute];
        BrowseAttributes();
        return Attribute;
    }

    /// Returns the Name member.
    std::string Tag::GetName() {
        return Name;
    }

    /// Returns the Text member.
    std::string Tag::GetText() {
        return Text;
    }

    /// Returns the Trigger member.
    int& Tag::GetTrigger() {
        return Trigger;
    }

    /// Used to check whether the end of the Attributes list has been reached.
    /** Determined by the value of the index `CurrentAttribute`. */
    bool Tag::HasAttributes() {
        bool HasAttributes = false;
        if ((signed)Attributes.size() > 0 && CurrentAttribute >= 0) HasAttributes = true; else ResetAttributes();
        return HasAttributes;
    }

    /// operator== implementation.
    /** Compares the Name member to the string value. */
    bool Tag::operator==(std::string String) {
        if (Name == String) return true; else return false;
    }

    /// operator!= implementation.
    /** Compares the Name member to the string value. */
    bool Tag::operator!=(std::string String) {
        if (Name != String) return true; else return false;
    }

    /// Resets index `CurrentAttribute` to 0.
    void Tag::ResetAttributes() {
        CurrentAttribute = 0;
    }

    /// Basic destructor.
    Tag::~Tag() {
        Name = Text = "";
        Trigger = -1;
        CurrentAttribute = 0;
    }
}
