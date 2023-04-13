#include <sstream>
#include "card.hpp"

using namespace ariel;

Card::Card(Suit suit, Rank rank) : suit_type(suit), rank_value(rank) {}

Card::Card(const Card &other) : Card(other.getSuit(), other.getRank()) {
}

Card::Card(Card &&other) noexcept: suit_type(other.suit_type), rank_value(other.rank_value) {
    other.suit_type = INVALID_SUIT;
    other.rank_value = INVALID_RANK;
}

Card::~Card() = default;

Card::Rank Card::getRank() const {
    return rank_value;
}

Card::Suit Card::getSuit() const {
    return suit_type;
}

bool Card::operator>(const Card &other) const {
    if (rank_value == Card::ACE) {
        if (other.rank_value == Card::TWO) return false;
    }
    return rank_value > other.rank_value;
}

bool Card::operator<(const Card &other) const {
    if (rank_value == Card::ACE) {
        if (other.rank_value == Card::TWO) return true;
    }
    return rank_value < other.rank_value;
}

bool Card::operator==(const Card &other) const {
    return rank_value == other.rank_value;
}

Card &Card::operator=(const Card &other) {
    if (this == &other) {
        return *this;
    }

    rank_value = other.rank_value;
    suit_type = other.suit_type;
    return *this;
}

Card &Card::operator=(Card &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    rank_value = other.rank_value;
    suit_type = other.suit_type;
    other.rank_value = INVALID_RANK;
    other.suit_type = INVALID_SUIT;

    return *this;
}

Card::operator std::string() const {
    std::stringstream stringStream;
    stringStream<<*this;
    return stringStream.str();
}

namespace ariel {
    std::ostream &operator<<(std::ostream &ostream, const Card &card) {
        Card::Rank card_rank = card.getRank();
        std::string rank;
        std::string suit;

        switch (card_rank) {
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
