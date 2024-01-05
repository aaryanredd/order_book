#include <vector>
#include <map>
#include <iostream>
#include "gtest/gtest.h"
#include "nlohmann/json.hpp"
#include "order_book/parser.h"
#include "order_book/order_book.h"

/**
 * Add your json test here into the vector of jsons
*/
std::vector<nlohmann::json> samples = {R"(
    {
      "snapshots": [
        {
          "symbol" : "BNBBTC",
          "bids" : [
            ["0.0024","14.70000000"],
            ["0.0022","6.40000000"],
            ["0.0020","9.70000000"]
          ],
          "asks": [
            ["0.0024","14.90000000"],
            ["0.0026","3.60000000"],
            ["0.0028","1.00000000"]
          ]
        }
      ]
    ,
    "updates":
        [{
            "e" : "depthUpdate",
            "s" : "BNBBTC",
            "b" : [["0.0024","10"]],
            "a" : [["0.0026","100"]]
        },
        {
            "e" : "depthUpdate",
            "s" : "BNBBTC",
            "b" : [["0.0024","8"]],
            "a" : [["0.0026","0"]]
        },
        {
            "e" : "depthUpdate",
            "s" : "BNBBTC",
            "b" : [["0.0024","0"]],
            "a" : [["0.0026","15"],["0.0027","5"]]
        },
                {
            "e" : "depthUpdate",
            "s" : "BNBBTC",
            "b" : [["0.0025","100"]],
            "a" : [["0.0026","0"],["0.0027","5"]]
        },
                {
            "e" : "depthUpdate",
            "s" : "BNBBTC",
            "b" : [["0.0025","0"]],
            "a" : [["0.0026","15"],["0.0024","0"]]
        }]
    }
  )"_json,
  R"(
    {
      "snapshots": [
        {
          "symbol" : "BNBBTC",
          "bids" : [
            ["0.0024","14.70000000"],
            ["0.0022","6.40000000"],
            ["0.0020","9.70000000"]
          ],
          "asks": [
          ]
        }
      ]
    ,
    "updates":
        [{
            "e" : "depthUpdate",
            "s" : "BNBBTC",
            "b" : [["0.0024","10"]],
            "a" : []
        },
        {
            "e" : "depthUpdate",
            "s" : "BNBBTC",
            "b" : [["0.0024","8"]],
            "a" : []
        },
        {
            "e" : "depthUpdate",
            "s" : "BNBBTC",
            "b" : [["0.0024","0"]],
            "a" : []
        },
                {
            "e" : "depthUpdate",
            "s" : "BNBBTC",
            "b" : [["0.0025","100"]],
            "a" : []
        },
                {
            "e" : "depthUpdate",
            "s" : "BNBBTC",
            "b" : [["0.0025","0"]],
            "a" : []
        }]
    }
  )"_json,
};

/**
 * At the same index mention the best prices expected after the input is complete. First is for bids and second for Asks
*/
std::vector<std::pair<double, double>> best_prices = {
    {0.0025,0.0024},
    {0.0025,0},
    };

/**
 * At the same index mention the empty statuses expected after the input is complete. First is for bids and second for Asks
*/
std::vector<std::pair<bool, bool>> empty_status = {
    {false,false},
    {false, true},
    };

/**
 * At the same index mention the expected structure how it should look like after the input is complete.
*/
std::vector<std::pair<std::map<double,double,std::greater<double>>,std::map<double,double>>> bids_asks= {
    {
        std::map<double, double, std::greater<double>>(
            {
                {0.0025,0},
                {0.0024,0},
                {0.0022,6.4},
                {0.0020,9.7}
            }
        ),
        std::map<double, double>(
            {
                {0.0024,0},
                {0.0026,15},
                {0.0027,5},
                {0.0028,1.0},
            }
        )
    },
    {
        std::map<double, double, std::greater<double>>(
            {
                {0.0025,0},
                {0.0024,0},
                {0.0022,6.4},
                {0.0020,9.7}
            }
        ),
        std::map<double, double>(
            
        )
    },
};

/**
 * Test to check the final structure
*/
TEST(order_book_function_tests, order_book_structure_test)
{
    for(int i=0; i<samples.size(); ++i)
    {
        std::string symbol = samples[i]["snapshots"][0]["symbol"];
        parser::parser p;
        p.input_snapshot(samples[i]);
        p.input_stream(samples[i]);
        order_book::order_book_handler& instance = order_book::order_book_handler::get_instance();
        ASSERT_EQ(bids_asks[i], instance.return_bids_asks(symbol));
    }
}


/**
 * Best price test
*/
TEST(order_book_function_tests, best_price_test)
{    
    for(int i=0; i<samples.size(); ++i)
    {
        std::string symbol = samples[i]["snapshots"][0]["symbol"];
        parser::parser p;
        p.input_snapshot(samples[i]);
        p.input_stream(samples[i]);
        order_book::order_book_handler& instance = order_book::order_book_handler::get_instance();
        ASSERT_EQ(best_prices[i], instance.get_best_prices(symbol));
    }
}

/**
 * Empty or not test
*/
TEST(order_book_function_tests, is_empty_test)
{    
    for(int i=0; i<samples.size(); ++i)
    {
        std::string symbol = samples[i]["snapshots"][0]["symbol"];
        parser::parser p;
        p.input_snapshot(samples[i]);
        p.input_stream(samples[i]);
        order_book::order_book_handler& instance = order_book::order_book_handler::get_instance();
        ASSERT_EQ(empty_status[i], instance.is_order_table_empty(symbol));
    }
}
