//File.h
#ifndef ANTXML_FILE_H
#define ANTXML_FILE_H

#include "Tag.h"
/// Contains all class and function implementations of the project.
namespace antXml {
	/// Class used to parse, implement, and output XML files.
	/** The XML file is implemented as a list of tags which can be accessed using public methods. */
    class File {
        //Attributes
        protected:
            Tag Declaration; 			                                    //!< XML declaration tag of the file.
            std::vector<Tag> Tags; 		                                    //!< List of Tags contained in the file.
            int CurrentTag; 			                                    //!< Index of attribute returned by GetTag() method.
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
