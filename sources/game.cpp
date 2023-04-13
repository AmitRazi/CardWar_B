#include <sstream>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include "game.hpp"
#include "card.hpp"

using namespace ariel;

Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2), p1Wins(0), p2Wins(0), draws(0),
                                               rounds(0) {
    Game::createDeck();
    Game::shuffleDeck();
    Game::distributeCard();
}

Game::Game(const Game &other) : Game(other.player1, other.player2) {
}

Game::Game(Game &&other) noexcept
        : player1(other.player1),
          player2(other.player2),
          p1Wins(other.p1Wins),
          p2Wins(other.p2Wins),
          draws(other.draws),
          rounds(other.rounds),
          deck(std::move(other.deck)),
          playLog(std::move(other.playLog)),
          winner(std::move(other.winner)) {

    other.p1Wins = 0;
    other.p2Wins = 0;
    other.draws = 0;
    other.rounds = 0;
}

Game::~Game() = default;

void Game::createDeck() {
    for (int suit = Card::HEARTS; suit <= Card::SPADES; ++suit) {
        for (int rank = Card::ACE; rank <= Card::KING; ++rank) {
            deck.emplace_back(Card{static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank)});
        }
    }
}

void Game::shuffleDeck() {
    std::shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device{}()));
}

void Game::distributeCard() {
    for (size_t i = 0; i < 52; i++) {
        if (i % 2 == 0) {
            player1.add_card(deck.at(i));
        } else {
            player2.add_card(deck.at(i));
        }
    }
}

bool Game::gameStarted() {
    return playLog.empty() == false;
}

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
        return false;
    } else if (player1.stacksize() == 0) {
        throw std::runtime_error("The game has already finished");
    }


    int counter = 0;
    std::stringstream roundLog;
    Card player1Card = player1.removeCard();
    Card player2Card = player2.removeCard();
    if (player1Card > player2Card) {
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
        while ((player1Card == player2Card) && player1.stacksize() > 1) {
            roundLog << createRoundLog(player1Card,player2Card);
            draws++;
            player1.removeCard();
            player2.removeCard();
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
            if (player1Card > player2Card) {
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
    rounds++;
    return true;
}

void Game::playAll() {
    while (playTurn());
}

void Game::printLastTurn() {
    if (gameStarted() == false) {
        std::cout << "The game hasn't started" << std::endl;
        return;
    }

    std::string roundLog = playLog.back();
    std::cout << roundLog << std::endl;
}


void Game::printLog() {
    if (gameStarted() == false) {
        std::cout << "The game hasn't started" << std::endl;
        return;
    }

    for (std::string &round: playLog) {
        std::cout << round << std::endl;
    }
}

void Game::printWiner() {
    if (gameStarted() == false) {
        std::cout << "The game hasn't started" << std::endl;
        return;
    }

    std::cout << winner << std::endl;
}

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
    std::cout << std::fixed << std::setprecision(2) << p1Name << " win rate: " << p1Winrate << ", " << p2Name
              << " win rate: " << p2Winrate
              << ", draw rate: " << draw_rate << ", amount of draws: " << draws <<
              ", winner: ";
    std::string message = winner.empty() ? "No winner yet" : winner;
    std::cout << winner;
}

std::string Game::createRoundLog(const Card &p1Card, const Card &p2Card) {
    std::string outcome;
    if (p1Card > p2Card) {
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
    winner = other.winner;
    deck = other.deck;
    playLog = other.playLog;

    return *this;
}

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
    winner = std::move(other.winner);
    deck = std::move(other.deck);
    playLog = std::move(other.playLog);

    rounds = other.rounds;
    draws = other.draws;
    p2Wins = other.p2Wins;
    p1Wins = other.p1Wins;
    winner = std::move(other.winner);
    deck = std::move(other.deck);
    playLog = std::move(other.playLog);


    other.rounds = 0;
    other.draws = 0;
    other.p2Wins = 0;
    other.p1Wins = 0;

    return *this;
}
