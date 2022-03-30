#include <iostream>
#include <boost/json/src.hpp>

#include "dto.hpp"
#include "serialize/json.hpp"


int main() {
    {
        messagecatalog::MyMessage m = { 1, "abc", 5.1 };

        auto data = serialize::json::to(m);
        auto m2 = serialize::json::from<messagecatalog::MyMessage>(data);

        std::cout << "Version: " << m2.version << "\nMessage: " << m2.message << "\nValue:   " << m2.value << std::endl;
    }

    {
        messagecatalog::MySecondMessage m = { "test" };

        auto data = serialize::json::to(m);
        auto m2 = serialize::json::from<messagecatalog::MySecondMessage>(data);

        std::cout << "Text: " << m2.text << std::endl;
    }
}
