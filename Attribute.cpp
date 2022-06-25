//Attribute.cpp
#include "Attribute.h"

namespace antXml {
    /// Constructor with optional parameters.
	/** @param Name The Name member of the attribute.
        @param Value The Value member of the attribute. */
    Attribute::Attribute(std::string Name, std::string Value) {
        this->Name = Name;
        this->Value = Value;
    }

    /// Returns the Name member.
    std::string Attribute::GetName() {
        return Name;
    }

    /// Returns the Value member.
    std::string Attribute::GetValue() {
        return Value;
    }

    /// operator== implementation.
    /** Compares the Name member to the string value. */
    bool Attribute::operator==(std::string String) {
        if (Name == String) return true; else return false;
    }

    /// operator!= implementation.
    /** Compares the Name member to the string value. */
    bool Attribute::operator!=(std::string String) {
        if (Name != String) return true; else return false;
    }

    /// Basic destructor.
    Attribute::~Attribute() {
        Name = Value = "";
    }
}
