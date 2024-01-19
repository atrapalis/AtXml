//Tag.cpp
#include "Tag.h"
#include <sstream>

namespace antxml {
    /// Constructor with optional parameters.
	/** @param name Initialises the Name member of the tag.
        @param trigger Initialises the type of the tag. */
    Tag::Tag(std::string name, Trigger trigger) {
        this->name = name;
        this->trigger = trigger;
        text = "";
        currentAttributeIndex = 0;
    }

    /// operator== implementation.
    /** Compares the Name member to the string value. */
    bool Tag::operator==(std::string stringValue) {
        return name == stringValue;
    }

    /// operator!= implementation.
    /** Compares the Name member to the string value. */
    bool Tag::operator!=(std::string stringValue) {
        return name != stringValue;
    }

    /// Adds specified Attribute to the list of attributes.
    void Tag::AddAttribute(Attribute attribute) {
        attributes.push_back(attribute);
    }

    /// Increments index `CurrentAttribute` by 1.
    void Tag::BrowseAttributes() {
        currentAttributeIndex += 1;
        if (currentAttributeIndex >= (signed)attributes.size())
            currentAttributeIndex = -1;
    }

    /// Returns the next attribute from the list and increments index `CurrentAttribute`.
    Attribute Tag::FetchAttribute() {
        Attribute attribute = attributes[currentAttributeIndex];
        BrowseAttributes();
        return attribute;
    }

    /// Returns the Name member.
    std::string Tag::GetName() {
        return name;
    }

    /// Returns the Text member.
    std::string Tag::GetText() {
        return text;
    }

    /// Returns the Trigger member.
    Trigger Tag::GetTrigger() {
        return trigger;
    }

    /// Used to check whether the end of the Attributes list has been reached.
    /** Determined by the value of the index `CurrentAttribute`. */
    bool Tag::HasAttributes() {
        bool HasAttributes = false;

        if (attributes.size() > 0U && currentAttributeIndex >= 0)
            HasAttributes = true;
        else
            ResetAttributes();

        return HasAttributes;
    }

    /// Resets index `CurrentAttribute` to 0.
    void Tag::ResetAttributes() {
        currentAttributeIndex = 0;
    }

    /// Basic destructor.
    Tag::~Tag() {
        name = text = "";
        trigger = TRIGGER_INVALID;
        currentAttributeIndex = 0;
    }
}
