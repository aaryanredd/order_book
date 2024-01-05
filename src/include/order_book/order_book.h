#pragma once
#include<map>
#include<memory>
#include<iostream>
#include<unordered_map>
#include<vector>

namespace order_book
{
    /**
     * @details Book manager that stores symbols and their respective order books. Is a singleton class so that multilple copies do not exist.
     * It is the primary interface to the user and has functions that translate the requests to the corresponding order books object. 
    */
    class order_book_handler
    {
        /**
         * @brief Order Book class to maintain the price-volume pairs in sorted AESC and DESC order for asks and bids respectively and their corresponding functions. 
        */
        private:
            class order_book
            {
                private:
                    
                    /**
                     * @brief Containers to store the price and volume pairs
                    */
                    std::map<double,double> asks;
                    std::map<double,double,std::greater<double>> bids;
                    
                    /**
                     * @brief Hashmaps to store the price and a pointer to its corresponding volume in asks or bids.
                     * This is to by-pass the search time of O(logN) for a price that already exists.
                    */
                    std::unordered_map<double,double*> hash_asks;
                    std::unordered_map<double,double*> hash_bids;

                public:
                    
                    /**
                     * @details Function to remove order from the book by providing @param[in] price as key, @param[in] is_bid to differentiate between bids and asks. 
                    */
                    inline void remove_order(const double& price, const bool& is_bid)
                    {
                        if(is_bid) { this->bids.erase(price); this->hash_bids.erase(price); }
                        else { this->asks.erase(price); this->hash_asks.erase(price); }
                    }
                    
                    /**
                     * @details Function to lookup the best price from the containers in constant time. Takes @param[in] is_bid to differentiate between bids and asks.
                    */
                    inline const double& best_price(const bool& is_bid) const { return is_bid?this->bids.begin()->first:this->asks.begin()->first; }
                    
                    /**
                     * @details Function to determine if the container is empty or not. Takes @param[in] is_bid to differentiate between bids and asks and returns a true if empty, false otherwise.
                    */
                    inline const bool is_empty(const bool& is_bid) const { return is_bid?this->bids.empty():this->asks.empty(); }

                    /**
                     * @brief Function to take add requests, takes @param[in] price, @param[in] volume, @param[in] is_bid parameters. 
                    */
                    void add_order(const double& price, const double& volume, const bool& is_bid);
                    
                    /**
                     * @brief This function is to enable testing, does not have significance in working logic. Meant to be removed.
                    */
                    const std::pair<std::map<double,double,std::greater<double>>,std::map<double,double>> return_bids_asks();
            };

            /**
             * @brief A hash map to store the corresponding order_books against the symbols. Dynamically allocated to accomodate large amount of symbols.
            */
            std::unordered_map<std::string, order_book>* books = new std::unordered_map<std::string, order_book>();

            /**
             * @brief Deleting the constructors, copy constructors and operators to maintain singleton pattern.
            */
            order_book_handler() = default; 
            order_book_handler(const order_book_handler&) = delete;
            order_book_handler& operator=(const order_book_handler&) = delete;
            ~order_book_handler(); 

        public:
            /**
             * @details Function to take input of snapshots and streams as STL containers and primitive data types.
             * @param[in] stream is a pair of vectors. First element in the pair is to represent bids, second for asks.
             * Each vector is a list of pairs in the format {price,volume}.
             * @param[in] symbol is to identify the order book from the book mapper.
            */
            void input_stream(const std::pair<std::vector<std::pair<double,double>>, std::vector<std::pair<double,double>>>& stream, const std::string& symbol);
            
            /**
             * @brief Function to put a remove request to corresponding object of the @param[in] symbol.
            */
            void remove_order(const double& price, const bool& is_bid, std::string& symbol);

            /**
             * @brief Static function to fetch the instance. Only way to access the object since the constructors are private. 
            */
            static order_book_handler& get_instance() 
            {
                static order_book_handler instance;
                return instance;                    
            }

            /**
             * @brief These functions are to enable testing, do not have significance in working logic. Meant to be removed.
            */
            const std::pair<std::map<double,double,std::greater<double>>,std::map<double,double>> return_bids_asks(const std::string symbol);
            const std::pair<double, double> get_best_prices(std::string symbol);
            const std::pair<bool, bool> is_order_table_empty(std::string symbol);
            void reset();
    };
}   