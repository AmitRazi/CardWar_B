//
// Created by 97250 on 21/03/2023.
//

#ifndef CARDGAME_CARD_HPP
#define CARDGAME_CARD_HPP

#include <iostream>
#include <vector>
#include <string>

namespace ariel {
    class Card {

    public:
        enum Suit {
            INVALID_SUIT = 0, HEARTS, DIAMONDS, CLUBS, SPADES
        };
        enum Rank {
            INVALID_RANK = 0, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
        };

        Card(Suit suit, Rank rank);

        Card(const Card &);

        Card(Card &&) noexcept;

        ~Card();

        Rank getRank() const;

        Suit getSuit() const;

        bool operator>(const Card &) const;

        bool operator<(const Card &) const;

        bool operator==(const Card &) const;

        Card &operator=(Card &&) noexcept;

        Card &operator=(const Card &);

        operator std::string() const;

        friend std::ostream &operator<<(std::ostream &ostream, const Card &card);

    private:
        Suit suit_type;
        Rank rank_value;
    };
}

#endif //CARDGAME_CARD_HPP
