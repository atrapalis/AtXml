#include <iostream>
#include <XMLReader.h>

int main() {
    XMLReader::File File;

    if (File.Parse("Test.xml")) {
        File.Build();
    }

    std::cout << std::endl;
    while (File.HasTags()) {
        XMLReader::Tag Tag = File.GetTag();
        std::cout << Tag.GetName() << std::endl;
    }

    return 0;
}
