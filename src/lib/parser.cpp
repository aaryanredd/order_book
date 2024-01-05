#include "parser.h"

void parser::parser::input_snapshot(nlohmann::json& sample)
{   
    for(nlohmann::json::const_iterator it = sample["snapshots"].cbegin(); it!=sample["snapshots"].cend(); ++it)
    {
        std::pair<std::vector<std::pair<double,double>>,std::vector<std::pair<double,double>>> snapshot_bids_asks; 
        try
        {
            for(nlohmann::json::const_iterator jt = ((*it)["bids"]).cbegin(); jt!= ((*it)["bids"]).cend(); ++jt)
                snapshot_bids_asks.first.push_back(std::make_pair(std::stod((std::string)((*jt)[0])) ,std::stod((std::string)((*jt)[1]))));   
            for(nlohmann::json::const_iterator jt = ((*it)["asks"]).cbegin(); jt!= ((*it)["asks"]).cend(); ++jt)
                snapshot_bids_asks.second.push_back(std::make_pair(std::stod((std::string)((*jt)[0])) ,std::stod((std::string)((*jt)[1]))));
        }
        catch(...){}
        order_book::order_book_handler::get_instance().input_stream(snapshot_bids_asks, (std::string)((*it)["symbol"]));
    }    
}

void parser::parser::input_stream(nlohmann::json& sample)
{   
    for(nlohmann::json::const_iterator it = sample["updates"].cbegin(); it!=sample["updates"].cend(); ++it)
    {
        std::pair<std::vector<std::pair<double,double>>,std::vector<std::pair<double,double>>> stream_bids_asks;
        try
        {
            for(nlohmann::json::const_iterator jt = ((*it)["b"]).cbegin(); jt!= ((*it)["b"]).cend(); ++jt)
                stream_bids_asks.first.push_back(std::make_pair(std::stod((std::string)((*jt)[0])) ,std::stod((std::string)((*jt)[1]))));
            for(nlohmann::json::const_iterator jt = ((*it)["a"]).cbegin(); jt!= ((*it)["a"]).cend(); ++jt)
                stream_bids_asks.second.push_back(std::make_pair(std::stod((std::string)((*jt)[0])) ,std::stod((std::string)((*jt)[1]))));
        }
        catch(...){}
        order_book::order_book_handler::get_instance().input_stream(stream_bids_asks, (std::string)((*it)["s"]));
    }    
}

parser::parser::~parser()
{
    order_book::order_book_handler::get_instance().reset();
}
