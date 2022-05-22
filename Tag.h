//Tag.h
#ifndef ATXML_TAG_H
#define ATXML_TAG_H

#include "Attribute.h"
#include <vector>
namespace AtXml {
	/// Namespace used to enumerate different Tag types.
    namespace Trigger {
        const int Close         = 0;                            //!< A closing tag, e.g. `</Tag>.`
        const int Open          = 1;                            //!< An opening tag, e.g. `<Tag>`.
        const int OpenClose     = 2;                            //!< A self-closing tag, e.g. `<Tag />`.
        const int Declaration   = 3;                            //!< A declaration tag, e.g. `<?xml ... ?>`
    }

	/// Class used to implement an XML tag.
	/** A Tag is implemented using three variables: Name, Trigger, and Text.
        Contains a list of attributes which can be accessed using public methods. */
    class Tag {
        //Attributes
        protected:
            std::string Name;                                   //!< Name of the XML tag.
            std::string Text;                                   //!< Text content of the XML tag.
            int Trigger;                                        //!< Tag type, e.g. opening, closing, self-closing.
            int CurrentAttribute;                               //!< Index of attribute returned by GetAttribute() method.
            std::vector<Attribute> Attributes;                  //!< List of attributes contained in the tag.
        //Access Methods
        public:
            Tag(std::string Name = "", int Trigger = -1);
            ~Tag();
            Attribute GetAttribute();
            std::string GetName();
            std::string GetText();
            int& GetTrigger();
            bool HasAttributes();
            bool operator==(std::string);
            bool operator!=(std::string);
        //Process Methods
        public:
            void AddAttribute(Attribute Attribute);
            template <typename Type> void AddText(Type Text);
            template <typename Type> void SetText(Type Text);
        protected:
            void BrowseAttributes();
            void ResetAttributes();
    };

    /// Concatenates the specified string to the current Text member.
    template <typename Type>
    void Tag::AddText(Type Text) {
        std::ostringstream Stream;
        Stream << Text;
        if (this->Text == "") this->Text = Stream.str(); else this->Text += "\n"+Stream.str();
    }

    /*template <>
    void Tag::AddText(std::string Text) {
        if (this->Text == "") this->Text = Text; else this->Text += "\n"+Text;
    }*/

    /// Sets the Text member to the specified parameter value.
    template <typename Type>
    void Tag::SetText(Type Text) {
        std::ostringstream Stream;
        Stream << Text;
        this->Text = Stream.str();
    }

    /*template <>
    void Tag::SetText(std::string Text) {
        this->Text = Text;
    }*/
}
#endif
