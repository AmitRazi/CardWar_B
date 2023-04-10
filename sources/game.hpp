//
// Created by 97250 on 21/03/2023.
//

#ifndef CARDGAME_GAME_HPP
#define CARDGAME_GAME_HPP

#include "player.hpp"

namespace ariel {
    class Game {
    private:
        Player &player1;
        Player &player2;
        int p1_wins;
        int p2_wins;
        int draws;
        int rounds;
        std::vector<Card> deck;
        std::vector<std::string> play_log;
        std::string winner;

        void create_deck();

        void shuffle_deck();

        void distribute_card();

    public:
        Game(Player &player1, Player &player2);

        Game(const Game &);

        Game(Game &&) noexcept;

        ~Game();

        bool playTurn();

        void printLastTurn();

        void playAll();

        void printWiner();

        void printLog();

        void printStats();

        Game &operator=(const Game &);

        Game &operator=(Game &&) noexcept;
    };
}

#endif //CARDGAME_GAME_HPP