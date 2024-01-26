#include "CSVReader.h"
#include <iostream>
#include <fstream>

using std::string;
using std::vector;

CSVReader::CSVReader()
{

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
        while(std::getline(csvFile, line))
        {
            try {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ',', 0));
                entries.push_back(obe);
            }catch(const std::exception& e)
            {
                //std::cout << "CSVReader::readCSV bad data"  << std::endl;
            }
        }// end of while
    }    

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries"  << std::endl;
    return entries; 
}

std::vector<std::string> CSVReader::tokenise(const string csvLine, char separator, char deletech)

{
    vector<string> tokens;
    string::size_type start, end;
    string token;
    start = csvLine.find_first_not_of(separator, 0);

    do { 
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end) break;
/*
        if (end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);
*/
        token = csvLine.substr(start, end - start);
        start = end + 1;
        if (0 != deletech)
        {
            string::size_type n_char = token.find_first_of(deletech, 0);
            while (n_char != token.length() && n_char != string::npos)
            {
                token.erase(n_char, 1);
                n_char = token.find_first_of(deletech, n_char);
            }
        }   
        tokens.push_back(token);
        
    } while (end != std::string::npos);
    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;

    if (tokens.size() != 5) // bad
    {
        //std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    try {
         price = std::stod(tokens[3]);
         amount = std::stod(tokens[4]);
    }catch(const std::exception& e){
        std::cout << "Bad float! " << tokens[3]<< std::endl;
        std::cout << "Bad float! " << tokens[4]<< std::endl; 
        throw;        
    }

    OrderBookEntry obe{price, 
                        amount, 
                        tokens[0],
                        tokens[1], 
                        OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obe; 
}
      
