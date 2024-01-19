//File.h
#ifndef ANTXML_FILE_H
#define ANTXML_FILE_H

#include "Tag.h"
/// Contains all class and function implementations of the project.
namespace antxml {
	/// Class used to parse, implement, and output XML files.
	/** The XML file is implemented as a list of tags which can be accessed using public methods. */
    class File {
        // Fields
        protected:
            Tag declaration; 			                                    //!< XML declaration tag of the file.
            std::vector<Tag> tags; 		                                    //!< List of Tags contained in the file.
            int currentTagIndex; 			                                //!< Index of attribute returned by GetTag() method.

        //Methods
        public:
            File(std::string location = "", std::string root = "");
            ~File();

            // Access
            Tag GetTag();
            bool HasTags();

            // Process
            void AddTag(Tag tag);
            void Build(std::string targetLocation = "");
            void Clear();
            int Parse(std::string location, std::string root = "");
            void Reset();
            void SetDeclaration(Tag tag);
    };
}

#endif
