#include "lang/texts.h"
#include "io/io.h"
#include <iostream>
#include <cstdlib>

using namespace arena;

int main()
{
    std::system("cls");

    std::optional<int> x = arena::print_and_get_choices(
        arena::dialog::menu_title, 
        arena::dialog::menu_options
    );
    
    if (x)
    {
        std::cout << *x << '\n';
    }
    return 0;
}
