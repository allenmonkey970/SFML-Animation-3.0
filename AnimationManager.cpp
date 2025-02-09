#include "AnimationManager.h"
#include <iostream>

// This implementation file provides the definitions for the member functions declared
// in the AnimationManager class. The key functionalities implemented include:
// - update: Updates the animation frame for a specific sprite based on the animation's frequency.
// - updateAll: Updates all animations in a given map of sprites.
// - addAnimation: Adds a new animation with specified parameters (texture, sheet size, sprite size, etc.).
// - deleteAnimation: Deletes an existing animation.
// - Setters: Modify animation properties such as frequency, sprite size, sheet size, and indices.
// The file initializes the static member variables and provides the logic for updating and managing
// animations in a game. Error handling and frequency-based updates are also implemented to ensure
// smooth animation transitions.

// Initialize static member variables
std::map<std::string, sf::Texture> AnimationManager::m_textures;
std::map<std::string, sf::Vector2i> AnimationManager::m_indices;
std::map<std::string, sf::Vector2i> AnimationManager::m_startingIndices;
std::map<std::string, sf::Vector2i> AnimationManager::m_endingIndices;
std::map<std::string, sf::Vector2i> AnimationManager::m_sheetSizes;
std::map<std::string, sf::Vector2i> AnimationManager::m_spriteSizes;
std::map<std::string, int> AnimationManager::m_frequencies;
std::map<std::string, int> AnimationManager::m_timesUpdated;

void AnimationManager::update(const std::string &animation, sf::Sprite &sprite) {
    // Check if the animation sheet size is valid
    if (m_sheetSizes[animation] != sf::Vector2i(0, 0)) {
        // Increment the update counter and check if it meets the frequency condition
        if (++m_timesUpdated[animation] >= m_frequencies[animation]) {
            m_timesUpdated[animation] = 0; // Reset the update counter

            // Calculate the texture rectangle for the current frame
            sf::IntRect rect({
                                 m_indices[animation].x * m_spriteSizes[animation].x,
                                 m_indices[animation].y * m_spriteSizes[animation].y
                             },
                             {m_spriteSizes[animation].x, m_spriteSizes[animation].y});

            // Set the sprite texture and texture rectangle
            sprite.setTexture(m_textures[animation]);
            sprite.setTextureRect(rect);

            // Update the animation indices to the next frame
            if (m_indices[animation].y < m_sheetSizes[animation].y - 1) {
                ++m_indices[animation].y;
            } else if (m_indices[animation].x < m_sheetSizes[animation].x - 1) {
                m_indices[animation].y = 0;
                ++m_indices[animation].x;
            } else {
                m_indices[animation] = m_startingIndices[animation]; // Reset to starting index for looping animation
            }
        }
    } else {
        // Output an error message if no animation entry is found
        std::cerr << "No animation entry found for \"" << animation << "\"!" << std::endl;
    }
}

void AnimationManager::updateAll(std::map<std::string, sf::Sprite> &map) {
    // Iterate through the map and update each animation
    for (auto &element: map) {
        update(element.first, element.second);
    }
}

void AnimationManager::addAnimation(const std::string &animation, const sf::Texture &texture,
                                    sf::Vector2i sheetSize, sf::Vector2i spriteSize,
                                    sf::Vector2i index, int frequency,
                                    sf::Vector2i startingIndex) {
    // Add a new animation with the specified parameters
    m_textures[animation] = texture;
    m_sheetSizes[animation] = sheetSize;
    m_spriteSizes[animation] = spriteSize;
    m_indices[animation] = index;
    m_startingIndices[animation] = startingIndex;
    m_endingIndices[animation] = sheetSize;
    m_frequencies[animation] = frequency;
    m_timesUpdated[animation] = 0; // Initialize the times updated counter
}

void AnimationManager::deleteAnimation(const std::string &animation) {
    // Remove the animation entry from all maps
    m_textures.erase(animation);
    m_indices.erase(animation);
    m_startingIndices.erase(animation);
    m_endingIndices.erase(animation);
    m_sheetSizes.erase(animation);
    m_spriteSizes.erase(animation);
    m_frequencies.erase(animation);
    m_timesUpdated.erase(animation);
}

void AnimationManager::setAnimationFrequency(const std::string &animation, int frequency) {
    // Set the update frequency for the specified animation
    m_frequencies[animation] = frequency;
}

void AnimationManager::setAnimationSpriteSize(const std::string &animation, sf::Vector2i size) {
    // Set the sprite size for the specified animation
    m_spriteSizes[animation] = size;
}

void AnimationManager::setAnimationSheetSize(const std::string &animation, sf::Vector2i size) {
    // Set the sheet size for the specified animation
    m_sheetSizes[animation] = size;
}

void AnimationManager::setAnimationIndex(const std::string &animation, sf::Vector2i index) {
    // Set the current index for the specified animation
    m_indices[animation] = index;
}

void AnimationManager::setAnimationTexture(const std::string &animation, const sf::Texture &texture) {
    // Set the texture for the specified animation
    m_textures[animation] = texture;
}

void AnimationManager::resetAnimationIndex(const std::string &animation) {
    // Reset the current index to the starting index for the specified animation
    m_indices[animation] = m_startingIndices[animation];
}

void AnimationManager::setAnimationStartingIndex(const std::string &animation, sf::Vector2i index) {
    // Set the starting index for the specified animation
    m_startingIndices[animation] = index;
}

void AnimationManager::setAnimationEndingIndex(const std::string &animation, sf::Vector2i index) {
    // Set the ending index for the specified animation
    m_endingIndices[animation] = index