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

        int p1Wins;
        int p2Wins;
        int draws;
        int rounds;

        std::vector<Card> deck;
        std::vector<std::string> playLog;
        std::string winner;

        bool gameStarted();

        void createDeck();

        void shuffleDeck();

        void distributeCard();

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

        std::string createRoundLog(const Card &, const Card &);

        Game &operator=(const Game &);

        Game &operator=(Game &&) noexcept;
    };
}

#endif //CARDGAME_GAME_HPP
