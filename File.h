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
