#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <memory>

class Button : public sf::Drawable {
public:
    Button(const std::string& text, 
           const sf::Vector2f& position, 
           const sf::Vector2f& size,
           const sf::Font& font);
    
    void update(const sf::RenderWindow& window, const sf::Event& event);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    void setNormalColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);
    void setPressedColor(const sf::Color& color);
    void setText(const std::string& text);
    void setTextColor(const sf::Color& color);
    void setCharacterSize(unsigned int size);
    void setOnClick(std::function<void()> onClick);
    
    sf::FloatRect getGlobalBounds() const;
    void setPosition(const sf::Vector2f& position);

private:
    void updateAppearance();
    bool contains(const sf::Vector2f& point) const;
    void centerText();
    
    sf::RectangleShape m_shape;
    sf::Text m_text;
    sf::Color m_normalColor;
    sf::Color m_hoverColor;
    sf::Color m_pressedColor;
    bool m_isHovered;
    bool m_isPressed;
    std::function<void()> m_onClick;
};

#endif