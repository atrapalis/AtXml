//File.cpp
#include "File.h"
#include "Functions.h"
#include <iostream>
#include <sstream>
#include <fstream>

namespace antxml {
    /// Constructor with optional parameters.
	/** @param location The location of the XML file.
        @param type The root element of the XML file. If not specified, the first tag encountered is used as the root element. */
    File::File(std::string location, std::string type) {
        currentTagIndex = 0;

        if (location != "")
            Parse(location, type);
    }

    /// Adds specified Tag to the list of tags.
    void File::AddTag(Tag tag) {
        tags.push_back(tag);
    }

    /// Used to output the contents of the class in XML format.
	/** @param targetLocation The output location of the XML file. If not specified, the file is printed on the console. */
    void File::Build(std::string targetLocation) {
        // Save currentTagIndex
        int temp = currentTagIndex;

        std::stringstream stringStream;

        // Declaration
        stringStream << "<?xml";

        while (declaration.HasAttributes()) {
            antxml::Attribute attribute = declaration.FetchAttribute();
            const std::string attributeName = attribute.GetName();
            const std::string attributeValue = attribute.GetValue();

            if (attributeName != "" || attributeValue != "")
                stringStream << " " << attributeName << "=\"" << attributeValue << "\"";
        }

        stringStream << " ?>\n";

        bool tab = true;
        int tabs = 0;

        while (HasTags()) {
            if (currentTagIndex > 0) {
                if (tags[currentTagIndex].GetTrigger()) {
                    if (tags[currentTagIndex-1].GetTrigger() == TRIGGER_OPEN) {
                        tab = true;
                        tabs++;
                    } else if (tags[currentTagIndex-1].GetTrigger() == TRIGGER_CLOSE){
                        //if (tab) Tabs--; useless?
                        tab = true;
                    }
                    stringStream << std::endl;
                } else {
                    if (tags[currentTagIndex-1].GetTrigger() == TRIGGER_OPEN) {
                        tab = false;
                    } else {
                        tab = true;
                        tabs--;
                        stringStream << std::endl;
                    }
                }
            }

            if (tab)
                for (int i = 0; i < tabs; i++)
                    stringStream << "\t";

            Tag tag = GetTag();
            const std::string name = tag.GetName();
            const Trigger trigger = tag.GetTrigger();
            const std::string text = tag.GetText();

            stringStream << "<";

            if (trigger == TRIGGER_CLOSE) {
                stringStream << "/";
            } else if (trigger == TRIGGER_DECLARATION) {
                stringStream << "?";
            }

            stringStream << name;

            while (tag.HasAttributes()) {
                antxml::Attribute attribute = tag.FetchAttribute();
                const std::string attributeName = attribute.GetName();
                const std::string attributeValue = attribute.GetValue();

                if (attributeName != "" || attributeValue != "")
                    stringStream << " " << attributeName << "=\"" << attributeValue << "\"";
            }

            if (trigger == TRIGGER_SELF_CLOSE)
                stringStream << " /";
            else if (trigger == TRIGGER_DECLARATION) stringStream << " ?";

            stringStream << ">";
            if (text != "")
                stringStream << text;
        }

        if (targetLocation == "") {
            std::cout << stringStream.rdbuf();
        } else {
            if (tags.size() > 0) {
                std::ofstream OutputFile;
                OutputFile.open (targetLocation.c_str());
                OutputFile << stringStream.rdbuf();
                OutputFile.close();
            } else
                std::cerr << "antxml: Writing failed. Attempted to write empty structure to " << targetLocation << "." << std::endl;
        }

        // Restore currentTagIndex
        currentTagIndex = temp;
    }

    /// Re-initialise all class members to default values and clear list of tags.
    void File::Clear() {
        tags.clear();
        currentTagIndex = 0;
    }

    /// Returns the next tag from the list and increments index `currentTagIndex`.
    Tag File::GetTag() {
        Tag tag = tags[currentTagIndex];
        currentTagIndex += 1;

        return tag;
    }

    /// Used to check whether the end of the tags list has been reached.
    /** Determined by the value of the index `currentTagIndex`. */
    bool File::HasTags() {
        return currentTagIndex < (signed)tags.size();
    }

    /// Parses the specified XML file.
	/** @param location The location of the XML file.
        @param root The root element of the XML file. If not specified, the first tag encountered is used as the root element. */
    int File::Parse(std::string location, std::string root) {
        int parse = 0;

        std::ifstream XML(location.c_str());
        if (XML) {
            int currentLine = 0;
            bool moreLines = true;
            bool rootFlag = false;

            bool comment = false;
            while (moreLines) {
                bool debug = false;
                currentLine++;

                if (debug)
                    std::cerr << "line " << currentLine << ": " << std::endl;

                // Get current line
                std::string line;
                getline(XML, line);

                // Convert to stream
                std::stringstream linestream;
                linestream << line;

                // Cleanup spaces
                char peek = linestream.peek();
                while (peek == ' ' || peek == '\t') {
                    linestream.ignore();
                    peek = linestream.peek();
                }

                // Get tags
                bool moretags;
                if (linestream.eof())
                    moretags = false;
                else
                    moretags = true;

                while (moretags) {
                    if (peek == '<') {
                        linestream.ignore();
                        peek = linestream.peek();
                        Trigger trigger = TRIGGER_OPEN;

                        // Cleanup spaces
                        while (peek == ' ' || peek == '\t') {
                            linestream.ignore();
                            peek = linestream.peek();
                        }
                        
                        int getPointer = linestream.tellg();

                        // Close tag
                        if (peek == '/') {
                            linestream.ignore();
                            peek = linestream.peek();
                            trigger = TRIGGER_CLOSE;
                        // Declaration tag
                        } else if (peek == '?') {
                            linestream.ignore();
                            peek = linestream.peek();
                            trigger = TRIGGER_DECLARATION;
                        // Comment
                        } else if (peek == '!' && line[getPointer + 1] == '-' && line[getPointer + 2] == '-') {
                            linestream.ignore();
                            linestream.ignore();
                            linestream.ignore();
                            peek = linestream.peek();
                            comment = true;
                            if (debug)
                                std::cerr << "Comment Open" << std::endl;
                        }

                        //Cleanup spaces
                        while (peek == ' ' || peek == '\t') {
                            linestream.ignore();
                            peek = linestream.peek();
                        }

                        getPointer = linestream.tellg();

                        //Get tag name
                        int criticalSpot[6] = {0, 0, 0, 0, 0, 0};
                        char criticalChar[6] = {'>', '=', ' ', '\t', '/', '?'};

                        if (debug)
                            std::cerr << "\t";

                        for (int i = 0; i<6; i++) {
                            criticalSpot[i] = line.find_first_of(criticalChar[i], getPointer);
                            if (criticalSpot[i] > criticalSpot[0])
                                criticalSpot[i] = -1; //Normalize

                            if (debug)
                                std::cerr << " " << criticalSpot[i];
                        }

                        if (debug) std::cerr << std::endl;

                        if (criticalSpot[0] > -1) {
                            if (comment) {
                                criticalSpot[0] = line.find_last_of('>');
                                if (line[criticalSpot[0] - 1] == '-' && line[criticalSpot[0] - 2] == '-') {
                                    while (getPointer < criticalSpot[0]) {
                                        linestream.ignore();
                                        peek = linestream.peek();
                                        getPointer = linestream.tellg();
                                    }

                                    linestream.ignore();
                                    peek = linestream.peek();

                                    comment = false;

                                    if (debug)
                                        std::cerr << "Comment close" << std::endl;
                                } else {
                                    moretags = false;
                                    linestream.clear();
                                }
                            } else {
                                // Self close
                                if (line[criticalSpot[0] - 1] == '/') {
                                    trigger = TRIGGER_SELF_CLOSE;
                                } else {
                                    // Verify trigger
                                    if (trigger == TRIGGER_DECLARATION) {
                                        if (line[criticalSpot[0] - 1] != '?')
                                            std::cerr << "antxml: Invalid XML declaration format at " << location << ":" << currentLine << "." << std::endl;
                                    }
                                }

                                //Get tag std::string
                                std::string tagstring;
                                int minimum;

                                minimum = FindMinimum(criticalSpot, 6);
                                getline(linestream, tagstring, criticalChar[minimum]);
                                linestream.putback(criticalChar[minimum]);
                                peek = linestream.peek();

                                Tag tag;
                                if (trigger == TRIGGER_DECLARATION) {
                                    if (tagstring == "xml") {
                                        declaration = antxml::Tag(tagstring, trigger);
                                    } else
                                        std::cerr << "antxml: Invalid XML declaration format at " << location << ":" << currentLine << "." << std::endl;
                                } else {
                                    tag = antxml::Tag(tagstring, trigger);
                                    if (root == "" && trigger == TRIGGER_OPEN)
                                        root = tagstring;
                                }

                                //Cleanup spaces
                                while (peek == ' ' || peek == '\t' || peek == '/')
                                    linestream.ignore(); peek = linestream.peek();

                                //Get attributes
                                bool MoreAttributes;
                                if (criticalSpot[1] > -1 && criticalSpot[1] < criticalSpot[0])
                                    MoreAttributes = true;
                                else
                                    MoreAttributes = false;

                                while (MoreAttributes) {
                                    //Cleanup
                                    while (peek == ' ' || peek == '\t' || peek == '/' || peek == '?') {
                                        linestream.ignore();
                                        peek = linestream.peek();
                                    }

                                    getPointer = linestream.tellg();

                                    if (debug)
                                        std::cerr << "\t\t";

                                    for(int i = 0; i<6; i++) {
                                        criticalSpot[i] = line.find_first_of(criticalChar[i], getPointer);
                                        if (criticalSpot[i] > criticalSpot[0])
                                            criticalSpot[i] = -1; //Normalize

                                        if (debug)
                                            std::cout << " " << criticalSpot[i];
                                    }

                                    if (debug) std::cerr << std::endl;

                                    if (criticalSpot[1] > -1 && criticalSpot[1] < criticalSpot[0])
                                        MoreAttributes = true;
                                    else
                                        MoreAttributes = false;

                                    if (MoreAttributes) {
                                        //Get attribute name
                                        std::string attributeName;
                                        minimum = FindMinimum(criticalSpot, 6);
                                        getline(linestream, attributeName, criticalChar[minimum]);
                                        linestream.putback(criticalChar[minimum]);
                                        peek = linestream.peek();

                                        //Cleanup
                                        while (peek == ' ' || peek == '\t' || peek == '=') {
                                            linestream.ignore();
                                            peek = linestream.peek();
                                        }

                                        //Get attribute value
                                        std::string attributeValue;
                                        if (peek == '"' || peek == '\'') {
                                            linestream.ignore();
                                            getline(linestream, attributeValue, peek);
                                            peek = linestream.peek();
                                        } else
                                            std::cerr << "antxml: Invalid attribute value. Expected quotation mark at " << location << ":" << currentLine << "." << std::endl;

                                        Attribute attribute = antxml::Attribute(attributeName, attributeValue);

                                        if (trigger == TRIGGER_DECLARATION) {
                                            declaration.AddAttribute(attribute);
                                        } else {
                                            if (attributeName != "")
                                                tag.AddAttribute(attribute);
                                        }
                                    }
                                }

                                //Add tag
                                if (trigger != TRIGGER_DECLARATION) AddTag(tag);

                                //Cleanup
                                if (criticalSpot[0] > -1) {
                                    while (peek != '>') { linestream.ignore(); peek = linestream.peek(); }
                                    if (peek == '>') {
                                        linestream.ignore();
                                        peek = linestream.peek();
                                    } else
                                        std::cerr << "antxml: Syntax error. Check for missing quotation marks or '>' at " << location << ":" << currentLine << "." << std::endl;
                                } else moretags = false;

                                //Cleanup spaces
                                while (peek == ' ' || peek == '\t') { linestream.ignore(); peek = linestream.peek(); }

                                if (tag.GetName() == root) {
                                    if (tag.GetTrigger() == TRIGGER_OPEN) {
                                        if (!rootFlag) rootFlag = true;
                                    } else if (tag.GetTrigger() == TRIGGER_CLOSE) {
                                        if (rootFlag) {
                                            moreLines = false;
                                            moretags = false;
                                            if (!linestream.eof()) {
                                                std::cerr << "antxml: Found data outside of root element at " << location << ":" << currentLine << "." << std::endl;
                                            } else if (!XML.eof()) {
                                                getline(XML, line);
                                                if (line != "")
                                                    std::cerr << "antxml: Found data outside of root element at " << location << ":" << currentLine + 1 << "." << std::endl;
                                            }
                                        }
                                    }
                                }

                                if (XML.eof() && !moretags) {
                                    if (rootFlag) {
                                        if (tag.GetName() != root || (tag.GetName() == root && tag.GetTrigger() != 0))
                                            std::cerr << "antxml: Root element not closed. End of file reached at " << location << ":" << currentLine << "."<< std::endl;
                                    }
                                }
                            }
                        } else {
                            linestream.clear();
                        }
                    } else {
                        //Get text
                        std::string Text;
                        getline(linestream, Text, '<');
                        if (!linestream.eof())
                            linestream.putback('<');
                        peek = linestream.peek();

                        int criticalSpot = line.find_first_of('>');
                        if (comment && line[criticalSpot - 1] == '-' && line[criticalSpot - 2] == '-') {
                            comment = false;
                            if (debug)
                                std::cerr << "Comment close" << std::endl;
                        } else {
                            //Add to tag
                            if (Text != "") {
                                if (tags.size() > 0) {
                                    if (tags.back().GetTrigger() == TRIGGER_OPEN)
                                        tags.back().AddText(Text);
                                    else
                                        std::cerr << "antxml: Unexpected characters ignored at " << location << ":" << currentLine << "." << std::endl;
                                } else
                                    std::cerr << "antxml: Unexpected characters ignored at " << location << ":" << currentLine << "." << std::endl;
                            }
                        }
                    }

                    if (linestream.eof()) {
                        moretags = false;
                        if (debug)
                            std::cerr << "End of line." << std::endl;
                    }
                }

                if (XML.eof()) {
                    moreLines = false;

                    if (debug)
                        std::cerr << "End of file." << std::endl;
                }
            }

            if (declaration == "")
                std::cerr << "antxml: XML declaration not found in " << location << "." << std::endl;

            if (!rootFlag)
                std::cerr << "antxml: Root element not found. End of file reached at " << location << ":" << currentLine << "."<< std::endl;

            XML.close();
            parse = 1;
        }

        return parse;
    }

    /// Resets index `currentTagIndex` to 0.
    void File::Reset() {
        currentTagIndex = 0;
    }

    /// Sets the declaration tag using the specified parameter.
    void File::SetDeclaration(Tag tag) {
        declaration = tag;
    }

    /// Basic destructor.
    File::~File() {
        tags.clear();
        currentTagIndex = 0;
    }
}
