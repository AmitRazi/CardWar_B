/*
 * References:
 * Regrading move semantics: https://www.youtube.com/watch?v=Bt3zcJZIalk
 * Regrading tuples: https://www.youtube.com/watch?v=33Y_5gOyi3Y
 * Regrading shuffle and mt19937: https://en.cppreference.com/w/cpp/algorithm/random_shuffle
 * Regrading stringstreams, sets, and more (I've been studying this course in recent weeks): https://www.udemy.com/course/beginning-c-plus-plus-programming/
 */


#include <sstream>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include "game.hpp"
#include "card.hpp"

using namespace ariel;

//Creates a deck with 52 cards. All cards in a standard deck excluding jokers.
void Game::createDeck() {
    for (int suit = Card::HEARTS; suit <= Card::SPADES; ++suit) {
        for (int rank = Card::TWO; rank <= Card::ACE; ++rank) {
            deck.emplace_back(Card{static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank)});
        }
    }
}

//Uses the shuffle algorithm from the STL and mt19937(A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits.)
void Game::shuffleDeck() {
    std::shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device{}()));
}

//Distributes the shuffled deck to the players. Cards in even indices go to player1, odds go to player2.
void Game::distributeCard() {
    for (size_t i = 0; i < 52; i++) {
        if (i % 2 == 0) {
            player1.addCard(deck.at(i));
        } else {
            player2.addCard(deck.at(i));
        }
    }
}

/*Checkes if the game has started by checking if the playLog is still empty. After a single round the playLog won't be empty.
 * This is used by the print functions.
 */
bool Game::gameStarted() {
    return playLog.empty() == false;
}


/*Runs a single game round. This function returns a boolean to indicate if a round was successful, thus it return false if the game has already finished.
 * */
bool Game::playTurn() {

    if (&player1 == &player2) {
        throw std::invalid_argument("A player can't play against himself");
    }

    if (player1.stacksize() == 0 && winner.length() == 0) {
        if (player1.cardesTaken() > player2.cardesTaken()) {
            winner = player1.getName();
            p1Wins++;
        } else if (player1.cardesTaken() < player2.cardesTaken()) {
            winner = player2.getName();
            p2Wins++;
        } else {
            winner = "Draw";
        }
        cardsWonByPlayer1 = player1.cardesTaken();
        cardsWonByPlayer2 = player2.cardesTaken();
        return false;
    } else if (player1.stacksize() == 0) {
        throw std::runtime_error("The game has already finished");
    }


    int counter = 0;
    std::stringstream roundLog;
    Card player1Card = player1.removeCard();
    Card player2Card = player2.removeCard();
    if (player2Card < player1Card) {
        p1Wins++;
        counter = 2;
        player1.won(counter);
        roundLog << createRoundLog(player1Card,player2Card);
    } else if (player1Card < player2Card) {
        p2Wins++;
        counter = 2;
        player2.won(counter);
        roundLog << createRoundLog(player1Card,player2Card);
    } else {
        counter = 2;
        while ((player1Card == player2Card) && player1.stacksize() >= 1) {
            roundLog << createRoundLog(player1Card,player2Card);
            draws++;
            player1.removeCard();
            player2.removeCard();
            if(player1.stacksize() == 0){
                counter+=2;
                break;
            }
            player1Card = player1.removeCard();
            player2Card = player2.removeCard();
            counter += 4;
        }
        if (player1.stacksize() == 0 && player1Card == player2Card) {
            int split_cards = counter / 2;
            player1.won(split_cards);
            player2.won(split_cards);
            roundLog << createRoundLog(player1Card,player2Card);
            draws++;

        } else {
            if (player2Card < player1Card) {
                p1Wins++;
                player1.won(counter);
                roundLog << createRoundLog(player1Card,player2Card);
            } else {
                p2Wins++;
                player2.won(counter);
                roundLog << createRoundLog(player1Card,player2Card);
            }
        }

    }
    playLog.push_back(roundLog.str());
    if(counter > 6){
        std::cout<<roundLog.str()<<std::endl;
    }
    rounds++;
    return true;
}

//Runs playTurn() until false is returned - meaning the game has finished.
void Game::playAll() {
    while (playTurn());
}

//Prints a description of the latest round played.
void Game::printLastTurn() {
    if (gameStarted() == false) {
        std::cout << "The game hasn't started" << std::endl;
        return;
    }

    std::string roundLog = playLog.back();
    std::cout << roundLog << std::endl;
}

//Prints a description of each round played thus far.
void Game::printLog() {
    if (gameStarted() == false) {
        std::cout << "The game hasn't started" << std::endl;
        return;
    }

    for (std::string &round: playLog) {
        std::cout << round << std::endl;
    }
}

//Prints the winner or draw. If the game has finished, it prints an appropriate message.
void Game::printWiner() {
    if (player1.stacksize() == 0) {
        std::cout << "The game hasn't finished yet" << std::endl;
        return;
    }
    std::cout << winner << std::endl;
}

//Prints the stats of the game thus far.
void Game::printStats() {
    if (gameStarted() == false) {
        std::cout << "The game hasn't started" << std::endl;
        return;
    }

    std::string p1Name = player1.getName();
    std::string p2Name = player2.getName();
    double p1Winrate = static_cast<double>(p1Wins) / (rounds);
    double p2Winrate = static_cast<double>(p2Wins) / (rounds);
    double draw_rate = static_cast<double>(draws) / rounds;
    std::cout << std::fixed << std::setprecision(2) << p1Name << " win rate: " << p1Winrate << ", "<<"Cards won by "<<p1Name<<cardsWonByPlayer1<<", " << p2Name
              << " win rate: " << p2Winrate<<", Cards won by "<<p1Name<<cardsWonByPlayer1<<", "
              << "draw rate: " << draw_rate << ", amount of draws: " << draws <<
              ", winner: ";
    std::string message = winner.empty() ? "No winner yet" : winner;
    std::cout << winner;
}

//This function creates a string depicting the round.
std::string Game::createRoundLog(const Card &p1Card, const Card &p2Card) {
    std::string outcome;
    if (p2Card < p1Card) {
        outcome = player1.getName() + " wins.";
    } else if (p1Card < p2Card) {
        outcome = player2.getName() + " wins.";
    } else{
        outcome = "Draw. ";
    }
    std::string roundLog = player1.getName() + " played " + std::string(p1Card) + " " + player2.getName()
                           + " played " + std::string(p2Card) + ". " + outcome;

    return roundLog;
}

//Overloading copy assignment operator
Game &Game::operator=(const Game &other) {
    if (this == &other) {
        return *this;
    }

    player1 = other.player1;
    player2 = other.player2;
    rounds = other.rounds;
    draws = other.draws;
    p2Wins = other.p2Wins;
    p1Wins = other.p1Wins;
    cardsWonByPlayer2 = other.cardsWonByPlayer2;
    cardsWonByPlayer1 = other.cardsWonByPlayer1;
    winner = other.winner;
    deck = other.deck;
    playLog = other.playLog;

    return *this;
}

//Overloading move assignment operator
Game &Game::operator=(Game &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    player1 = other.player1;
    player2 = other.player2;
    rounds = other.rounds;
    draws = other.draws;
    p2Wins = other.p2Wins;
    p1Wins = other.p1Wins;
    cardsWonByPlayer1 = other.cardsWonByPlayer1;
    cardsWonByPlayer2 = other.cardsWonByPlayer2;
    winner = std::move(other.winner);
    deck = std::move(other.deck);
    playLog = std::move(other.playLog);

    winner = std::move(other.winner);
    deck = std::move(other.deck);
    playLog = std::move(other.playLog);

    cardsWonByPlayer2 = 0;
    cardsWonByPlayer1 = 0;
    other.rounds = 0;
    other.draws = 0;
    other.p2Wins = 0;
    other.p1Wins = 0;

    return *this;
}

