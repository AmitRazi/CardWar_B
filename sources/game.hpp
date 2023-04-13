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
        int cardsWonByPlayer1;
        int cardsWonByPlayer2;

        std::vector<Card> deck;
        std::vector<std::string> playLog;
        std::string winner;

        bool gameStarted();

        void createDeck();

        void shuffleDeck();

        void distributeCard();

    public:


        Game(Player &player1, Player &player2) : player1(player1), player2(player2), p1Wins(0), p2Wins(0), draws(0),
                                                 rounds(0), cardsWonByPlayer1(0), cardsWonByPlayer2(0) {
            Game::createDeck();
            Game::shuffleDeck();
            Game::distributeCard();
        }

        //Copy constructor
        Game(const Game &other) : Game(other.player1, other.player2) {
        }

        //Move constructor
        Game(Game &&other) noexcept
                : player1(other.player1),
                  player2(other.player2),
                  p1Wins(other.p1Wins),
                  p2Wins(other.p2Wins),
                  draws(other.draws),
                  rounds(other.rounds),
                  deck(std::move(other.deck)),
                  cardsWonByPlayer1(other.cardsWonByPlayer1),
                  cardsWonByPlayer2(other.cardsWonByPlayer2),
                  playLog(std::move(other.playLog)),
                  winner(std::move(other.winner)) {

            other.cardsWonByPlayer2 = 0;
            other.cardsWonByPlayer1 = 0;
            other.p1Wins = 0;
            other.p2Wins = 0;
            other.draws = 0;
            other.rounds = 0;
        }

        ~Game() = default;

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
