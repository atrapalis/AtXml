//Attribute.cpp
#include "Attribute.h"

namespace AtXml {
    Attribute::Attribute() {
        Name = Value = "";
    }

    Attribute::Attribute(std::string Name, std::string Value) {
        this->Name = Name;
        this->Value = Value;
    }

    std::string Attribute::GetName() {
        return Name;
    }

    std::string Attribute::GetValue() {
        return Value;
    }

    bool Attribute::operator==(std::string String) {
        if (Name == String) return true; else return false;
    }

    bool Attribute::operator!=(std::string String) {
        if (Name != String) return true; else return false;
    }

    Attribute::~Attribute() {
        Name = Value = "";
    }
}
