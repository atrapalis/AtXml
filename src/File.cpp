//File.cpp
#include "File.h"
#include "Functions.h"
#include <iostream>
#include <sstream>
#include <fstream>

namespace antxml {
    /// Adds specified Tag to the list of tags.
    void File::AddTag(Tag Tag) {
        Tags.push_back(Tag);
    }

    /// Used to output the contents of the class in XML format.
	/** @param TargetLocation The output location of the XML file. If not specified, the file is printed on the console. */
    void File::Build(std::string TargetLocation) {
        //Save CurrentTag
        int Temp = CurrentTag;

        std::stringstream StringStream;

        //Declaration
        StringStream << "<?xml";

        while (Declaration.HasAttributes()) {
            antxml::Attribute Attribute = Declaration.GetAttribute();
            const std::string AttributeName = Attribute.GetName();
            const std::string AttributeValue = Attribute.GetValue();

            if (AttributeName != "" || AttributeValue != "") StringStream << " " << AttributeName << "=\"" << AttributeValue << "\"";
        }

        StringStream << " ?>\n";

        bool Tab = true;
        int Tabs = 0;
        while (HasTags()) {
            if (CurrentTag > 0) {
                if (Tags[CurrentTag].GetTrigger()) {
                    if (Tags[CurrentTag-1].GetTrigger() == Trigger::Open) {
                        Tab = true;
                        Tabs++;
                    } else if (Tags[CurrentTag-1].GetTrigger() == Trigger::Close){
                        //if (Tab) Tabs--; useless?
                        Tab = true;
                    }
                    StringStream << std::endl;
                } else {
                    if (Tags[CurrentTag-1].GetTrigger() == Trigger::Open) {
                        Tab = false;
                    } else {
                        Tab = true;
                        Tabs--;
                        StringStream << std::endl;
                    }
                }
            }

            if (Tab) for (int i = 0; i<Tabs; i++) StringStream << "\t";

            Tag Tag = GetTag();
            const std::string &Name = Tag.GetName();
            const int &Trigger = Tag.GetTrigger();
            const std::string &Text = Tag.GetText();

            StringStream << "<";

            if (Trigger == Trigger::Close) {
                StringStream << "/";
            } else if (Trigger == Trigger::Declaration) {
                StringStream << "?";
            }

            StringStream << Name;

            while (Tag.HasAttributes()) {
                antxml::Attribute Attribute = Tag.GetAttribute();
                const std::string AttributeName = Attribute.GetName();
                const std::string AttributeValue = Attribute.GetValue();

                if (AttributeName != "" || AttributeValue != "") StringStream << " " << AttributeName << "=\"" << AttributeValue << "\"";
            }

            if (Trigger == Trigger::OpenClose) StringStream << " /"; else if (Trigger == Trigger::Declaration) StringStream << " ?";

            StringStream << ">";
            if (Text != "") StringStream << Text;
        }

        if (TargetLocation == "") {
            std::cout << StringStream.rdbuf();
        } else {
            if (Tags.size() > 0) {
                std::ofstream OutputFile;
                OutputFile.open (TargetLocation.c_str());
                OutputFile << StringStream.rdbuf();
                OutputFile.close();
            } else std::cerr << "antxml: Writing failed. Attempted to write empty structure to " << TargetLocation << "." << std::endl;
        }

        //Restore CurrentTag
        CurrentTag = Temp;
    }

    /// Re-initialise all class members to default values and clear list of tags.
    void File::Clear() {
        Tags.clear();
        CurrentTag = 0;
    }

    /// Constructor with optional parameters.
	/** @param Location The location of the XML file.
        @param Type The root element of the XML file. If not specified, the first tag encountered is used as the root element. */
    File::File(std::string Location, std::string Type) {
        CurrentTag = 0;
        if (Location != "") Parse(Location, Type);
    }

    /// Returns the next tag from the list and increments index `CurrentTag`.
    Tag File::GetTag() {
        Tag Tag = Tags[CurrentTag];
        CurrentTag+=1;

        return Tag;
    }

    /// Used to check whether the end of the Tags list has been reached.
    /** Determined by the value of the index `CurrentTag`. */
    bool File::HasTags() {
        bool HasTags = false;
        if (CurrentTag < (signed)Tags.size()) HasTags = true;
        return HasTags;
    }

    /// Parses the specified XML file.
	/** @param Location The location of the XML file.
        @param Root The root element of the XML file. If not specified, the first tag encountered is used as the root element. */
    int File::Parse(std::string Location, std::string Root) {
        int Parse = 0;

        std::ifstream XML(Location.c_str());
        if (XML) {
            int CurrentLine = 0;
            bool MoreLines = true;
            bool RootFlag = false;

            bool Comment = false;
            while (MoreLines) {
                bool Debug = false;
                CurrentLine++;

                if (Debug) std::cerr << "Line " << CurrentLine << ": " << std::endl;

                //Get current line
                std::string Line;
                getline(XML, Line);

                //Convert to stream
                std::stringstream Linestream;
                Linestream << Line;

                //Cleanup spaces
                char Peek = Linestream.peek();
                while (Peek == ' ' || Peek == '\t') { Linestream.ignore(); Peek = Linestream.peek(); }

                //Get tags
                bool MoreTags;
                if (Linestream.eof()) MoreTags = false; else MoreTags = true;
                while (MoreTags) {
                    if (Peek == '<') {
                        Linestream.ignore();
                        Peek = Linestream.peek();
                        int Trigger = Trigger::Open;

                        //Cleanup spaces
                        while (Peek == ' ' || Peek == '\t') { Linestream.ignore(); Peek = Linestream.peek(); }
                        int GetPointer = Linestream.tellg();

                        //Close tag
                        if (Peek == '/') {
                            Linestream.ignore();
                            Peek = Linestream.peek();
                            Trigger = Trigger::Close;
                        //Declaration tag
                        } else if (Peek == '?') {
                            Linestream.ignore();
                            Peek = Linestream.peek();
                            Trigger = Trigger::Declaration;
                        //Comment
                        } else if (Peek == '!' && Line[GetPointer+1] == '-' && Line[GetPointer+2] == '-') {
                            Linestream.ignore();
                            Linestream.ignore();
                            Linestream.ignore();
                            Peek = Linestream.peek();
                            Comment = true;
                            if (Debug) std::cerr << "Comment Open" << std::endl;
                        }

                        //Cleanup spaces
                        while (Peek == ' ' || Peek == '\t') { Linestream.ignore(); Peek = Linestream.peek(); }
                        GetPointer = Linestream.tellg();

                        //Get tag name
                        int CriticalSpot[6] = {0, 0, 0, 0, 0, 0};
                        char CriticalChar[6] = {'>', '=', ' ', '\t', '/', '?'};

                        if (Debug) std::cerr << "\t";

                        for (int i = 0; i<6; i++) {
                            CriticalSpot[i] = Line.find_first_of(CriticalChar[i], GetPointer);
                            if (CriticalSpot[i] > CriticalSpot[0]) CriticalSpot[i] = -1; //Normalize

                            if (Debug) std::cerr << " " << CriticalSpot[i];
                        }

                        if (Debug) std::cerr << std::endl;

                        if (CriticalSpot[0] > -1) {
                            if (Comment) {
                                CriticalSpot[0] = Line.find_last_of('>');
                                if (Line[CriticalSpot[0]-1] == '-' && Line[CriticalSpot[0]-2] == '-') {
                                    while (GetPointer < CriticalSpot[0]) { Linestream.ignore(); Peek = Linestream.peek(); GetPointer = Linestream.tellg(); }
                                    Linestream.ignore();
                                    Peek = Linestream.peek();

                                    Comment = false;
                                    if (Debug) std::cerr << "Comment close" << std::endl;
                                } else {
                                    MoreTags = false;
                                    Linestream.clear();
                                }
                            } else {
                                //OpenClose
                                if (Line[CriticalSpot[0]-1] == '/') {
                                    Trigger = Trigger::OpenClose;
                                } else {
                                    //Verify trigger
                                    if (Trigger == Trigger::Declaration) {
                                        if (Line[CriticalSpot[0]-1] != '?') std::cerr << "antxml: Invalid XML declaration format at " << Location << ":" << CurrentLine << "." << std::endl;
                                    }
                                }

                                //Get tag std::string
                                std::string TagString;
                                int Minimum;

                                Minimum = FindMinimum(CriticalSpot, 6);
                                getline(Linestream, TagString, CriticalChar[Minimum]);
                                Linestream.putback(CriticalChar[Minimum]);
                                Peek = Linestream.peek();

                                Tag Tag;
                                if (Trigger == Trigger::Declaration) {
                                    if (TagString == "xml") {
                                        Declaration = antxml::Tag(TagString, Trigger);
                                    } else std::cerr << "antxml: Invalid XML declaration format at " << Location << ":" << CurrentLine << "." << std::endl;
                                } else {
                                    Tag = antxml::Tag(TagString, Trigger);
                                    if (Root == "" && Trigger == Trigger::Open) Root = TagString;
                                }

                                //Cleanup spaces
                                while (Peek == ' ' || Peek == '\t' || Peek == '/') { Linestream.ignore(); Peek = Linestream.peek(); }

                                //Get attributes
                                bool MoreAttributes;
                                if (CriticalSpot[1] > -1 && CriticalSpot[1] < CriticalSpot[0]) MoreAttributes = true; else MoreAttributes = false;
                                while (MoreAttributes) {
                                    //Cleanup
                                    while (Peek == ' ' || Peek == '\t' || Peek == '/' || Peek == '?') { Linestream.ignore(); Peek = Linestream.peek(); }

                                    GetPointer = Linestream.tellg();

                                    if (Debug) std::cerr << "\t\t";

                                    for(int i = 0; i<6; i++) {
                                        CriticalSpot[i] = Line.find_first_of(CriticalChar[i], GetPointer);
                                        if (CriticalSpot[i] > CriticalSpot[0]) CriticalSpot[i] = -1; //Normalize

                                        if (Debug) std::cout << " " << CriticalSpot[i];
                                    }

                                    if (Debug) std::cerr << std::endl;

                                    if (CriticalSpot[1] > -1 && CriticalSpot[1] < CriticalSpot[0]) MoreAttributes = true; else MoreAttributes = false;

                                    if (MoreAttributes) {
                                        //Get attribute name
                                        std::string AttributeName;
                                        Minimum = FindMinimum(CriticalSpot, 6);
                                        getline(Linestream, AttributeName, CriticalChar[Minimum]);
                                        Linestream.putback(CriticalChar[Minimum]);
                                        Peek = Linestream.peek();

                                        //Cleanup
                                        while (Peek == ' ' || Peek == '\t' || Peek == '=') { Linestream.ignore(); Peek = Linestream.peek(); }

                                        //Get attribute value
                                        std::string AttributeValue;
                                        if (Peek == '"' || Peek == '\'') {
                                            Linestream.ignore();
                                            getline(Linestream, AttributeValue, Peek);
                                            Peek = Linestream.peek();
                                        } else std::cerr << "antxml: Invalid attribute value. Expected quotation mark at " << Location << ":" << CurrentLine << "." << std::endl;

                                        Attribute Attribute = antxml::Attribute(AttributeName, AttributeValue);

                                        if (Trigger == Trigger::Declaration) {
                                            Declaration.AddAttribute(Attribute);
                                        } else {
                                            if (AttributeName != "") Tag.AddAttribute(Attribute);
                                        }
                                    }
                                }

                                //Add tag
                                if (Trigger != Trigger::Declaration) AddTag(Tag);

                                //Cleanup
                                if (CriticalSpot[0] > -1) {
                                    while (Peek != '>') { Linestream.ignore(); Peek = Linestream.peek(); }
                                    if (Peek == '>') {
                                        Linestream.ignore();
                                        Peek = Linestream.peek();
                                    } else {
                                        std::cerr << "antxml: Syntax error. Check for missing quotation marks or '>' at " << Location << ":" << CurrentLine << "." << std::endl;
                                    }
                                } else MoreTags = false;

                                //Cleanup spaces
                                while (Peek == ' ' || Peek == '\t') { Linestream.ignore(); Peek = Linestream.peek(); }

                                if (Tag.GetName() == Root) {
                                    if (Tag.GetTrigger() == Trigger::Open) {
                                        if (!RootFlag) RootFlag = true;
                                    } else if (Tag.GetTrigger() == Trigger::Close) {
                                        if (RootFlag) {
                                            MoreLines = false;
                                            MoreTags = false;
                                            if (!Linestream.eof()) {
                                                std::cerr << "antxml: Found data outside of root element at " << Location << ":" << CurrentLine << "." << std::endl;
                                            } else if (!XML.eof()) {
                                                getline(XML, Line);
                                                if (Line != "") std::cerr << "antxml: Found data outside of root element at " << Location << ":" << CurrentLine+1 << "." << std::endl;
                                            }
                                        }
                                    }
                                }

                                if (XML.eof() && !MoreTags) {
                                    if (RootFlag) {
                                        if (Tag.GetName() != Root || (Tag.GetName() == Root && Tag.GetTrigger() != 0)) std::cerr << "antxml: Root element not closed. End of file reached at " << Location << ":" << CurrentLine << "."<< std::endl;
                                    }
                                }
                            }
                        } else {
                            Linestream.clear();
                        }
                    } else {
                        //Get text
                        std::string Text;
                        getline(Linestream, Text, '<');
                        if (!Linestream.eof()) Linestream.putback('<');
                        Peek = Linestream.peek();

                        int CriticalSpot = Line.find_first_of('>');
                        if (Comment && Line[CriticalSpot-1] == '-' && Line[CriticalSpot-2] == '-') {
                            Comment = false;
                            if (Debug) std::cerr << "Comment close" << std::endl;
                        } else {
                            //Add to tag
                            if (Text != "") {
                                if (Tags.size() > 0) {
                                    if (Tags.back().GetTrigger() == Trigger::Open) Tags.back().AddText(Text); else std::cerr << "antxml: Unexpected characters ignored at " << Location << ":" << CurrentLine << "." << std::endl;
                                } else std::cerr << "antxml: Unexpected characters ignored at " << Location << ":" << CurrentLine << "." << std::endl;
                            }
                        }
                    }

                    if (Linestream.eof()) {
                        MoreTags = false;
                        if (Debug) std::cerr << "End of line." << std::endl;
                    }
                }

                if (XML.eof()) {
                    MoreLines = false;

                    if (Debug) std::cerr << "End of file." << std::endl;
                }
            }

            if (Declaration == "") std::cerr << "antxml: XML declaration not found in " << Location << "." << std::endl;
            if (!RootFlag) {
                std::cerr << "antxml: Root element not found. End of file reached at " << Location << ":" << CurrentLine << "."<< std::endl;
            }

            XML.close();
            Parse = 1;
        }

        return Parse;
    }

    /// Resets index `CurrentTag` to 0.
    void File::Reset() {
        CurrentTag = 0;
    }

    /// Sets the declaration tag using the specified parameter.
    void File::SetDeclaration(Tag Tag) {
        Declaration = Tag;
    }

    /// Basic destructor.
    File::~File() {
        Tags.clear();
        CurrentTag = 0;
    }
}
