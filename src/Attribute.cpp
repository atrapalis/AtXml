//Attribute.cpp
#include "Attribute.h"

namespace antxml {
    /// Constructor with optional parameters.
	/** @param name The name member of the attribute.
        @param value The value member of the attribute. */
    Attribute::Attribute(std::string name, std::string value) {
        this->name = name;
        this->value = value;
    }

    /// operator== implementation.
    /** Compares the Name member to the string value. */
    bool Attribute::operator==(std::string attributeName) {
        return name == attributeName;
    }

    /// operator!= implementation.
    /** Compares the Name member to the string value. */
    bool Attribute::operator!=(std::string attributeName) {
        return name != attributeName;
    }

    /// Returns the Name member.
    std::string Attribute::GetName() {
        return name;
    }

    /// Returns the Value member.
    std::string Attribute::GetValue() {
        return value;
    }

    /// Basic destructor.
    Attribute::~Attribute() {
        name = value = "";
    }
}
