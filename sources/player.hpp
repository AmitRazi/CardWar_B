//
// Created by 97250 on 21/03/2023.
//

#ifndef CARDGAME_PLAYER_HPP
#define CARDGAME_PLAYER_HPP

#include "card.hpp"

namespace ariel {
    class Player {
    private:
        std::string name;
        std::vector<Card> stack;
        int wonCards;

    public:

        Player(std::string name) : name(std::move(name)), wonCards(0) {
            if(this->name.length() == 0) {this->name = "No Name"};
        }

        //Copy constructor
        Player(const Player &other) : Player(other.name) {
        }

        //Move constructor
        Player(Player &&other) noexcept: name(std::move(other.name)), stack(std::move(other.stack)),
                                                 wonCards(other.wonCards) {
            other.wonCards = -1;
        }

        ~Player() = default;

        std::string getName();

        int stacksize() const;

        int cardesTaken() const;

        void won(int);

        void addCard(const Card &card);

        Card removeCard();

        Card topCard() const;

        Player &operator=(const Player &);

        Player &operator=(Player &&) noexcept;
    };
}

#endif //CARDGAME_PLAYER_HPP
