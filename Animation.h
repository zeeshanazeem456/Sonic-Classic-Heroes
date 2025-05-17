#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Animation {
    Clock clk;
public:

    // Run ke liye function
    void Run(Sprite& sprite, int totalFrames, Clock& clock, int& currentFrame, int frameWidth, int frameHeight) {

        // 60 seconds ke baad naya frame
        if (clk.getElapsedTime().asMilliseconds() >= 60) {
            currentFrame++;
            // Agr frame ki limit se zyada hogaya toh currentFrame ko wapas zero pr krdo
            if (currentFrame >= totalFrames) {
                currentFrame = 0;
            }

            // PNG ka kuch hissa uthao aur sprite mein dal do
            sprite.setTextureRect(IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));

            // clock ko reset krdo
            clk.restart();
        }
    }


    // Run ke liye function
    void Jump(Sprite& sprite, int totalFrames, Clock& clock, int& currentFrame, int frameWidth, int frameHeight) {

        // 60 seconds ke baad naya frame
        if (clk.getElapsedTime().asMilliseconds() >= 60) {
            currentFrame++;

            // Agr frame ki limit se zyada hogaya toh currentFrame ko wapas zero pr krdo
            if (currentFrame >= totalFrames) {
                currentFrame = 0;
            }

            // PNG ka kuch hissa uthao aur sprite mein dal do
            sprite.setTextureRect(IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));

            // clock ko reset krdo
            clk.restart();
        }
    }
    void coinAnimation(Sprite& sprite, int totalFrames, Clock& clock, int& currentFrame, int frameWidth, int frameHeight){
        if (clock.getElapsedTime().asMilliseconds() >= 60) {
            currentFrame++;

            if (currentFrame >= totalFrames) {
                currentFrame = 0;
            }

            sprite.setTextureRect(IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            clock.restart();
        }
    }

};