#include "XMLFile.h"
#include <iostream>
using namespace std;
using namespace FileType;

/* All the XML read modes */
#define XML_BLANK 0
#define XML_TAGNAME 1
#define XML_ATTRIBUTE_NAME 2
#define XML_ATTRIBUTE_VALUE_SEARCH 3
#define XML_ATTRIBUTE_VALUE 4
#define XML_INNER 5
#define XML_ENDTAG 6

/* Adds the current tag in the stack to the last one */
#define COLLAPSE(tagStack) mode = XML_BLANK; tagStack[tagStack.size() - 2].subs.push_back(tagStack[tagStack.size() - 1]); tagStack.pop_back();

XMLFile XMLFile::load(File& file)
{
	/* If the files data has not already been loaded, then load it */
	if (!file.isLoaded())
		file.loadFileData();
	
	/* The current branch in the XML tree layout */
	vector<XML::Tag> tagStack;
	/* Add the main body tag */
	tagStack.push_back(XML::Tag("body"));
	/* The currently loaded attribute */
	XML::Attribute currentAttr;
	/* Defines which read mode it is in */
	unsigned int mode = XML_BLANK;
	for (unsigned int i = 0; i < file.getData().length(); i++)
	{
		/* Get the current character it is reading */
		char c = file.getData()[i];
		switch (mode)
		{
		/* There is no tag currently being read, this will search for a new one */
		case XML_BLANK:
			/* If the current character is not the start of a tag, then move onto the next one */
			if (c != '<') break;
			/* Otherwise, add a new tag to the stack and set the mode to read the tag name */
			tagStack.push_back(XML::Tag());
			mode = XML_TAGNAME;
			break;
		/* Reads the name of the tag */
		case XML_TAGNAME:
			/* If there is a space, then the end the tag name and read the first attribute's name */
			if (c == ' ') mode = XML_ATTRIBUTE_NAME;
			/* If there is a forward slash strait after the start, then it is an ending tag, so put it into that mode */
			else if (c == '/' && tagStack[tagStack.size() - 1].name == "") mode = XML_ENDTAG;
			/* If there is a forward slash after the name, then end the tag */
			else if (c == '/') { COLLAPSE(tagStack); }
			/* if there is a greater then sign, then read the inner data */
			else if (c == '>') mode = XML_INNER;
			/* Otherwise, add the current character to the current tag's name */
			else tagStack[tagStack.size() - 1].name += c; 
			break;
		case XML_ATTRIBUTE_NAME:
			/* If there is a space, then ignore it */
			if (c == ' ') break;
			/* If there is an equals sign, then search for the corresponding attribute */
			else if (c == '=') mode = XML_ATTRIBUTE_VALUE_SEARCH;
			/* A forward slash will indicate a tag ending, so it will end the tag */
			else if (c == '/') { COLLAPSE(tagStack); }
			/* if there is a greater then sign, then read the inner data */
			else if (c == '>') mode = XML_INNER;
			/* Otherwise, add the current character to the current attribute's name */
			else currentAttr.name += c;
			break;
		case XML_ATTRIBUTE_VALUE_SEARCH:
			/* If there is a speech mark, then it has found the attribute value */
			if (c == '"') mode = XML_ATTRIBUTE_VALUE;
			break;
		case XML_ATTRIBUTE_VALUE:
			/* If there is a speech mark, then the attribute has ended, so add it to the current tag, then reset the current attribute */
			if (c == '"')
			{
				mode = XML_ATTRIBUTE_NAME;
				tagStack[tagStack.size() - 1].addAttr(currentAttr);
				currentAttr = XML::Attribute();
				break;
			}
			/* Otherwise, add the current character to the current attribute's value */
			currentAttr.value += c;
		case XML_INNER:
			/* If there is a less then sign, then this means there is a new tag, so put it into new tag mode */
			if (c == '<') { mode = XML_BLANK; i -= 1; break; }
			/* Otherwise, add the current character to the current tag's inner data */
			tagStack[tagStack.size() - 1].inner += c;
		case XML_ENDTAG:
			/* If there is a greater then sign, then end the tag */
			if (c == '>') { tagStack.pop_back(); COLLAPSE(tagStack); }
			break;
		}
	}

	/* Create a new XML file, set the body to the fist tag, then return it */
	XMLFile xmlFile(file);
	xmlFile.body = tagStack[0];
	return xmlFile;
}