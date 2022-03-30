#include <string>
#include <boost/json.hpp>
#include <boost/hana.hpp>

/* This file contains code to convert a DTO to JSON and back.
 * It uses boost::hana to iterate over the members of a struct, as otherwise you need to repeat the members here twice.
 * All DTOs have boost::hana around them.
 */

namespace messagecatalog {
    template<class T>
    void extract( boost::json::object const& obj, T& t, boost::json::string_view key )
    {
        t = boost::json::value_to<T>( obj.at( key ) );
    }

    template<class TMessage>
    void tag_invoke( boost::json::value_from_tag, boost::json::value& jv, TMessage const& m )
    {
        boost::json::object obj;

        /* Iterate over all the keys that exist in the struct, converting them to the JSON object. */
        boost::hana::for_each(boost::hana::keys(m), [&m, &obj](const auto& key) {
            obj[key.c_str()] = boost::hana::at_key(m, key);
        });

        jv = obj;
    }

    template<class TMessage>
    TMessage tag_invoke( boost::json::value_to_tag< TMessage >, boost::json::value const& jv )
    {
        boost::json::object const& obj = jv.as_object();

        TMessage m;
        /* Iterate over all the keys that exist in the struct, extracting them from the JSON object. */
        boost::hana::for_each(boost::hana::keys(m), [&m, &obj](const auto& key) {
            extract( obj, boost::hana::at_key(m, key), key.c_str() );
        });
        return m;
    }
};

namespace serialize {
namespace json {

    template <class TMessage>
    static std::string to(TMessage m) {
        return boost::json::serialize(boost::json::value_from(m));
    }

    template <class TMessage>
    static TMessage from(std::string &data) {
        auto jv = boost::json::parse(data);
        return TMessage(boost::json::value_to<TMessage>(jv));
    }

}
}
