#include "XMLFile.h"
#include <iostream>
using namespace std;
using namespace FileType;

#define XML_BLANK 0
#define XML_TAGNAME 1
#define XML_ATTRIBUTE_NAME 2
#define XML_ATTRIBUTE_VALUE_SEARCH 3
#define XML_ATTRIBUTE_VALUE 4
#define XML_INNER 5
#define XML_ENDTAG 6

XMLFile XMLFile::load(File& file)
{
	if (!file.isLoaded())
		file.loadFileData();
	
	vector<XML::Tag> tags;
	vector<XML::Tag> tagStack;
	tagStack.push_back(XML::Tag("body"));
	XML::Attribute currentAttr;
	unsigned int mode = XML_BLANK;
	for (unsigned int i = 0; i < file.getData().length(); i++)
	{
		char c = file.getData()[i];
		switch (mode)
		{
		case XML_BLANK:
			if (c != '<') break;
			tagStack.push_back(XML::Tag());
			mode = XML_TAGNAME;
			break;
		case XML_TAGNAME:
			if (c == ' ') mode = XML_ATTRIBUTE_NAME;
			else if (c == '/' && tagStack[tagStack.size() - 1].name == "") mode = XML_ENDTAG;
			else if (c == '/') { mode = XML_BLANK; tagStack[tagStack.size() - 2].subs.push_back(tagStack[tagStack.size() - 1]); tagStack.pop_back(); }
			else if (c == '>') mode = XML_INNER;
			else tagStack[tagStack.size() - 1].name += c; 
			break;
		case XML_ATTRIBUTE_NAME:
			if (c == ' ') break;
			else if (c == '=') mode = XML_ATTRIBUTE_VALUE_SEARCH;
			else if (c == '/') { mode = XML_BLANK; tagStack[tagStack.size() - 2].subs.push_back(tagStack[tagStack.size() - 1]); tagStack.pop_back(); }
			else if (c == '>') mode = XML_INNER;
			else currentAttr.name += c;
			break;
		case XML_ATTRIBUTE_VALUE_SEARCH:
			if (c == '"') mode = XML_ATTRIBUTE_VALUE;
			break;
		case XML_ATTRIBUTE_VALUE:
			if (c == '"')
			{
				mode = XML_ATTRIBUTE_NAME;
				tagStack[tagStack.size() - 1].addAttr(currentAttr);
				currentAttr = XML::Attribute();
				break;
			}
			currentAttr.value += c;
		case XML_INNER:
			if (c == '<') { mode = XML_BLANK; i -= 1; break; }
			tagStack[tagStack.size() - 1].inner += c;
		case XML_ENDTAG:
			if (c == '>') { mode = XML_BLANK; tagStack.pop_back(); tagStack[tagStack.size() - 2].subs.push_back(tagStack[tagStack.size() - 1]); tagStack.pop_back(); }
			break;
		}
	}

	XMLFile xmlFile(file);
	xmlFile.body = tagStack[0];
	return xmlFile;
}