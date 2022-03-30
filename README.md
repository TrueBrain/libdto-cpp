# LibDTO C++

A very simple proof-of-concept how to make a DTO library that can convert JSON to a C++ struct and back.

## Why does this exist?!

After seeing some examples on the Internet about how one could make a DTO library in C++, I got curious why they are all very complicated to follow.
So I gave it a spin myself.

`boost::json` has a pretty nice templated way to convert JSON to a struct and back.
The downside of this approach is that the information is three times in memory:
- The raw JSON string.
- The boost converted object.
- The actual struct.

So by using `boost::json` there seems to be some overhead in terms of memory.

By using `boost::json`, it turned out it was relative easy to convert a DTO to JSON and back.
Just you had to repeat the members of the struct in various of places, making adding new structs a bit annoying.

As I was using boost anyway, I looked at `boost::hana`, which allows for iterating the members of a struct.
This turned out to be a pretty nifty solution, and avoided code duplication.
The only penalty is that you need an extra line of code after each struct to let `boost::hana` do its magic.
Lastly, the `BOOST_HANA_ADAPT_STRUCT` has to be done on the global level, making the code look slightly off.

One could opt for `BOOST_HANA_DEFINE_STRUCT`, but that makes the structs harder to read for everyone.

Lastly, I wanted to have a clean way to serialize/deserialize to JSON, but allow future expansion into YAML, protobuf, ...
As such, I opt'd for a `serialize::json` namespace, which takes away the slight magic around JSON serialization with `boost::json`.

One can argue that `serialize/json.hpp` should be two files, but that is bikeshedding.

## Compiling

Install boost 1.75+.
Run:

```bash
g++ -std=c++17 -o dto main.cpp
```

Use `-I <boostpath>` if you don't have the installed boost in your default include path.
Now simply run `./dto`, and see that it actually works.
