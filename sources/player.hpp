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
        int won_cards;

    public:

        Player();

        Player(std::string name);

        Player(Player &&) noexcept;

        Player(const Player &);

        ~Player();

        std::string get_name();

        int stacksize() const;

        int cardesTaken() const;

        void won(int);

        void add_card(const Card &);

        Card remove_card();

        Card top_card() const;

        Player &operator=(const Player &);

        Player &operator=(Player &&) noexcept;
    };
}

#endif //CARDGAME_PLAYER_HPP