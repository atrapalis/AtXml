// Copyright © 2017 Aristotelis Trapalis. All Rights Reserved.
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer
//    in the documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products derived from this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE DEVELOPER "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
