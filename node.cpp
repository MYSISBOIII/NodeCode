#include "raylib.h"

// Need this for uint16
#include <cstdint>

#include <vector>
#include <string>

// -------------------------------TODO LIST--------------------------------

// Learn what these flags mean
// g++ node.cpp -L. -lraylib -lopengl32 -lgdi32 -lwinmm -o node

// Structure the project more appropriately

// Empty strings as arguments might be bad

// Use CMake

// ------------------------------------------------------------------------

namespace ScreenConfig 
{
    uint16_t WIDTH;
    uint16_t HEIGHT;
}

namespace Colors 
{
    constexpr Color BACKGROUND = Color{125, 125, 125, 125}; 
    constexpr Color CURSOR = Color{255, 255, 255, 255};
    constexpr Color BUTTON = Color{205, 205, 205, 255};
    constexpr Color BUTTON_TEXT = Color{0, 150, 0, 255};
}

typedef std::string string;

class Button 
{

    string title;
    Vector2 position;
    int width, height;

    public:
        Button(const string name, const Vector2 pos, const int w, const int h, std::vector<Button>& array, void (*func)()) : title(name), position(pos), width(w), height(h), callback(func) 
        {
            // Makes it easier to determine which button was clicked
            array.push_back(*this);
        } 

        bool is_hovered(const Vector2 cursor) 
        {
            int x = cursor.x;
            int y = cursor.y;

            if (x > position.x && x < position.x + width && y > position.y && y < position.y + height) { return true; }

            return false;
        }

        string get_title() { return title; }

        Vector2 pos() { return position; }

        uint16_t get_width() { return width; }

        uint16_t get_height() { return height; }

        // Define the logic using a stateless lambda
        void (*callback)();
};

int main() 
{

    std::vector<Button> buttons;

    // Initialize window and OpenGL context
    InitWindow(1, 1, "");
    
    ToggleFullscreen();

    ScreenConfig::WIDTH = GetScreenWidth();
    ScreenConfig::HEIGHT = GetScreenHeight();
    
    Button("Exit", Vector2{static_cast<float>(ScreenConfig::WIDTH / 2), static_cast<float>(ScreenConfig::HEIGHT/2)}, 100, 100, buttons, []() 
    {
        CloseWindow();
        std::exit(0);
    });

    Image cursor_img = LoadImage("cursor.png");
    
    // Resize with respect to monitor size; native image too big
    ImageResize(&cursor_img, ScreenConfig::WIDTH / 55, ScreenConfig::WIDTH / 55);

    Texture2D cursor_texture = LoadTextureFromImage(cursor_img);
 
    Vector2 mouse_pos;


    // Prevents CPU from shitting itself
    SetTargetFPS(80);

    HideCursor();

    // Condition becomes true if KEY_ESCAPE pressed or windows closed
    while (!WindowShouldClose()) 
    {
        
        // Sets up framebuffer, which is a portion of memory that holds pixel data before drawn
        BeginDrawing();

            // Control background colour
            ClearBackground(Colors::BACKGROUND);

            // Draw all buttons
            for (Button button : buttons) 
            {

                Vector2 pos = button.pos();
                uint16_t width = button.get_width();
                uint16_t height = button.get_height();

                // Figure out a way to efficiently cache text measurement variables
                // First argument returns a const char*, raylib doesn't know how to process C++ strings
                DrawRectangle(button.pos().x, button.pos().y, button.get_width(), button.get_height(), Colors::BUTTON);
                
                // This is also weird
                uint16_t font_size = width * height / 100;
                
                string title = button.get_title();
                const char* title_ptr = title.c_str();

                uint8_t text_width = MeasureText(title_ptr, font_size);
                
                DrawText(title_ptr, pos.x + (width - text_width) / 2, pos.y + (height - font_size) / 2, font_size, Colors::BUTTON_TEXT);  
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                for (Button button : buttons) 
                {
                    if (button.is_hovered(mouse_pos)) 
                    {
                        (*button.callback)();
                    }
                }
            }

            mouse_pos = GetMousePosition();
            DrawTexture(cursor_texture, mouse_pos.x, mouse_pos.y, Colors::CURSOR);

        // Swap buffers (double buffering)
        EndDrawing();
    }

    CloseWindow();
    return 0;
}