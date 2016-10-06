#pragma once
#include "../FileSystem.h"
#include <vector>
using namespace std;

namespace FileType
{
	namespace XML
	{
		struct Attribute
		{
			Attribute() : name(""), value("") {}
			string name;
			string value;
		};
		struct Tag
		{
		public:
			Tag() : name(""), inner("") {}
			Tag(string name) : name(name), inner("") {}
			void addAttr(Attribute attr) { attributes.push_back(attr); }
			string operator[](string selector) { for (Attribute attr : attributes) if (attr.name == selector) return attr.value; return "NULL"; };
			Tag operator[](unsigned int selector) { return subs[selector]; };
			string name;
			string inner;
			vector<Tag> subs;
		private:
			vector<Attribute> attributes;
		};
	}
	class XMLFile : public File
	{
	public:
		XMLFile(File& file) : File(file) {}
		static XMLFile load(File& file);

		XML::Tag getBody() { return body; };
	private:
		XML::Tag body;
	};
}