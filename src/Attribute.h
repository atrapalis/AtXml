//Attribute.h
#ifndef ANTXML_ATTRIBUTE_H
#define ANTXML_ATTRIBUTE_H

#include <string>
#include <sstream>

namespace antXml {
	/// Class used to implement an XML attribute.
	/** An attribute is implemented using two variables: Name, and Value. */
    class Attribute {
        //Attributes
        protected:
            std::string Name;                                                       //!< Name of the XML attribute.
            std::string Value;                                                      //!< Value of the XML attribute.
        //Access Methods
        public:
            Attribute(std::string Name = "", std::string Value = "");
            template <typename Type> Attribute(std::string Name, Type Value);
            ~Attribute();
            std::string GetName();
            std::string GetValue();
            bool operator==(std::string);
            bool operator!=(std::string);
        //Process Methods
        public:
    };

	/// Template constructor.
	/** @param Name The Name member of the attribute.
        @param Value The Value member of the attribute, automatically converted to a C++ string. */
    template <typename Type>
    Attribute::Attribute(std::string Name, Type Value) {
        this->Name = Name;

        std::ostringstream Stream;
        Stream << Value;
        this->Value = Stream.str();
    }
}

#endif
