#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "resource_holder.hpp"
#include "scene_node.hpp"
#include "aircraft.hpp"

class World : private sf::NonCopyable
{
	public:
		explicit World(sf::RenderWindow& window);

	private:
		sf::RenderWindow& mWindow;
		sf::View mWorldView;
		TextureHolder mTexture;
		SceneNode mSceneGraph;
		std::array<SceneNode*, LayerCount> mSceneLayer;
		sf::FloatRect mWorldBounds;
		sf::Vector2f mSpawnPosition;
		float mScrollSpeed;
		Aircraft* mPlayerAircraft;
};

#endif //__WORLD_HPP__
