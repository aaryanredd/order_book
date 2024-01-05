#include "order_book.h"

namespace order_book
{
    /**
     * @details To take input from the user. 
    */
    void order_book_handler::input_stream(const std::pair<std::vector<std::pair<double,double>>,std::vector<std::pair<double,double>>>& stream, const std::string& symbol)
    {
        for(int i=0; i<stream.first.size(); ++i)
            (*this->books)[symbol].add_order(stream.first[i].first, stream.first[i].second, true);
        for(int i=0; i<stream.second.size(); ++i)
            (*this->books)[symbol].add_order(stream.second[i].first, stream.second[i].second, false);
    }

    /**
     * @details release the dynamically allocated memory. No leaks detected even if this destructor wasn't defined.
    */
    order_book_handler::~order_book_handler()
    {
        delete this->books;
    }

    /**
     * @details Function to remove order. Doesn't do anything other than calling the remove function of corresponding order book. Takes @param[in] symbol to identify the order book.
    */
    void order_book_handler::order_book_handler::remove_order(const double& price, const bool& is_bid, std::string& symbol)
    {
        (*this->books)[symbol].remove_order(price, is_bid);
    }

    /**
     * @details Takes the @param[in] price, @param[in] volume, @param[in] is_bid to insert into the order_book in the corresponding asks or bids container.
     * Before the adding to the container, checks into the hash if the price already exists. This way the first insertion is done in logrithmic time, all succeeding requests are dealt at constant time.
    */
    void order_book_handler::order_book::add_order(const double& price, const double& volume, const bool& is_bid)
    {
        if(is_bid)
        {
            auto it = hash_bids.find(price);
            if(it!=hash_bids.end())
                *(it->second) = volume;
            else
            {
                this->bids[price]=volume;
                this->hash_bids[price] = &this->bids[price];
            }
        }
        else
        {
            auto it = hash_asks.find(price);
            if(it!=hash_asks.end())
                *(it->second) = volume;
            else
            {
                this->asks[price] = volume;
                this->hash_asks[price] = &this->asks[price];
            }
        }
    }

    /**
     * @brief Testing helper function. Resets the order_book.
    */
    void order_book::order_book_handler::reset()
    {
        this->books->clear();
    }

    /**
     * Testing Helper Function
    */
    const std::pair<std::map<double,double,std::greater<double>>,std::map<double,double>> order_book_handler::return_bids_asks(const std::string symbol)
    {
        return (*this->books)[symbol].return_bids_asks();
    }
    
    /**
     * Testing Helper Function
    */
    const std::pair<bool, bool> order_book_handler::is_order_table_empty(std::string symbol)
    {
        return std::make_pair<double, double>((*this->books)[symbol].is_empty(true), (*this->books)[symbol].is_empty(false));
    }

    /**
     * Testing Helper Function
    */
    const std::pair<double, double> order_book_handler::get_best_prices(std::string symbol)
    {
        return std::make_pair((*this->books)[symbol].best_price(true),  (*this->books)[symbol].best_price(false)); 
    }
    
    /**
     * Testing Helper Function
    */
    const std::pair<std::map<double,double,std::greater<double>>,std::map<double,double>> order_book_handler::order_book::return_bids_asks()
    {
        return std::make_pair((this->bids), (this->asks));
    }
}
