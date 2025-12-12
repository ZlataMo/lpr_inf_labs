#include "Button.hpp"
#include <iostream>

Button::Button(const std::string& text, 
               const sf::Vector2f& position, 
               const sf::Vector2f& size,
               const sf::Font& font)
    : m_isHovered(false)
    , m_isPressed(false)
    , m_onClick(nullptr)
{
    m_shape.setPosition(position);
    m_shape.setSize(size);
    m_text.setFont(font); 
    m_text.setString(text);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::White);
    
    m_normalColor = sf::Color(70, 130, 180);
    m_hoverColor = sf::Color(100, 149, 237);
    m_pressedColor = sf::Color(65, 105, 225);
    
    centerText();
    updateAppearance();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
    target.draw(m_text, states);
}

void Button::update(const sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    
    m_isHovered = contains(mousePos);
    
    switch (event.type) {
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left && m_isHovered) {
                m_isPressed = true;
            }
            break;
            
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (m_isPressed && m_isHovered && m_onClick) {
                    m_onClick();
                }
                m_isPressed = false;
            }
            break;
    }
    
    updateAppearance();
}

void Button::updateAppearance() {
    if (m_isPressed && m_isHovered) {
        m_shape.setFillColor(m_pressedColor);
    } else if (m_isHovered) {
        m_shape.setFillColor(m_hoverColor);
    } else {
        m_shape.setFillColor(m_normalColor);
    }
}

bool Button::contains(const sf::Vector2f& point) const {
    return m_shape.getGlobalBounds().contains(point);
}

void Button::centerText() {
    sf::FloatRect textBounds = m_text.getLocalBounds();
    sf::FloatRect buttonBounds = m_shape.getGlobalBounds();
    
    float centerX = buttonBounds.left + buttonBounds.width / 2.0f;
    float centerY = buttonBounds.top + buttonBounds.height / 2.0f;
    
    m_text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                     textBounds.top + textBounds.height / 2.0f);
    m_text.setPosition(centerX, centerY);
}

void Button::setNormalColor(const sf::Color& color) {
    m_normalColor = color;
    updateAppearance();
}

void Button::setHoverColor(const sf::Color& color) {
    m_hoverColor = color;
    updateAppearance();
}

void Button::setPressedColor(const sf::Color& color) {
    m_pressedColor = color;
    updateAppearance();
}

void Button::setText(const std::string& text) {
    m_text.setString(text);
    centerText();
}

void Button::setTextColor(const sf::Color& color) {
    m_text.setFillColor(color);
}

void Button::setCharacterSize(unsigned int size) {
    m_text.setCharacterSize(size);
    centerText();
}

void Button::setOnClick(std::function<void()> onClick) {
    m_onClick = onClick;
}

sf::FloatRect Button::getGlobalBounds() const {
    return m_shape.getGlobalBounds();
}

void Button::setPosition(const sf::Vector2f& position) {
    m_shape.setPosition(position);
    centerText();
}