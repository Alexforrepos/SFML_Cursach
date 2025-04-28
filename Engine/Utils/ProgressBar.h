#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class ProgressBar
{
private:
    float progress = 0.f;
    float step = 0.f;
    uint16_t bar_step = 0;

    sf::RectangleShape progressBar;
    sf::RectangleShape backgroundBar;
    sf::Text progressText;
    std::shared_ptr<sf::Font> font;

    sf::Color fillColor = sf::Color::Green;
    sf::Color backgroundColor = sf::Color(70, 70, 70);
    sf::Color outlineColor = sf::Color::White;
    sf::Color textColor = sf::Color::White;

    bool showText = true;
    bool showPercentage = true;

public:
    ProgressBar(int totalElements, const sf::Vector2f& size = { 400.f, 30.f },
        const sf::Vector2f& position = { 300.f, 300.f })
    {
       
        step = 1.f / totalElements;
        bar_step = static_cast<uint16_t>(size.x / totalElements);

      
        backgroundBar.setSize(size);
        backgroundBar.setFillColor(backgroundColor);
        backgroundBar.setOutlineThickness(2.f);
        backgroundBar.setOutlineColor(outlineColor);
        backgroundBar.setPosition(position);

       
        progressBar.setSize({ 0.f, size.y });
        progressBar.setFillColor(fillColor);
        progressBar.setPosition(position);

    }

    void setFillColor(const sf::Color& color) {
        fillColor = color;
        progressBar.setFillColor(fillColor);
    }

    void setBackgroundColor(const sf::Color& color) {
        backgroundColor = color;
        backgroundBar.setFillColor(backgroundColor);
    }

    void setOutlineColor(const sf::Color& color) {
        outlineColor = color;
        backgroundBar.setOutlineColor(outlineColor);
    }

    void setTextColor(const sf::Color& color) {
        textColor = color;
        if (showText) progressText.setFillColor(textColor);
    }

    void setShowText(bool show) { showText = show && (font != nullptr); }
    void setShowPercentage(bool show) { showPercentage = show; }

    void increment() {
        if (progress < 1.f) {
            progress += step;
            progressBar.setSize({
                progress * backgroundBar.getSize().x,
                progressBar.getSize().y
                });
            updateText();
        }
    }

    void setProgress(float newProgress) {
        progress = std::clamp(newProgress, 0.f, 1.f);
        progressBar.setSize({
            progress * backgroundBar.getSize().x,
            progressBar.getSize().y
            });
        updateText();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(backgroundBar);
        window.draw(progressBar);
        if (showText) {
            window.draw(progressText);
        }
    }

    bool isComplete() const { return progress >= 1.f; }
    float getProgress() const { return progress; }

private:
    void updateText() {
        if (!showText) return;

        if (showPercentage) {
            int percentage = static_cast<int>(progress * 100);
            progressText.setString(std::to_string(percentage) + "%");
        }
        else {
            progressText.setString(std::to_string(static_cast<int>(progress * 100 / step)) +
                "/" + std::to_string(static_cast<int>(1.f / step)));
        }
    }
};

