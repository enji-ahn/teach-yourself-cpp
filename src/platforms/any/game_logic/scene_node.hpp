#ifndef __SCENE_NODE_HPP__
#define __SCENE_NODE_HPP__

#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable,
				  public sf::Drawable,
				  private sf::NonCopyable
{
};

#endif // __SCENE_NODE_HPP__

