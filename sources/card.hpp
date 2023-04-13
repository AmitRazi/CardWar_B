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

        //Enum used to indicate the suit of a card
        enum Suit {
            INVALID_SUIT = 0, HEARTS, DIAMONDS, CLUBS, SPADES
        };

        //Enum used to indicate the rank of a card
        enum Rank {
            INVALID_RANK = 0, ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
        };


        Card(Suit suit, Rank rank) : suitType(suit), rankValue(rank) {}

        //Copy constructor
        Card(const Card &other) : Card(other.getSuit(), other.getRank()) {
        }

        //Move constructor
        Card(Card &&other) noexcept: suitType(other.suitType), rankValue(other.rankValue) {
            other.suitType = INVALID_SUIT;
            other.rankValue = INVALID_RANK;
        }

        ~Card() = default;


        Rank getRank() const {
            return rankValue;
        }

        Suit getSuit() const {
            return suitType;
        }

        bool operator>(const Card &) const;

        bool operator<(const Card &) const;

        bool operator==(const Card &) const;

        Card &operator=(Card &&) noexcept;

        Card &operator=(const Card &);

        operator std::string() const;

        friend std::ostream &operator<<(std::ostream &ostream, const Card &card);

    private:
        Suit suitType;
        Rank rankValue;
    };
}

#endif //CARDGAME_CARD_HPP
