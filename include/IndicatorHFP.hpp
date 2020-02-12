//
// Created by Gaëtan Léandre on 12/02/2020.
//

#ifndef                     HANDS_FREE_INDICATORHFP_HPP
#define                     HANDS_FREE_INDICATORHFP_HPP

#include                    <string>
#include                    <iostream>

class                       IndicatorHFP {
    std::string             _name;
    int                     _upRange;
    int                     _downRange;
    int                     _value = 0;

    std::string             parseName(std::string const &str) const;
    std::pair<int, int>     parseRange(std::string const &str) const;


public:
    IndicatorHFP(std::string const &str);
    ~IndicatorHFP();
    std::string             getName() const;
};


#endif                  //HANDS_FREE_INDICATORHFP_HPP
