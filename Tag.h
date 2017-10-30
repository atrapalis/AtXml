//Tag.h
#ifndef ATXML_TAG_H
#define ATXML_TAG_H

#include "Attribute.h"
#include <vector>
namespace AtXml {
    namespace Trigger {
        const int Close         = 0;
        const int Open          = 1;
        const int OpenClose     = 2;
        const int Declaration   = 3;
    }

    class Tag {
        //Attributes
        protected:
            std::string Name, Text;
            int Trigger, CurrentAttribute;
            std::vector<Attribute> Attributes;
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
