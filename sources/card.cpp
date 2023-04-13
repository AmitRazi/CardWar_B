#include <sstream>
#include "card.hpp"

using namespace ariel;

bool Card::operator<(const Card &other) const {
    if (rankValue == Card::Rank::ACE && other.rankValue == Card::Rank::TWO){
        return true;
    }
    if(rankValue == Card::Rank::TWO && other.rankValue == Card::Rank::ACE){
        return false;
    }
    return rankValue < other.rankValue;
}


bool Card::operator==(const Card &other) const {
    return rankValue == other.rankValue;
}

//Overloading copy assignment operator
Card &Card::operator=(const Card &other) {
    if (this == &other) {
        return *this;
    }

    rankValue = other.rankValue;
    suitType = other.suitType;
    return *this;
}

//Overloading move assignment operator
Card &Card::operator=(Card &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    rankValue = other.rankValue;
    suitType = other.suitType;
    other.rankValue = INVALID_RANK;
    other.suitType = INVALID_SUIT;

    return *this;
}

//Overloading string() operator to be used in tandem with the overloaded << operator
Card::operator std::string() const {
    std::stringstream stringStream;
    stringStream<<*this;
    return stringStream.str();
}

namespace ariel {

    std::ostream &operator<<(std::ostream &ostream, const Card &card) {
        Card::Rank cardRank = card.getRank();
        std::string rank;
        std::string suit;

        switch (cardRank) {
            case Card::Rank::ACE:
                rank = "Ace";
                break;
            case Card::Rank::TWO:
                rank = "2";
                break;
            case Card::Rank::THREE:
                rank = "3";
                break;
            case Card::Rank::FOUR:
                rank = "4";
                break;
            case Card::Rank::FIVE:
                rank = "5";
                break;
            case Card::Rank::SIX:
                rank = "6";
                break;
            case Card::Rank::SEVEN:
                rank = "7";
                break;
            case Card::Rank::EIGHT:
                rank = "8";
                break;
            case Card::Rank::NINE:
                rank = "9";
                break;
            case Card::Rank::TEN:
                rank = "10";
                break;
            case Card::Rank::JACK:
                rank = "Jack";
                break;
            case Card::Rank::QUEEN:
                rank = "Queen";
                break;
            case Card::Rank::KING:
                rank = "King";
                break;
            case Card::Rank::INVALID_RANK:
                rank = "Invalid";
                break;
        }

        switch (card.getSuit()) {
            case Card::Suit::CLUBS:
                suit = "Clubs";
                break;
            case Card::Suit::DIAMONDS:
                suit = "Diamonds";
                break;
            case Card::Suit::HEARTS:
                suit = "Hearts";
                break;
            case Card::Suit::SPADES:
                suit = "Spades";
                break;
            case Card::Suit::INVALID_SUIT:
                suit = "Invalid";
                break;
        }

        ostream << rank << " of " << suit;
        return ostream;
    }
}
