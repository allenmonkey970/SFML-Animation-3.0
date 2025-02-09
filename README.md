### SFML Animation Manager

This class provides an easy way to animate sprites in a game using the SFML Graphics library. The `AnimationManager` allows you to manage various animations for your game characters or objects. Below, you'll find a documentation and usage examples.

#### Overview

**Key Functions**:
- **`addAnimation`**: Add a new animation.
- **`update`**: Update the current frame of a specific animation.
- **`updateAll`**: Update all animations.
- **`deleteAnimation`**: Remove an animation.
- **Setters**: Modify properties of animations (e.g., frequency, sprite size, sheet size, etc.).

#### Example: Adding and Updating an Animation

##### Adding an Animation
First, you need to create an instance of the `AnimationManager` and add an animation. Here's how you can do it:

```cpp
#include "AnimationManager.hpp"
#include <SFML/Graphics.hpp>

// Load the animation sheet texture
sf::Texture animationSpritesheet;
animationSpritesheet.loadFromFile("path/to/file.png");

// Set the number of frames in the sheet and the size of each frame
sf::Vector2i frameRectangle(4, 4); // A total of 16 frames
sf::Vector2i spriteSize(64, 64);

// Create the AnimationManager instance and add the animation
AnimationManager am;
am.addAnimation("Walking", animationSpritesheet, frameRectangle, spriteSize);
```

##### Updating an Animation
To update the animation within your game loop, you can use the `update` method:

```cpp
// Our game loop
while (window.isOpen()) {
    ...
    am.update("Walking", sprite); // Update the animation frame
    ...
}
```

#### Optional Fields
There are additional fields that you can specify when adding an animation: frequency, starting/ending index, and current index. 

- **Frequency**: To update the sprite at a slower rate, use `setAnimationFrequency`:

```cpp
am.setAnimationFrequency("Walking", 2); // Update every other call
// Or
am.setAnimationFrequency("Walking", 3); // Update every 3rd call
```

- **Current Index**: To start the animation at a specific frame:

```cpp
am.setAnimationIndex("Walking", sf::Vector2i(2, 0)); // Start halfway through the 4x4 sheet
```

- **Resetting Index**: To reset the animation to the starting frame:

```cpp
am.resetAnimationIndex("Walking");
```

- **Starting/Ending Index**: To set specific start and end frames for animations within the same sprite sheet:

```cpp
am.setAnimationStartingIndex("Walking", sf::Vector2i(4, 4)); // Start frame
am.setAnimationEndingIndex("Walking", sf::Vector2i(8, 4));   // End frame
```

#### Full Usage with a Game Character

Below is a snippet showing how to integrate `AnimationManager` with a game character class. The `Slime` class demonstrates setting up multiple animations and updating them.

```cpp
#include "AnimationManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Slime {
public:
    Slime() : sprite(idleTexture), currentAnimation("idle") {
        setupAnimation(idleTexture, "idle", "assets/slime/Idle/idle.png", {7, 1}, {30, 27}, {0, 0}, 10);
        sprite.setTexture(idleTexture);
    }

    void setScale(const std::string& animationName, const sf::Vector2f& scale) {
        setTexture(animationName, scale);
        currentAnimation = animationName;
        AnimationManager::resetAnimationIndex(currentAnimation);
    }

    void draw(sf::RenderWindow& window) {
        AnimationManager::update(currentAnimation, sprite);
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;
    sf::Texture idleTexture;
    std::string currentAnimation;

    static void setupAnimation(sf::Texture& texture, const std::string& animationName,
                               const std::string& filePath, sf::Vector2i frameCount,
                               sf::Vector2i frameSize, sf::Vector2i startPosition, int frequency) {
        if (!texture.loadFromFile(filePath)) {
            std::cerr << "Failed to load texture: " << filePath << "\n";
        } else {
            AnimationManager::addAnimation(animationName, texture, frameCount, frameSize, startPosition, frequency);
        }
    }

    void setTexture(const std::string& animationName, const sf::Vector2f& scale) {
        if (animationName == "idle") {
            sprite.setTexture(idleTexture);
        }
        sprite.setScale(scale);
    }
};
```

##### Main Game Loop

Here's a sample main loop that integrates the `Slime` class:

```cpp
#include <SFML/Graphics.hpp>
#include "slime.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Adventure of the Slime");
    window.setFramerateLimit(60);

    Slime mainSlime;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        mainSlime.draw(window); // Draw the slime with its current animation frame
        window.display();
    }

    return 0;
}
```

---

### Changes from Original Code by [Jfeatherstone](https://github.com/Jfeatherstone/SFMLAnimation/tree/master)

1. **Include Directives**:
   - The new code includes `#include "AnimationManager.h"` and `#include <iostream>` directives at the beginning, which were not present in the old code.

2. **Static Member Variable Definitions**:
   - Static member variable definitions are now outside the class declaration and initialized using the `std::map` syntax.
   - The new code uses `std::map` for member variables, while the old code uses `map` (without the `std::` namespace prefix). This ensures proper namespace usage.

3. **Update Method**:
   - The `update` method in the new code increments `m_timesUpdated[animation]` and checks if it reaches `m_frequencies[animation]` before updating the sprite texture. If the frequency condition is met, it resets the `m_timesUpdated[animation]` counter and proceeds with updating the sprite texture.
   - The old code does not have this frequency-based update mechanism.

4. **Resetting Animation Indices**:
   - In the new code, when the end of the animation sheet is reached, the indices are reset to the `m_startingIndices[animation]` for looping animations.
   - The old code does not have this explicit reset mechanism.

5. **Error Handling**:
   - The new code uses `std::cerr` to output error messages when no animation entry is found, while the old code uses `cout`.

6. **Initialization in `addAnimation`**:
   - In the new code, `m_timesUpdated[animation]` is explicitly initialized to 0 in the `addAnimation` method.
   - The old code does not have this explicit initialization.

7. **Method Signatures**:
   - The new code uses `const std::string&` for string parameters in method signatures to avoid unnecessary copying of strings and improve performance.
   - The old code uses `string` directly in method signatures.

8. **Consistency in Naming**:
   - The new code consistently uses the `std` namespace (e.g., `std::map`, `std::string`) throughout the implementation.
