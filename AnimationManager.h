#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

// This header file defines the AnimationManager class, which manages animations
// for game sprites using the SFML Graphics library. The class provides functions to:
// - Add, update, and delete animations.
// - Set various animation properties such as frequency, sprite size, sheet size, and indices.
// - Store animation data in static member variables (textures, indices, sizes, frequencies, etc.).
// The class includes several private static member variables to store animation data
// and public static member functions to manage animations.

class AnimationManager {
private:
    // Static member variables to store animation data
    static std::map<std::string, sf::Texture> m_textures;      // Textures of animations
    static std::map<std::string, sf::Vector2i> m_indices;      // Current indices of animations
    static std::map<std::string, sf::Vector2i> m_startingIndices; // Starting indices of animations
    static std::map<std::string, sf::Vector2i> m_endingIndices; // Ending indices of animations
    static std::map<std::string, sf::Vector2i> m_sheetSizes;   // Sizes of animation sheets
    static std::map<std::string, sf::Vector2i> m_spriteSizes;  // Sizes of animation sprites
    static std::map<std::string, int> m_frequencies;           // Frequencies of updates
    static std::map<std::string, int> m_timesUpdated;          // Times updated counters

public:
    // Function to update the animation frame for a specific sprite
    static void update(const std::string &animation, sf::Sprite &sprite);

    // Function to update all animations in a given map of sprites
    static void updateAll(std::map<std::string, sf::Sprite> &map);

    // Function to add a new animation with the specified parameters
    static void addAnimation(const std::string &animation, const sf::Texture &texture,
                             sf::Vector2i sheetSize, sf::Vector2i spriteSize,
                             sf::Vector2i index = {0, 0}, int frequency = 0,
                             sf::Vector2i startingIndex = {0, 0});

    // Function to delete an existing animation
    static void deleteAnimation(const std::string &animation);

    // Setter functions to modify animation properties
    static void setAnimationFrequency(const std::string &animation, int frequency);
    static void setAnimationSpriteSize(const std::string &animation, sf::Vector2i size);
    static void setAnimationSheetSize(const std::string &animation, sf::Vector2i size);
    static void setAnimationIndex(const std::string &animation, sf::Vector2i index);
    static void setAnimationTexture(const std::string &animation, const sf::Texture &texture);
    static void setAnimationStartingIndex(const std::string &animation, sf::Vector2i index);
    static void setAnimationEndingIndex(const std::string &animation, sf::Vector2i index);

    // Function to reset the animation index to the starting index
    static void resetAnimationIndex(const std::string &animation);
};