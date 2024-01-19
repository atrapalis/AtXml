//Tag.h
#ifndef ANTXML_TAG_H
#define ANTXML_TAG_H

#include "Attribute.h"
#include <vector>
namespace antxml {
	/// Enumerators for different Tag types.
    enum Trigger {
        TRIGGER_CLOSE           = 0,                            //!< A closing tag, e.g. `</Tag>.`
        TRIGGER_OPEN            = 1,                            //!< An opening tag, e.g. `<Tag>`.
        TRIGGER_SELF_CLOSE      = 2,                            //!< A self-closing tag, e.g. `<Tag />`.
        TRIGGER_DECLARATION     = 3,                            //!< A declaration tag, e.g. `<?xml ... ?>`
        TRIGGER_INVALID         = -1,
    };

	/// Class used to implement an XML tag.
	/** A Tag is implemented using three variables: Name, Trigger, and Text.
        Contains a list of attributes which can be accessed using public methods. */
    class Tag {
        // Fields
        protected:
            std::string name;                                   //!< Name of the XML tag.
            std::string text;                                   //!< Text content of the XML tag.
            Trigger trigger;                                    //!< Tag type, e.g. opening, closing, self-closing.
            int currentAttributeIndex;                          //!< Index of attribute returned by GetAttribute() method.
            std::vector<Attribute> attributes;                  //!< List of attributes contained in the tag.

        // Methods
        public:
            Tag(std::string name = "", Trigger trigger = TRIGGER_OPEN);
            ~Tag();

            // Operators
            bool operator==(std::string);
            bool operator!=(std::string);

            // Access
            Attribute FetchAttribute();
            std::string GetName();
            std::string GetText();
            Trigger GetTrigger();
            bool HasAttributes();

            // Process
            void AddAttribute(Attribute attribute);
            template <typename Type> void AddText(Type text);
            template <typename Type> void SetText(Type text);

        protected:
            void BrowseAttributes();
            void ResetAttributes();
    };

    /// Concatenates the specified string to the current text member.
    template <typename Type>
    void Tag::AddText(Type text) {
        std::ostringstream stream;
        stream << text;

        if (this->text != "")
            this->text += "\n";

        this->text = stream.str();
    }

    /// Sets the Text member to the specified parameter value.
    template <typename Type>
    void Tag::SetText(Type text) {
        std::ostringstream stream;
        stream << text;
        this->text = stream.str();
    }
}
#endif
