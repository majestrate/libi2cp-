/*
  i2cp name lookup util
  copy wrong you're mom 2014 Jeff
 */
#include <i2cp/i2cp.hpp>
#include <iostream>

int main(int argc, char * argv[])
{
    if ( argc == 1 ) {
        std::cout << "usage: " << argv[0] << " name [ name ... ]" << std::endl;
        return 0;
    }
    i2cp::destination_ptr dest;
    for (int counter = 1; counter < argc; counter++) {
        std::string name(argv[counter]);
        I2CP_LOG("look up name: "+name);
        try {
            if ( i2cp::lookup(name, dest) ) { 
                std::cout << name << " is " << dest->Base32();
            } else {
                std::cout << "cannot resolve " << name;
            }
        } catch( std::exception & exc ) { 
            std::cout << "error resolving " << name;
            std::cout << " : " << exc.what(); 
        }
        std::cout << std::endl;
    }

}
