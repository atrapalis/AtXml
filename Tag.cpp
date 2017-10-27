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

//Tag.cpp
#include "Tag.h"
#include <sstream>

namespace AtXml {
    void Tag::AddAttribute(Attribute Attribute) {
        Attributes.push_back(Attribute);
    }

    void Tag::BrowseAttributes() {
        CurrentAttribute+=1;
        if (CurrentAttribute >= (signed)Attributes.size()) CurrentAttribute = -1;
    }

    Tag::Tag(std::string Name, int Trigger) {
        this->Name = Name;
        this->Trigger = Trigger;
        Text = "";
        CurrentAttribute = 0;
    }

    Attribute Tag::GetAttribute() {
        Attribute Attribute = Attributes[CurrentAttribute];
        BrowseAttributes();
        return Attribute;
    }

    std::string Tag::GetName() {
        return Name;
    }

    std::string Tag::GetText() {
        return Text;
    }

    int& Tag::GetTrigger() {
        return Trigger;
    }

    bool Tag::HasAttributes() {
        bool HasAttributes = false;
        if ((signed)Attributes.size() > 0 && CurrentAttribute >= 0) HasAttributes = true; else ResetAttributes();
        return HasAttributes;
    }

    bool Tag::operator==(std::string String) {
        if (Name == String) return true; else return false;
    }

    bool Tag::operator!=(std::string String) {
        if (Name != String) return true; else return false;
    }

    void Tag::ResetAttributes() {
        CurrentAttribute = 0;
    }

    Tag::~Tag() {
        Name = Text = "";
        Trigger = -1;
        CurrentAttribute = 0;
    }
}
