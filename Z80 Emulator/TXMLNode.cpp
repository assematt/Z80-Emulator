#include "TXMLNode.h"

#include <sstream>

namespace nne
{
	namespace xml
	{

		TXMLNode::TXMLNode() :
			mParentNode(nullptr)
		{
		}

		TXMLNode::TXMLNode(const std::string& Name) :
			mParentNode(nullptr),
			mNodeName(Name)
		{

		}

		TXMLNode::TXMLNode(TXMLNode::Ptr Parent) :
			mParentNode(Parent)
		{
		}

		TXMLNode::TXMLNode(TXMLNode::Ptr Parent, const std::string& Name) :
			mParentNode(Parent),
			mNodeName(Name)
		{
		}
		
		TXMLNode::~TXMLNode()
		{
			for (auto Child : mChilds)
				delete Child;
		}

		void TXMLNode::setName(const std::string& Name)
		{
			mNodeName = Name;
		}

		const std::string& TXMLNode::getName() const
		{
			return mNodeName;
		}

		void TXMLNode::setContent(const std::string& Content)
		{
			mNodeContent = Content;
		}

		const std::string& TXMLNode::getContent() const
		{
			return mNodeContent;
		}

		bool TXMLNode::hasContent() const
		{
			return !mNodeContent.empty();
		}

		void TXMLNode::addAttribute(const std::string& AttributeName, const std::string& AttributeContent)
		{
			mAttributes.emplace(AttributeName, AttributeContent);
		}

		bool TXMLNode::hasAttributes() const
		{
			return mAttributes.size();
		}

		void TXMLNode::setParent(const Ptr ParentNode)
		{
			mParentNode = ParentNode;

			mParentNode->addChildNode(this);
		}

		bool TXMLNode::hasParent() const
		{
			return mParentNode ? true : false;
		}

		TXMLNode::Ptr TXMLNode::addChildNode(Ptr Child)
		{
			mChilds.push_back(Child);

			return mChilds.back();
		}

		TXMLNode::Ptr TXMLNode::addChildNode()
		{
			mChilds.push_back(new TXMLNode(this));

			return mChilds.back();
		}

		nne::xml::TXMLNode::Ptr TXMLNode::addChildNode(const std::string& ChildName)
		{
			mChilds.push_back(new TXMLNode(this, ChildName));

			return mChilds.back();
		}

		nne::xml::TXMLNode::Ptr TXMLNode::addChildNode(const std::string& ChildName, const std::string& ChildContent)
		{
			auto TempChild = new TXMLNode(this, ChildName);
			TempChild->mNodeContent = ChildContent;

			mChilds.push_back(TempChild);

			return mChilds.back();
		}

		std::vector<TXMLNode::Ptr> TXMLNode::getChildrenNodes(const std::string& Name, const std::size_t& Depth /*= 0*/) const
		{
			std::vector<Ptr> Result;

			for (auto& Child : mChilds)
			{
				if (Child->mNodeName == Name)
					Result.push_back(Child);

				if (!Child->mChilds.empty())
				{
					auto VR = Child->getChildrenNodes(Name, Depth);

					if (!VR.empty())
					{
						for (auto& mSubChild : VR)
							Result.push_back(mSubChild);
					}
				}
			}

			return Result;
		}

		TXMLNode::Ptr TXMLNode::getChildNode(const std::string& Name) const
		{
			for (auto& Child : mChilds)
				if (Child->mNodeName == Name)
					return Child;

			// Return an invalid child 
			return nullptr;
		}

		void TXMLNode::removeChildNode(Ptr Child)
		{
			auto It = std::find(mParentNode->mChilds.begin(), mParentNode->mChilds.end(), Child);

			if (It != mParentNode->mChilds.end())
			{
				// Mark the parent node of the node to delete as nullptr to avoid double delation of this element in the element destructor and down belowe
				(*It)->mParentNode = nullptr;

				delete *It;
				*It = nullptr;

				mParentNode->mChilds.erase(It);
			}
		}

		bool TXMLNode::hasChildren() const
		{
			return !mChilds.empty();
		}

		std::string TXMLNode::renderNode(bool PrettyRendering /*= false*/, std::size_t Depth /*= 0*/)
		{
			std::string Result = "";
			
			std::string TabString = PrettyRendering ? printTabs(Depth) : "";

			std::string NewLineChar = PrettyRendering ? "\n" : "";

			// Add the eventual tab if we are using pretty rendering
			Result += TabString;

			// Print the begin tag
			Result += printBeginNodeNameTag(mNodeName, mAttributes);

			// Print the content if it has some
			if (hasContent())
			{
				Result += mNodeContent;
			}
			// Otherwise print all the child
			else
			{
				Result += NewLineChar;

				for (auto& Child : mChilds)
					Result += Child->renderNode(PrettyRendering, Depth + 1);

				Result += TabString;
			}

			// Print the end tag
			Result += printEndNodeNameTag(mNodeName);

			Result += NewLineChar;

			return Result;
		}

		std::string TXMLNode::printTabs(const std::size_t& NumberOfTab)
		{
			std::string Result;

			for (auto Index = 0u; Index < NumberOfTab; ++Index)
				Result += '\t';

			return Result;
		}

		std::string TXMLNode::printBeginNodeNameTag(const std::string& Name, const TAttributes& Attributes)
		{
			std::string Result = "<" + Name;

			for (auto& Attribute : Attributes)
				Result += " " + Attribute.first + "=\"" + Attribute.second + "\"";

			return Result + ">";
		}

		std::string TXMLNode::printEndNodeNameTag(const std::string& Name)
		{
			return "</" + Name + ">";
		}

		const std::string& TXMLNode::getAttribute(const std::string& AttributeName) const
		{
			return mAttributes.at(AttributeName);
		}

	}
}