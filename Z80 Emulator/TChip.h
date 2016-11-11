#pragma once

#include <SFML/Config.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

#include "IComponent.h"
#include "TPinComponent.h"
#include "TDrawableVector.h"
#include "TEntity.h"

namespace nne
{
	class TChip : public IComponent
	{
	public:
		enum class TPackage
		{
			DIP,
			SOIC,
			LQFP
		};

		TChip(TEntity* ManagedObject) :
			mManagedObject(ManagedObject)
		{
		}

		void Init() override
		{
			mObjectShape = std::make_shared<sf::VertexArray>(sf::Quads);
			mParent->GetComponentAsPtr<TDrawableVector>()->PushDrawableObject(mObjectShape);

			RenderDipChip();
		}

		void Update() override {}

		void Refresh() override {}

		void SetSize(const sf::Vector2f& Size)
		{
			auto& Vertices = *mObjectShape;

			Vertices[0].position = { 0.f, 0.f };
			Vertices[1].position = { Size.x, 0.f };
			Vertices[2].position = Size; // { Size.x, Size.y };
			Vertices[3].position = { 0.f, Size.y };
		}

		void SetChipColor(const sf::Color& Color)
		{
			auto& Vertices = *mObjectShape;

			Vertices[0].color = Color;
			Vertices[1].color = Color;
			Vertices[2].color = Color;
			Vertices[3].color = Color;
		}

	private:
		void RenderDipChip()
		{
			/// Get the number of pins
			sf::Uint8 NumberOfPins = mManagedObject->GetComponentAsPtr<tcomponents::TPinComponent>()->GetPinList().size();
			auto& Vertices = *mObjectShape;

			//sf::Uint8 NumberOfPins = 28;

			// Create a vertex array big enough to fit all the pins and the chip base
			Vertices.resize(NumberOfPins * 8 + 4);

			// Set the chip's base properties
			//SetSize({ 403.f, 793.f });
			SetSize({ 403.f, (21.f * NumberOfPins / 2 + 33.f * (NumberOfPins / 2 - 1)) + 70.f });

			SetChipColor(sf::Color(30, 30, 30));

			// Set the chip's pins properties
			for (std::size_t Index = 4, PinCounter = 0; Index < Vertices.getVertexCount(); Index += 8, ++PinCounter)
			{
				// Pin properties
				sf::Vector2f BottomPinSize = { 82.f, 21.f };
				sf::Vector2f TopPinSize = { 31.f, 21.f };

				sf::Color BottomPinColor = { 120, 120, 120 };
				sf::Color TopPinColor = { 60, 60, 60 };


				auto Median = NumberOfPins / 2;
				sf::Vector2f BottomPinOffset = { PinCounter < Median ? -82.f : 403.f, 54.f * (PinCounter < Median ? PinCounter : PinCounter - Median) + 35.f };
				sf::Vector2f TopPinOffset = { PinCounter < Median ? -31.f : 403.f, 54.f * (PinCounter < Median ? PinCounter : PinCounter - Median) + 35.f };

				sf::Vector2f PinYOffset = { 0.f, 35.f };

				// Bottom PIN portion

				// Pin Size {82.f, 21.f}
				Vertices[Index + 0].position = { 0.f,  0.f };
				Vertices[Index + 1].position = { BottomPinSize.x,  0.f };
				Vertices[Index + 2].position = { BottomPinSize.x, BottomPinSize.y };
				Vertices[Index + 3].position = { 0.f, BottomPinSize.y };

				// Pin Offset first {82.f, 35.f}
				Vertices[Index + 0].position += BottomPinOffset;
				Vertices[Index + 1].position += BottomPinOffset;
				Vertices[Index + 2].position += BottomPinOffset;
				Vertices[Index + 3].position += BottomPinOffset;

				// Pin Color
				Vertices[Index + 0].color = BottomPinColor;
				Vertices[Index + 1].color = BottomPinColor;
				Vertices[Index + 2].color = BottomPinColor;
				Vertices[Index + 3].color = BottomPinColor;

				// Top PIN portion

				// Pin Size {31.f, 21.f}
				Vertices[Index + 4].position = { 0.f,  0.f };
				Vertices[Index + 5].position = { TopPinSize.x,  0.f };
				Vertices[Index + 6].position = { TopPinSize.x, TopPinSize.y };
				Vertices[Index + 7].position = { 0.f,  TopPinSize.y };

				// Pin Offset first {31.f, 35.f}
				Vertices[Index + 4].position += TopPinOffset;
				Vertices[Index + 5].position += TopPinOffset;
				Vertices[Index + 6].position += TopPinOffset;
				Vertices[Index + 7].position += TopPinOffset;

				// Pin Color
				Vertices[Index + 4].color = TopPinColor;
				Vertices[Index + 5].color = TopPinColor;
				Vertices[Index + 6].color = TopPinColor;
				Vertices[Index + 7].color = TopPinColor;
			}			
		}

	private:
		nne::TEntity* mManagedObject;
		std::shared_ptr<sf::VertexArray> mObjectShape;
	};
}