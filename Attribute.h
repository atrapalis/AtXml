//Attribute.h
#ifndef ATXML_ATTRIBUTE_H
#define ATXML_ATTRIBUTE_H

#include <string>
#include <sstream>

namespace AtXml {
    class Attribute {
        //Attributes
        protected:
            std::string Name, Value;
        //Access Methods
        public:
            Attribute();
            Attribute(std::string Name, std::string Value);
            template <typename Type> Attribute(std::string Name, Type Value);
            ~Attribute();
            std::string GetName();
            std::string GetValue();
            bool operator==(std::string);
            bool operator!=(std::string);
        //Process Methods
        public:
    };

    template <typename Type>
    Attribute::Attribute(std::string Name, Type Value) {
        this->Name = Name;

        std::ostringstream Stream;
        Stream << Value;
        this->Value = Stream.str();
    }
}

#endif
