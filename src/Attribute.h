// Attribute.h
#ifndef ANTXML_ATTRIBUTE_H
#define ANTXML_ATTRIBUTE_H

#include <string>
#include <sstream>

namespace antxml {
	/// Class used to implement an XML attribute.
	/** An attribute is implemented using two variables: name, and value. */
    class Attribute {
        // Fields
        protected:
            std::string name;                                                       //!< The name of the XML attribute.
            std::string value;                                                      //!< The value of the XML attribute.
        
        // Methods
        public:
            Attribute(std::string name = "", std::string value = "");
            template <typename Type> Attribute(std::string name, Type value);

            bool operator==(std::string);
            bool operator!=(std::string);

            std::string GetName();
            std::string GetValue();

            ~Attribute();
    };

	/// Template constructor.
	/** @param name The name of the attribute.
        @param value The value of the attribute, converted to a C++ string using std::ostringstream. */
    template <typename Type>
    Attribute::Attribute(std::string name, Type value) {
        this->name = name;

        std::ostringstream stream;
        stream << value;
        this->value = stream.str();
    }
}

#endif
