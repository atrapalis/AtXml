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

//File.h
#ifndef ATXML_FILE_H
#define ATXML_FILE_H

#include "Tag.h"
namespace AtXml {
    class File {
        //Attributes
        protected:
            Tag Declaration;
            std::vector<Tag> Tags;
            int CurrentTag;
        //Access Methods
        public:
            File(std::string Location = "", std::string Root = "");
            ~File();
            void Clear();
            Tag GetTag();
            bool HasTags();
            void Reset();
        //Process Methods
        public:
            void AddTag(Tag Tag);
            void Build(std::string TargetLocation = "");
            int Parse(std::string Location, std::string Root = "");
            void SetDeclaration(Tag Tag);
    };
}

#endif
