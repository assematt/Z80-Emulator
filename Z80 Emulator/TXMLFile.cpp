#include "TXMLFile.h"

#include <algorithm>

namespace nne
{
	namespace xml
	{		
		bool TXMLFile::readFile(const std::string& Path, TXMLNode::Ptr Head)
		{
			// Open the file specified by Path
			mFile.open(Path);

			// If something goes bad return false
			if (!mFile.is_open())
				return false;

			// Load the entire file in memory
			mLoadedFile = "";
			std::string TempString;
			while (getline(mFile, TempString))
				mLoadedFile += TempString;

			// Un-prettify the loaded file
			mLoadedFile.erase(std::remove(mLoadedFile.begin(), mLoadedFile.end(), '\t'), mLoadedFile.end());
			mLoadedFile.erase(std::remove(mLoadedFile.begin(), mLoadedFile.end(), '\n'), mLoadedFile.end());

			// Parse the file
			parseFile(mLoadedFile, Head);

			mFile.close();

			mLoadedFile.clear();

			// If we made to this point everything went ok so return true
			return true;
		}

		bool TXMLFile::writeFile(const std::string& Path, TXMLNode::Ptr Head)
		{
			// Open the file specified by Path
			mFile.open(Path);

			// If something goes bad return false
			if (!mFile.is_open())
				return false;

			mFile << Head->renderNode();

			// If we made to this point everything went ok so return true
			return true;
		}

		std::string TXMLFile::getNodeName(const std::string& Node)
		{
			// The node name start 1 character after the '<' char
			auto StartTag = Node.find_first_of('<') + 1;

			// Find the first space in the string for the end of the node name since the node might have some attributes
			auto EndTag = Node.find_first_of(' ');

			// If it doesn't have any attributes the end position it's at the '>' char
			if ((EndTag == std::string::npos) || (EndTag > Node.find_first_of('>')))
				EndTag = Node.find_first_of('>');

			// See what the Node type
			return Node.substr(StartTag, EndTag - StartTag);
		}

		std::string TXMLFile::getNodeContent(const std::string& Node)
		{
			// Get the name of the node
			auto NodeName = getNodeName(Node);
			auto EndNodeName = "</" + NodeName + ">";

			auto StartTag = Node.find_first_of('>') + 1;
			auto EndTag = Node.find(EndNodeName);

			// See what the Node type
			return Node.substr(StartTag, EndTag - StartTag);
		}
		
		TXMLFile::TNodeAttributes TXMLFile::getNodeAttributes(const std::string& Node)
		{
			std::string SubString = "";
			auto SubStringStartTag = Node.find_first_of('<') + 1;
			auto SubStringEndTag = Node.find_first_of('>', SubStringStartTag);

			SubString = Node.substr(SubStringStartTag, SubStringEndTag - SubStringStartTag);

			// If the substring doesn't have any space we can assume that this node doesn't have any attributes so we can exit the function now
			if (SubString.find_first_of(' ') == std::string::npos)
				return TNodeAttributes();

			auto Index = SubString.find_first_of(' ') + 1;
			auto EndTag = SubString.size();

			TNodeAttributes Result;

			while (Index < EndTag)
			{
				auto EndAttributeName = SubString.find_first_of('=', Index);
				auto AttributeName = SubString.substr(Index, EndAttributeName - Index);

				EndAttributeName += 2;

				auto EndAttributeContent = SubString.find_first_of('"', EndAttributeName);
				auto AttributeContent = SubString.substr(EndAttributeName, EndAttributeContent - EndAttributeName);

				Result.emplace(AttributeName, AttributeContent);

				Index = EndAttributeContent + 2;
			}
			
			return Result;
		}

		TXMLFile::TNodeChildren TXMLFile::getNodeChildren(const std::string& Node)
		{
			TNodeChildren Result;

			// By default we start from the beginning
			auto BeginPos = 0u;

			while (BeginPos < Node.size())
			{
				// Get the name of the children
				auto ChildName = getNodeName(Node.substr(BeginPos));

				// Compose the string of the end tag fro this child
				auto EndTag = "</" + ChildName + ">";

				// Get the end position of the children
				auto EndPos = Node.find(EndTag, BeginPos) + EndTag.size();

				Result.push_back(Node.substr(BeginPos, EndPos - BeginPos));

				// Move the begin tag forward
				BeginPos = EndPos;
			}

/*

			auto BeginTag = Node.find_first_of('>') + 1;
			auto EndTag = Node.find_last_of('/') - 1;

			while (BeginTag != std::string::npos)
			{
				auto ChildBeginTag = Node.find_first_of('<', BeginTag) - 1;
				auto ChildEndTag = Node.find_first_of('/', BeginTag) - 1;

				Result.push_back(Node.substr(BeginTag, ChildEndTag - BeginTag));

				BeginTag = Node.find_first_of('>', ChildEndTag) + 1;
			}
*/

			return Result;
		}

		bool TXMLFile::hasContent(const std::string& Node)
		{
			auto StartTag = Node.find_first_of('>') + 1;

			return Node[StartTag] == '<' ? false : true;
		}

		bool TXMLFile::hasChildren(const std::string& Node)
		{
			auto StartTag = Node.find_first_of('>') + 2;

			return Node[StartTag] == '/' ? false : true;
		}

		/*
		<board>
			<wires>
				<wire>
					<points>
						<point>
							<X>0.f</X>
							<Y>0.f</Y>
						</point>
						<point>
							<X>50.f</X>
							<Y>50.f</Y>
						</point>
					</point>
					<junctions>
						<junction>
							<X>100.f</X>
							<Y>0.f</Y>
						</junction>
					</junctions>
				</wire>
			</wires>
		</board>
		*/

		std::string TXMLFile::parseFile(const std::string& StringToParse, TXMLNode::Ptr Node)
		{
			// Forward declare all the node properties
			std::string		NodeName;
			std::string		NodeContent;
			TNodeChildren	NodeChildren;
			TNodeAttributes	NodeAttributes;

			// Get the node name
			NodeName = getNodeName(StringToParse);

			// Get the node attributes if it has any
			NodeAttributes = getNodeAttributes(StringToParse);

			// Get the node content if it has any
			if (hasContent(StringToParse))
				NodeContent = getNodeContent(StringToParse);
			// Get the node children if it has any
			else if (hasChildren(StringToParse))
				NodeChildren = getNodeChildren(getNodeContent(StringToParse));
			
			// Creates the node
			//TXMLNode::Ptr NewNode = new TXMLNode();

			// Set his properties

			// Set the name
			//NewNode->setName(NodeName);
			Node->setName(NodeName);

			// Set the attributes (if it doesn't have none this loop will be skipped)
			for (auto& Attribute : NodeAttributes)
				//NewNode->addAttribute(Attribute.first, Attribute.second);
				Node->addAttribute(Attribute.first, Attribute.second);
			
			// Set the content if we have any
			if (!NodeContent.empty())
			{
				//NewNode->setContent(NodeContent);
				Node->setContent(NodeContent);
			}
			// Add the children if it has any
			else if (!NodeChildren.empty())
			{
				for (auto& Child : NodeChildren)
					//parseFile2(Child, NewNode->addChildNode());
					parseFile(Child, Node->addChildNode());
			}

			// If the passed node it's nullptr or it doesn't have any parent, we assign this created node
// 			if (!Node || (Node && !Node->hasParent()))
// 				Node = NewNode;
// 			else
// 				Node->addChildNode(NewNode);

			return StringToParse;
		}
		
	}
}