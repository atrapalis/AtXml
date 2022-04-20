# AtXml 

XML Parser library written in C++. Developed from scratch using C++ standard libraries. Some examples and documentation can be found in the 'resources' folder.

This library is no longer in development but served its purpose to parse and interpret User Interface structures stored in XML for other C++ projects.

## Classes
- **Tag:** Used to describe a tag as defined in an XML document, e.g.
```
<Tag>Content</Tag>
<Tag />
```
- **Attribute:** Used to describe attributes as defined in an XML tag, e.g.
```
<Tag Attribute="value" />
```
- **File:** Used to parse XML documents, and store data to memory using Tag/Attribute classes, e.g.
```
<Tag Attribute1="false">
  <NestedTag1 Attribute2="true" />
  <NestedTag2>Content</NestedTag2>
</Tag>
```

## Dependencies
- None
