#include <benchmark/benchmark.h>
#include "nlohmann/json.hpp"
#include "gtest/gtest.h"
#include "order_book/parser.h"

/**
 * Vector of Json inputs to be tried. Just append to the list in the same format as on mentioned.
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
  )"_json
  };

/**
 * To benchmark the performance of the all input sets.
 * Timers run only for the input functions
*/
static void SnapshotBenchmark(benchmark::State& state) 
{
  int i = state.range(0);
  for (auto _ : state)
  {
    state.PauseTiming();
    parser::parser r;
    state.ResumeTiming();
    r.input_snapshot(samples[i]);
    r.input_stream(samples[i]);
    state.SetComplexityN(state.range(0));
  }
}

/** 
 * Registering the benchmark
*/
BENCHMARK(SnapshotBenchmark)->DenseRange(0, samples.size()-1,1)->Complexity(benchmark::oN);

BENCHMARK_MAIN();