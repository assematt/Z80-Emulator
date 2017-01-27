#pragma once

#include <functional>
#include <fstream>
#include <map>

#include "TXMLNode.h"

namespace nne
{
	namespace xml
	{
		class TXMLFile
		{
		public:

			using TNodeAttributes = std::map<std::string, std::string>;
			using TNodeChildren = std::vector<std::string>;

			/// Function to save the current XML file
			bool readFile(const std::string& Path, TXMLNode::Ptr Head);

			/// Function to load the current XML file
			bool writeFile(const std::string& Path, TXMLNode::Ptr Head);

		private:

			std::string getNodeName(const std::string& Node);

			std::string getNodeContent(const std::string& Node);

			TNodeAttributes getNodeAttributes(const std::string& Node);

			TNodeChildren getNodeChildren(const std::string& Node);

			bool hasContent(const std::string& Node);

			bool hasChildren(const std::string& Node);

			std::string parseFile(const std::string& StringToParse, TXMLNode::Ptr Node);
						
		private:
			std::string		mLoadedFile;
			std::fstream	mFile;
		};
	}
	
}