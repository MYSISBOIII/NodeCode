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

// Spiff up the GUI, and replace font

// Very helpful blog post: https://austinhenley.com/blog/teenytinycompiler1.html, it would be more relevant to place this elsewhere but the file structure is gonna get massively changed anyway
// Was helpful, but started figuring out how to classifying tokens on my own, and from here on out, I'll try making the compiler on my own

// You don't have to include some of the libraries in main if they're already in .h

// It would look way cleaner/be a lot more readable, if you delete the get methods and just make all members public

// Check parameter types and names for functions and make sure you keep a pattern

// Use enum class instead

// ifdef directives?

// Make habit of using const in argument

// Class private and public indentation

// SET UP FAILGUARDS!!!!!!

// Maybe make compiler based on minheap? How would that work?

// Add more cases in lexer.cpp

// IF ELSE SYNTAX 

// check set identifiers, iterating funny

// Delete get_next_char

// Node class placed where they aren't supposed to be, for convenience

// Add more comments

// templates might be written weirdly

// ------------------------------------------------------------------------

typedef std::string string;

enum class ButtonState 
{
    MENU,
    EDITOR,
    SETTINGS
};

namespace ScreenConfig 
{
    float WIDTH;
    float HEIGHT;
}

namespace Colors 
{
    constexpr Color BACKGROUND = Color{125, 125, 125, 125}; 
    constexpr Color CURSOR = Color{255, 255, 255, 255};
    constexpr Color BUTTON = Color{205, 205, 205, 255};
    constexpr Color BUTTON_TEXT = Color{0, 150, 0, 255};
}

class Button 
{

    string title;
    Vector2 position;
    uint16_t width, height;
    ButtonState state;

    public:
        // These parameter names are very funky, this needs to be fixed
        Button(const string name, const Vector2 pos, const uint16_t w, const uint16_t h, std::vector<Button>& array, ButtonState parent, void (*func)(ButtonState&)) : title(name), position(pos), width(w), height(h), state(parent), callback(func)
        {
            // Makes it easier to determine which button was clicked
            array.push_back(*this);
        } 

        bool is_hovered(const Vector2 cursor) 
        {
            uint16_t x = cursor.x;
            uint16_t y = cursor.y;

            if (x > position.x && x < position.x + width && y > position.y && y < position.y + height) { return true; }

            return false;
        }

        string get_title() { return title; }

        Vector2 pos() { return position; }

        uint16_t get_width() { return width; }

        uint16_t get_height() { return height; }

        ButtonState get_state() { return state; }

        // Define the logic using a stateless lambda
        void (*callback)(ButtonState&);

        void set_width(uint16_t new_width) { width = new_width; }
};

int main() 
{

    std::vector<Button> buttons;
    ButtonState current_state = ButtonState::MENU;

    // Initialize window and OpenGL context
    InitWindow(1, 1, "");
    
    ToggleFullscreen();

    ScreenConfig::WIDTH = GetScreenWidth();
    ScreenConfig::HEIGHT = GetScreenHeight();

    
    // ---------- MAIN MENU BUTTONS ----------
    
    Button("Editor", Vector2{ScreenConfig::WIDTH / 7, ScreenConfig::HEIGHT / 5}, 150, ScreenConfig::HEIGHT / 10, buttons, ButtonState::MENU, [](ButtonState& state) 
    {
        state = ButtonState::EDITOR;
    });

    Button("Settings", Vector2{ScreenConfig::WIDTH / 7, ScreenConfig::HEIGHT / 5 * 2}, 150, ScreenConfig::HEIGHT / 10, buttons, ButtonState::MENU, [](ButtonState& state) 
    {
        state = ButtonState::SETTINGS;
    });

    Button("Quit", Vector2{ScreenConfig::WIDTH / 7, ScreenConfig::HEIGHT / 5 * 3}, 150, ScreenConfig::HEIGHT / 10, buttons, ButtonState::MENU, [](ButtonState& state) 
    {
        CloseWindow();
        std::exit(0);
    });

    // ---------- SETTINGS BUTTONS ----------

    Button("Back", Vector2{ScreenConfig::HEIGHT / 4, ScreenConfig::WIDTH / 2}, 1, ScreenConfig::HEIGHT / 10, buttons, ButtonState::SETTINGS, [](ButtonState& state) 
    {
        state = ButtonState::MENU;
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

            mouse_pos = GetMousePosition();

            // Control background colour
            ClearBackground(Colors::BACKGROUND);

            // Draw all buttons
            for (Button& button : buttons) 
            {
                // Ignore all buttons that aren't supposed to be rendered
                if (button.get_state() != current_state) { continue; }


                Vector2 pos = button.pos();
                uint16_t width = button.get_width();
                uint16_t height = button.get_height();

                
                // This is also weird
                uint16_t font_size = static_cast<uint16_t>(height * 0.5f);
                
                string title = button.get_title();
                const char* title_ptr = title.c_str();

                uint8_t text_width = MeasureText(title_ptr, font_size);
                
                // Figure out a way to efficiently cache text measurement variables
                // First argument returns a const char*, raylib doesn't know how to process C++ strings
                
                // If the text is too large, increase box width to compensate
                if (text_width > width) { button.set_width(width += 2 * (text_width - width)); }
                
                DrawRectangle(pos.x, pos.y, width, height, Colors::BUTTON);
                
                DrawText(title_ptr, pos.x + (width - text_width) / 2, pos.y + (height - font_size) / 2, font_size, Colors::BUTTON_TEXT);  
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                for (Button& button : buttons) 
                {
                    if (button.get_state() != current_state) { continue; }
                    
                    if (button.is_hovered(mouse_pos)) 
                    {
                        (*button.callback)(current_state);
                    }
                }
            }

            DrawTexture(cursor_texture, mouse_pos.x, mouse_pos.y, Colors::CURSOR);

        // Swap buffers (double buffering)
        EndDrawing();
    }

    CloseWindow();
    return 0;
}