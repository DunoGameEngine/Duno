#pragma once
#include "../FileSystem.h"
#include <vector>
using namespace std;

namespace FileType
{
	/* XML Data */ 
	namespace XML
	{
		/* Stores the data for an XML attribute */
		struct Attribute
		{
			/* Default constructor */
			Attribute() : name(""), value("") {}
			/* Stores the attributes name */
			string name;
			/* Stores the attributes value as a string */
			string value;
		};
		/* Stores the data for an XML tag */
		struct Tag
		{
		public:
			/* Default constructor */
			Tag() : name(""), inner("") {}
			/* Initialize with name */
			Tag(string name) : name(name), inner("") {}
			/* Adds an attribute to the tag */
			void addAttr(Attribute attr) { attributes.push_back(attr); }
			/* Allows you to select an attribute with <tag>[<name>] */
			string operator[](string selector) { for (Attribute attr : attributes) if (attr.name == selector) return attr.value; return "NULL"; };
			/* Allows you to select a sub tab with <tag>[<position>] */
			Tag operator[](unsigned int selector) { return subs[selector]; };
			/* Stores the tags name */
			string name;
			/* Stores the tags inner text */
			string inner;
			/* Stores the list of sub tags */
			vector<Tag> subs;
		private:
			/* Privately stores the tag's attributes */
			vector<Attribute> attributes;
		};
	}
	/* An XML file, contains the body tag, which includes all the tag in the file */
	class XMLFile : public File
	{
	public:
		/* Copy constructor */
		XMLFile(File& file) : File(file) {}
		/* Loads the XML data from a raw file */
		static XMLFile load(File& file);

		/* Returns the body tag, which contains all the tags in the file */
		XML::Tag getBody() { return body; };
	private:
		/* Store the XML body tag */
		XML::Tag body;
	};
}