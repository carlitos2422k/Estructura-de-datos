#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
private:
    std::vector<sf::Text> options;
    sf::Font font;
    int selectedIndex;
    float padding;

public:
    Menu(const std::vector<std::string>& items, const sf::Font& font, float padding = 30.0f) 
        : selectedIndex(0), padding(padding) {
        this->font = font;
        for (const auto& item : items) {
            sf::Text text;
            text.setFont(font);
            text.setString(item);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            options.push_back(text);
        }
        updatePositions();
    }

    void draw(sf::RenderWindow& window) {
        for (size_t i = 0; i < options.size(); i++) {
            options[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
            window.draw(options[i]);
        }
    }

    void moveUp() {
        if (selectedIndex > 0) {
            selectedIndex--;
            updatePositions();
        }
    }

    void moveDown() {
        if (selectedIndex < options.size() - 1) {
            selectedIndex++;
            updatePositions();
        }
    }

    int getSelectedIndex() const {
        return selectedIndex;
    }

private:
    void updatePositions() {
        for (size_t i = 0; i < options.size(); i++) {
            float y = 100.0f + i * padding;
            options[i].setPosition(100.0f, y);
        }
    }
};