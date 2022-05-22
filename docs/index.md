 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`AtXml`](#namespace_at_xml) | Contains all class and function implementations of the project.

# namespace AtXml 

Contains all class and function implementations of the project.

## AtXml Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`FindMinimum`](#namespace_at_xml_1a265445dc5b2ec6dd67ca2b1ae3f0c5b7)`(int Integers,int Size)`            | Returns the minimum value from an array of integers.
`class `[`AtXml::Attribute`](#class_at_xml_1_1_attribute) | Class used to implement an XML attribute.
`class `[`AtXml::File`](#class_at_xml_1_1_file) | Class used to parse, implement, and output XML files.
`class `[`AtXml::Tag`](#class_at_xml_1_1_tag) | Class used to implement an XML tag.

## AtXml Members

#### `public int `[`FindMinimum`](#namespace_at_xml_1a265445dc5b2ec6dd67ca2b1ae3f0c5b7)`(int Integers,int Size)` 

Returns the minimum value from an array of integers.

#### Parameters
* `Integers` The array of integers. 

* `Size` The size of the array.

# class AtXml::Attribute 

Class used to implement an XML attribute.

An attribute is implemented using two variables: Name, and Value.

## AtXml::Attribute Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`Attribute`](#class_at_xml_1_1_attribute_1ab99a374b3da4a471d0c74270e6255adc)`(std::string Name,std::string Value)` | Constructor with optional parameters.
`public template<>`  <br/>` `[`Attribute`](#class_at_xml_1_1_attribute_1aa1ab75198c619a25f9a23116fe1c10dd)`(std::string Name,Type Value)` | Template constructor.
`public  `[`~Attribute`](#class_at_xml_1_1_attribute_1a4d5dd1626adb0b60ecfe2adb38ddd451)`()` | Basic destructor.
`public std::string `[`GetName`](#class_at_xml_1_1_attribute_1aac2f88fd2f8982228683198d80d8506e)`()` | Returns the Name member.
`public std::string `[`GetValue`](#class_at_xml_1_1_attribute_1aa78d6610d65f84d4167d4c50bcac1fdd)`()` | Returns the Value member.
`public bool `[`operator==`](#class_at_xml_1_1_attribute_1aa554e4e3aaaeac30b75b99230216552d)`(std::string)` | operator== implementation.
`public bool `[`operator!=`](#class_at_xml_1_1_attribute_1a68398b81e868b9af07b9fd81bdc7b0cf)`(std::string)` | operator!= implementation.
`protected std::string `[`Name`](#class_at_xml_1_1_attribute_1a9569eeaba6599f861cd291e8d85de0a9) | Name of the XML attribute.
`protected std::string `[`Value`](#class_at_xml_1_1_attribute_1a9cd66ebeb69f6b1d72b61c8d469d883d) | Value of the XML attribute.

## AtXml::Attribute Members

#### `public  `[`Attribute`](#class_at_xml_1_1_attribute_1ab99a374b3da4a471d0c74270e6255adc)`(std::string Name,std::string Value)` 

Constructor with optional parameters.

#### Parameters
* `Name` The Name member of the attribute. 

* `Value` The Value member of the attribute.

#### `public template<>`  <br/>` `[`Attribute`](#class_at_xml_1_1_attribute_1aa1ab75198c619a25f9a23116fe1c10dd)`(std::string Name,Type Value)` 

Template constructor.

#### Parameters
* `Name` The Name member of the attribute. 

* `Value` The Value member of the attribute, automatically converted to a C++ string.

#### `public  `[`~Attribute`](#class_at_xml_1_1_attribute_1a4d5dd1626adb0b60ecfe2adb38ddd451)`()` 

Basic destructor.

#### `public std::string `[`GetName`](#class_at_xml_1_1_attribute_1aac2f88fd2f8982228683198d80d8506e)`()` 

Returns the Name member.

#### `public std::string `[`GetValue`](#class_at_xml_1_1_attribute_1aa78d6610d65f84d4167d4c50bcac1fdd)`()` 

Returns the Value member.

#### `public bool `[`operator==`](#class_at_xml_1_1_attribute_1aa554e4e3aaaeac30b75b99230216552d)`(std::string)` 

operator== implementation.

Compares the Name member to the string value.

#### `public bool `[`operator!=`](#class_at_xml_1_1_attribute_1a68398b81e868b9af07b9fd81bdc7b0cf)`(std::string)` 

operator!= implementation.

Compares the Name member to the string value.

#### `protected std::string `[`Name`](#class_at_xml_1_1_attribute_1a9569eeaba6599f861cd291e8d85de0a9) 

Name of the XML attribute.

#### `protected std::string `[`Value`](#class_at_xml_1_1_attribute_1a9cd66ebeb69f6b1d72b61c8d469d883d) 

Value of the XML attribute.

# class AtXml::File 

Class used to parse, implement, and output XML files.

The XML file is implemented as a list of tags which can be accessed using public methods.

## AtXml::File Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`File`](#class_at_xml_1_1_file_1a5bea5a69b19de87b2b3d7750fca3967e)`(std::string Location,std::string Root)` | Constructor with optional parameters.
`public  `[`~File`](#class_at_xml_1_1_file_1a9df72763dfe7fbda8923cbdfea487ad8)`()` | Basic destructor.
`public void `[`Clear`](#class_at_xml_1_1_file_1a21eb0d7562f659c90dee99ef9823a3d4)`()` | Re-initialise all class members to default values and clear list of tags.
`public `[`Tag`](#class_at_xml_1_1_tag)` `[`GetTag`](#class_at_xml_1_1_file_1a25394b7eaadffedd16ecf63e53d10635)`()` | Returns the next tag from the list and increments index `CurrentTag`.
`public bool `[`HasTags`](#class_at_xml_1_1_file_1a5753b7dc1d32511b0a33ef03b2d443e1)`()` | Used to check whether the end of the Tags list has been reached.
`public void `[`Reset`](#class_at_xml_1_1_file_1a890a177aa85a857625c3e2d3e16fa400)`()` | Resets index `CurrentTag` to 0.
`public void `[`AddTag`](#class_at_xml_1_1_file_1a3f9ac9ec57b174d234bf3512e258bbdf)`(`[`Tag`](#class_at_xml_1_1_tag)` Tag)` | Adds specified [Tag](#class_at_xml_1_1_tag) to the list of tags.
`public void `[`Build`](#class_at_xml_1_1_file_1aa0752ce30bb57b34922384a09b4d182f)`(std::string TargetLocation)` | Used to output the contents of the class in XML format.
`public int `[`Parse`](#class_at_xml_1_1_file_1a9ff4c809dc24d6a1485f69817a68aaea)`(std::string Location,std::string Root)` | Parses the specified XML file.
`public void `[`SetDeclaration`](#class_at_xml_1_1_file_1aca126b450699367781e19b28d7abc76c)`(`[`Tag`](#class_at_xml_1_1_tag)` Tag)` | Sets the declaration tag using the specified parameter.
`protected `[`Tag`](#class_at_xml_1_1_tag)` `[`Declaration`](#class_at_xml_1_1_file_1a26e81175f73226602605bc6047557763) | XML declaration tag of the file.
`protected std::vector< `[`Tag`](#class_at_xml_1_1_tag)` > `[`Tags`](#class_at_xml_1_1_file_1a66dacebafddf1a58a0a4a0913957f0fc) | List of Tags contained in the file.
`protected int `[`CurrentTag`](#class_at_xml_1_1_file_1ae6a52aec4b931a936b3285869831cfb6) | Index of attribute returned by [GetTag()](#class_at_xml_1_1_file_1a25394b7eaadffedd16ecf63e53d10635) method.

## AtXml::File Members

#### `public  `[`File`](#class_at_xml_1_1_file_1a5bea5a69b19de87b2b3d7750fca3967e)`(std::string Location,std::string Root)` 

Constructor with optional parameters.

#### Parameters
* `Location` The location of the XML file. 

* `Type` The root element of the XML file. If not specified, the first tag encountered is used as the root element.

#### `public  `[`~File`](#class_at_xml_1_1_file_1a9df72763dfe7fbda8923cbdfea487ad8)`()` 

Basic destructor.

#### `public void `[`Clear`](#class_at_xml_1_1_file_1a21eb0d7562f659c90dee99ef9823a3d4)`()` 

Re-initialise all class members to default values and clear list of tags.

#### `public `[`Tag`](#class_at_xml_1_1_tag)` `[`GetTag`](#class_at_xml_1_1_file_1a25394b7eaadffedd16ecf63e53d10635)`()` 

Returns the next tag from the list and increments index `CurrentTag`.

#### `public bool `[`HasTags`](#class_at_xml_1_1_file_1a5753b7dc1d32511b0a33ef03b2d443e1)`()` 

Used to check whether the end of the Tags list has been reached.

Determined by the value of the index `CurrentTag`.

#### `public void `[`Reset`](#class_at_xml_1_1_file_1a890a177aa85a857625c3e2d3e16fa400)`()` 

Resets index `CurrentTag` to 0.

#### `public void `[`AddTag`](#class_at_xml_1_1_file_1a3f9ac9ec57b174d234bf3512e258bbdf)`(`[`Tag`](#class_at_xml_1_1_tag)` Tag)` 

Adds specified [Tag](#class_at_xml_1_1_tag) to the list of tags.

#### `public void `[`Build`](#class_at_xml_1_1_file_1aa0752ce30bb57b34922384a09b4d182f)`(std::string TargetLocation)` 

Used to output the contents of the class in XML format.

#### Parameters
* `TargetLocation` The output location of the XML file. If not specified, the file is printed on the console.

#### `public int `[`Parse`](#class_at_xml_1_1_file_1a9ff4c809dc24d6a1485f69817a68aaea)`(std::string Location,std::string Root)` 

Parses the specified XML file.

#### Parameters
* `Location` The location of the XML file. 

* `Root` The root element of the XML file. If not specified, the first tag encountered is used as the root element.

#### `public void `[`SetDeclaration`](#class_at_xml_1_1_file_1aca126b450699367781e19b28d7abc76c)`(`[`Tag`](#class_at_xml_1_1_tag)` Tag)` 

Sets the declaration tag using the specified parameter.

#### `protected `[`Tag`](#class_at_xml_1_1_tag)` `[`Declaration`](#class_at_xml_1_1_file_1a26e81175f73226602605bc6047557763) 

XML declaration tag of the file.

#### `protected std::vector< `[`Tag`](#class_at_xml_1_1_tag)` > `[`Tags`](#class_at_xml_1_1_file_1a66dacebafddf1a58a0a4a0913957f0fc) 

List of Tags contained in the file.

#### `protected int `[`CurrentTag`](#class_at_xml_1_1_file_1ae6a52aec4b931a936b3285869831cfb6) 

Index of attribute returned by [GetTag()](#class_at_xml_1_1_file_1a25394b7eaadffedd16ecf63e53d10635) method.

# class AtXml::Tag 

Class used to implement an XML tag.

A [Tag](#class_at_xml_1_1_tag) is implemented using three variables: Name, [Trigger](#namespace_at_xml_1_1_trigger), and Text. Contains a list of attributes which can be accessed using public methods.

## AtXml::Tag Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`Tag`](#class_at_xml_1_1_tag_1af4e604f2ead78dbcd4cb29c2592386d3)`(std::string Name,int Trigger)` | Constructor with optional parameters.
`public  `[`~Tag`](#class_at_xml_1_1_tag_1ad89bb67fefb45fb75873238c4aef1bd7)`()` | Basic destructor.
`public `[`Attribute`](#class_at_xml_1_1_attribute)` `[`GetAttribute`](#class_at_xml_1_1_tag_1af427e782bc5c080531a28c255c29ba85)`()` | Returns the next attribute from the list and increments index `CurrentAttribute`.
`public std::string `[`GetName`](#class_at_xml_1_1_tag_1a415450010b01263d755db934b680469c)`()` | Returns the Name member.
`public std::string `[`GetText`](#class_at_xml_1_1_tag_1ae7350201d81437785227d158a475d1bb)`()` | Returns the Text member.
`public int & `[`GetTrigger`](#class_at_xml_1_1_tag_1a2cbdbeb9586d6d19563d638507ed6f2a)`()` | Returns the [Trigger](#namespace_at_xml_1_1_trigger) member.
`public bool `[`HasAttributes`](#class_at_xml_1_1_tag_1aa3f2b8ec0ddc9ead7b5c4a1f7e610c1f)`()` | Used to check whether the end of the Attributes list has been reached.
`public bool `[`operator==`](#class_at_xml_1_1_tag_1a0afc916244fffe02e3f1276b15cd1ef0)`(std::string)` | operator== implementation.
`public bool `[`operator!=`](#class_at_xml_1_1_tag_1a3ad5f81b41f496f3dd30152fb3a7df35)`(std::string)` | operator!= implementation.
`public void `[`AddAttribute`](#class_at_xml_1_1_tag_1ac3aaee94b182e3b5a65d7720ae169103)`(`[`Attribute`](#class_at_xml_1_1_attribute)` Attribute)` | Adds specified [Attribute](#class_at_xml_1_1_attribute) to the list of attributes.
`public template<>`  <br/>`void `[`AddText`](#class_at_xml_1_1_tag_1a231fa1993121a201d6adc31dc353cf1f)`(Type Text)` | Concatenates the specified string to the current Text member.
`public template<>`  <br/>`void `[`SetText`](#class_at_xml_1_1_tag_1acf311973d0d57d720c67aeaf0630f78e)`(Type Text)` | Sets the Text member to the specified parameter value.
`protected std::string `[`Name`](#class_at_xml_1_1_tag_1afff917fc101aeb43e1b0666ad599b302) | Name of the XML tag.
`protected std::string `[`Text`](#class_at_xml_1_1_tag_1acce6ae42eafb83fc004030a12f1f1819) | Text content of the XML tag.
`protected int `[`Trigger`](#class_at_xml_1_1_tag_1af31db3bab2ba05b900f8429e5d88ab43) | [Tag](#class_at_xml_1_1_tag) type, e.g. opening, closing, self-closing.
`protected int `[`CurrentAttribute`](#class_at_xml_1_1_tag_1a3accd619bc8253a914f185d528a2a953) | Index of attribute returned by [GetAttribute()](#class_at_xml_1_1_tag_1af427e782bc5c080531a28c255c29ba85) method.
`protected std::vector< `[`Attribute`](#class_at_xml_1_1_attribute)` > `[`Attributes`](#class_at_xml_1_1_tag_1ac6d8c3a52235449e37e5bbc2f6b13b38) | List of attributes contained in the tag.
`protected void `[`BrowseAttributes`](#class_at_xml_1_1_tag_1a226a3622f22318a09e1735da7c70b957)`()` | Increments index `CurrentAttribute` by 1.
`protected void `[`ResetAttributes`](#class_at_xml_1_1_tag_1ad5f1d2e22c6631c5e83e56c3f63ff998)`()` | Resets index `CurrentAttribute` to 0.

## AtXml::Tag Members

#### `public  `[`Tag`](#class_at_xml_1_1_tag_1af4e604f2ead78dbcd4cb29c2592386d3)`(std::string Name,int Trigger)` 

Constructor with optional parameters.

#### Parameters
* `Name` Initialises the Name member of the tag. 

* `[Trigger](#namespace_at_xml_1_1_trigger)` Initialises the type of the tag.

#### `public  `[`~Tag`](#class_at_xml_1_1_tag_1ad89bb67fefb45fb75873238c4aef1bd7)`()` 

Basic destructor.

#### `public `[`Attribute`](#class_at_xml_1_1_attribute)` `[`GetAttribute`](#class_at_xml_1_1_tag_1af427e782bc5c080531a28c255c29ba85)`()` 

Returns the next attribute from the list and increments index `CurrentAttribute`.

#### `public std::string `[`GetName`](#class_at_xml_1_1_tag_1a415450010b01263d755db934b680469c)`()` 

Returns the Name member.

#### `public std::string `[`GetText`](#class_at_xml_1_1_tag_1ae7350201d81437785227d158a475d1bb)`()` 

Returns the Text member.

#### `public int & `[`GetTrigger`](#class_at_xml_1_1_tag_1a2cbdbeb9586d6d19563d638507ed6f2a)`()` 

Returns the [Trigger](#namespace_at_xml_1_1_trigger) member.

#### `public bool `[`HasAttributes`](#class_at_xml_1_1_tag_1aa3f2b8ec0ddc9ead7b5c4a1f7e610c1f)`()` 

Used to check whether the end of the Attributes list has been reached.

Determined by the value of the index `CurrentAttribute`.

#### `public bool `[`operator==`](#class_at_xml_1_1_tag_1a0afc916244fffe02e3f1276b15cd1ef0)`(std::string)` 

operator== implementation.

Compares the Name member to the string value.

#### `public bool `[`operator!=`](#class_at_xml_1_1_tag_1a3ad5f81b41f496f3dd30152fb3a7df35)`(std::string)` 

operator!= implementation.

Compares the Name member to the string value.

#### `public void `[`AddAttribute`](#class_at_xml_1_1_tag_1ac3aaee94b182e3b5a65d7720ae169103)`(`[`Attribute`](#class_at_xml_1_1_attribute)` Attribute)` 

Adds specified [Attribute](#class_at_xml_1_1_attribute) to the list of attributes.

#### `public template<>`  <br/>`void `[`AddText`](#class_at_xml_1_1_tag_1a231fa1993121a201d6adc31dc353cf1f)`(Type Text)` 

Concatenates the specified string to the current Text member.

#### `public template<>`  <br/>`void `[`SetText`](#class_at_xml_1_1_tag_1acf311973d0d57d720c67aeaf0630f78e)`(Type Text)` 

Sets the Text member to the specified parameter value.

#### `protected std::string `[`Name`](#class_at_xml_1_1_tag_1afff917fc101aeb43e1b0666ad599b302) 

Name of the XML tag.

#### `protected std::string `[`Text`](#class_at_xml_1_1_tag_1acce6ae42eafb83fc004030a12f1f1819) 

Text content of the XML tag.

#### `protected int `[`Trigger`](#class_at_xml_1_1_tag_1af31db3bab2ba05b900f8429e5d88ab43) 

[Tag](#class_at_xml_1_1_tag) type, e.g. opening, closing, self-closing.

#### `protected int `[`CurrentAttribute`](#class_at_xml_1_1_tag_1a3accd619bc8253a914f185d528a2a953) 

Index of attribute returned by [GetAttribute()](#class_at_xml_1_1_tag_1af427e782bc5c080531a28c255c29ba85) method.

#### `protected std::vector< `[`Attribute`](#class_at_xml_1_1_attribute)` > `[`Attributes`](#class_at_xml_1_1_tag_1ac6d8c3a52235449e37e5bbc2f6b13b38) 

List of attributes contained in the tag.

#### `protected void `[`BrowseAttributes`](#class_at_xml_1_1_tag_1a226a3622f22318a09e1735da7c70b957)`()` 

Increments index `CurrentAttribute` by 1.

#### `protected void `[`ResetAttributes`](#class_at_xml_1_1_tag_1ad5f1d2e22c6631c5e83e56c3f63ff998)`()` 

Resets index `CurrentAttribute` to 0.

Generated by [Moxygen](https://sourcey.com/moxygen)