#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

namespace nne
{
	namespace xml
	{
	
		class TXMLNode
		{
		public:

			/// TXMLNode Iterator
			using Ptr = TXMLNode*;
			using SharedPtr = std::shared_ptr<TXMLNode>;
			using TChildren = std::vector<Ptr>;
			using TAttributes = std::unordered_map<std::string, std::string>;

			TXMLNode();

			TXMLNode(const std::string& Name);

			TXMLNode(TXMLNode::Ptr Parent);

			TXMLNode(TXMLNode::Ptr Parent, const std::string& Name);

			TXMLNode(const TXMLNode& Copy) = delete;
			TXMLNode(TXMLNode&& Move) = delete;

			~TXMLNode();

			/// Set/Get this node name
			void setName(const std::string& Name);
			const std::string& getName() const;

			/// Set/Get this node content
			void setContent(const std::string& Content);

			/// Generic case
			const std::string& getContent() const;

			template <class T>
			typename std::enable_if<!std::is_scalar<T>::value, T>::type getContent() const
			{
				return static_cast<T>(mNodeContent);
			}

			/// Specialization for non-floating point number
			template <class T>
			typename std::enable_if<std::numeric_limits<T>::is_integer, T>::type getContent() const
			{
				return static_cast<T>(std::stoull(mNodeContent));
			}

			/// Specialization for floating point number
			template <class T>
			typename std::enable_if<std::is_floating_point<T>::value, T>::type getContent() const
			{
				return static_cast<T>(std::stold(mNodeContent));
			}


			/// Function to check whatever or not this node as some content
			bool hasContent() const;

			/// Add an attribute to the node
			void addAttribute(const std::string& AttributeName, const std::string& AttributeContent);

			/// Get an attribute to the node
			/// Generic case
			const std::string& getAttribute(const std::string& AttributeName) const;

			template <class T>
			typename std::enable_if<!std::is_scalar<T>::value, T>::type getAttribute(const std::string& AttributeName) const
			{
				return static_cast<T>(mAttributes.at(AttributeName));
			}

			/// Specialization for non-floating point number
			template <class T>
			typename std::enable_if<std::numeric_limits<T>::is_integer, T>::type getAttribute(const std::string& AttributeName) const
			{
				return static_cast<T>(std::stoull(mAttributes.at(AttributeName)));
			}

			/// Specialization for floating point number
			template <class T>
			typename std::enable_if<std::is_floating_point<T>::value, T>::type getAttribute(const std::string& AttributeName) const
			{
				return static_cast<T>(std::stold(mAttributes.at(AttributeName)));
			}

			/// Function to check whatever or not this node as some content
			bool hasAttributes() const;

			/// Set the parent of this node
			void setParent(const Ptr ParentNode);

			/// Function to check whatever or not this node has a parent
			bool hasParent() const;

			/// Add an attribute to the node
			Ptr addChildNode();
			Ptr addChildNode(Ptr Child);
			Ptr addChildNode(const std::string& ChildName);
			Ptr addChildNode(const std::string& ChildName, const std::string& ChildContent);

			/// Functions to retrieve a child or a vector of child based on the supplied name
			Ptr getChildNode(const std::string& Name) const;
			TChildren getChildrenNodes(const std::string& Name, const std::size_t& Depth = 0) const;

			/// Remove a child
			void removeChildNode(Ptr Child);

			/// Function to check whatever or not this node has at least a child
			bool hasChildren() const;

			/// Render a node, return an XML formatted string of this node and all his child if it has some
			std::string renderNode(bool PrettyRendering = false, std::size_t Depth = 0);

		private:
			/// Return a string that contains only as many '\t' char as specified by NumberOfTab
			std::string printTabs(const std::size_t& NumberOfTab);

			/// Return a string with the formatted node name and attributes enclosed by the open and close tag
			std::string printBeginNodeNameTag(const std::string& Name, const TAttributes& Attributes);

			/// Return a string with the formatted node name enclosed by the '</ >' tag
			std::string printEndNodeNameTag(const std::string& Name);

		private:
			Ptr			mParentNode;
			TChildren	mChilds;
			std::string	mNodeName;
			std::string	mNodeContent;
			TAttributes	mAttributes;
		};
	}
}