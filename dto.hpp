#include <string>
#include <boost/hana.hpp>

namespace messagecatalog {
    struct MyMessage {
        int version;
        std::string message;
        float value;
    };
};
BOOST_HANA_ADAPT_STRUCT(messagecatalog::MyMessage, version, message, value);

namespace messagecatalog {
    struct MySecondMessage {
        std::string text;
    };
};
BOOST_HANA_ADAPT_STRUCT(messagecatalog::MySecondMessage, text);
