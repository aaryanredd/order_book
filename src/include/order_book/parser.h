#pragma once
#include "nlohmann/json.hpp"
#include "order_book.h"
#include <vector>

namespace parser
{
    /**
     * Class to parse json data to STL containers and primitive data types. 
     * User shall invoke this object and pass the json and insert into the order_book without having to write a conversion function.
    */
    class parser
    {       
        public:
            /**
             * Takes input json to feed the snapshot, convert and pass to the input_stream function of the order_book_handler class
            */
            void input_snapshot(nlohmann::json& sample);
            
            /**
             * Takes input json to feed the stream, convert and pass to the input_stream function of the order_book_handler class
            */
            void input_stream(nlohmann::json& sample);

            /**
             * This destructor is to enable few to be compatible with testing structure. Meant to be removed. 
            */
            ~parser();
    };
}