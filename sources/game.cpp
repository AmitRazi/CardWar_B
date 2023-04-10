#include <sstream>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include "game.hpp"
#include "card.hpp"

using namespace ariel;

Game::Game(Player &player1, Player &player2) : player1(player1), player2(player2), p1_wins(0), p2_wins(0), draws(0),
                                               rounds(0) {
    Game::create_deck();
    Game::shuffle_deck();
    Game::distribute_card();
}

Game::Game(const Game &other) : Game(other.player1, other.player2) {
}

Game::Game(Game &&other) noexcept
        : player1(other.player1),
          player2(other.player2),
          p1_wins(other.p1_wins),
          p2_wins(other.p2_wins),
          draws(other.draws),
          rounds(other.rounds),
          deck(std::move(other.deck)),
          play_log(std::move(other.play_log)),
          winner(std::move(other.winner)) {

    other.p1_wins = 0;
    other.p2_wins = 0;
    other.draws = 0;
    other.rounds = 0;
};

Game::~Game() = default;

bool Game::playTurn() {

    if (&player1 == &player2) {
        throw std::invalid_argument("A player can't play against himself");
    }

    if (player1.stacksize() == 0 && winner.length() == 0) {
        if (player1.cardesTaken() > player2.cardesTaken()) {
            winner = player1.get_name();
            p1_wins++;
        } else if (player1.cardesTaken() < player2.cardesTaken()) {
            winner = player2.get_name();
            p2_wins++;
        } else {
            winner = "Draw";
        }
        return false;
    } else if (player1.stacksize() == 0) {
        throw std::runtime_error("The game has already finished");
    }


    int counter = 0;
    std::ostringstream round_log;
    Card player1_card = player1.remove_card();
    Card player2_card = player2.remove_card();
    if (player1_card > player2_card) {
        p1_wins++;
        counter = 2;
        player1.won(counter);
        round_log << player1.get_name() << " played " << player1_card << " " << player2.get_name() << " played "
                  << player2_card << ". " << player1.get_name() << " won.";
    } else if (player1_card < player2_card) {
        p2_wins++;
        counter = 2;
        player2.won(counter);
        round_log << player1.get_name() << " played " << player1_card << " " << player2.get_name() << " played "
                  << player2_card << ". " << player2.get_name() << " won.";
    } else {
        counter = 2;
        while ((player1_card == player2_card) && player1.stacksize() > 1) {
            round_log << player1.get_name() << " played " << player1_card << " " << player2.get_name() << " played "
                      << player2_card << ". draw. ";
            draws++;
            player1.remove_card();
            player2.remove_card();
            player1_card = player1.remove_card();
            player2_card = player2.remove_card();
            counter += 4;
        }
        if (player1.stacksize() == 0 && player1_card == player2_card) {
            int split_cards = counter / 2;
            player1.won(split_cards);
            player2.won(split_cards);
            round_log << player1.get_name() << " played " << player1_card << " " << player2.get_name()
                      << " played " << player2_card << ". draw.";
            draws++;

        } else {
            if (player1_card > player2_card) {
                p1_wins++;
                player1.won(counter);
                round_log << player1.get_name() << " played " << player1_card << " " << player2.get_name()
                          << " played " << player2_card << ". " << player1.get_name() << " won.";
            } else {
                p2_wins++;
                player2.won(counter);
                round_log << player1.get_name() << " played " << player1_card << " " << player2.get_name()
                          << " played " << player2_card << ". " << player2.get_name() << " won.";
            }
        }

    }
    play_log.push_back(round_log.str());
    rounds++;
    return true;
}

void Game::printLastTurn() {
    std::string round_log = play_log.back();
    std::cout << round_log << std::endl;
}

void Game::playAll() {
    while (playTurn());
}

void Game::printWiner() {
    std::cout << winner << std::endl;
}

void Game::printLog() {
    for (std::string &round: play_log) {
        std::cout << round << std::endl;
    }
}

void Game::printStats() {
    std::string p1_name = player1.get_name();
    std::string p2_name = player2.get_name();
    double p1_winrate = static_cast<double>(p1_wins) / (rounds);
    double p2_winrate = static_cast<double>(p2_wins) / (rounds);
    double draw_rate = static_cast<double>(draws) / rounds;
    std::cout << std::fixed << std::setprecision(2) << p1_name << " win rate: " << p1_winrate << ", " << p2_name
              << " win rate: " << p2_winrate
              << ", draw rate: " << draw_rate << ", amount of draws: " << draws <<
              ", winner: ";
    printWiner();
}

void Game::create_deck() {
    for (int suit = Card::HEARTS; suit <= Card::SPADES; ++suit) {
        for (int rank = Card::ACE; rank <= Card::KING; ++rank) {
            deck.emplace_back(Card{static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank)});
        }
    }
}

void Game::shuffle_deck() {
    std::shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device{}()));
}

void Game::distribute_card() {
    for (size_t i = 0; i < 52; i++) {
        if (i % 2 == 0) {
            player1.add_card(deck.at(i));
        } else {
            player2.add_card(deck.at(i));
        }
    }
}

Game &Game::operator=(const Game &other) {
    if (this == &other) {
        return *this;
    }

    player1 = other.player1;
    player2 = other.player2;
    rounds = other.rounds;
    draws = other.draws;
    p2_wins = other.p2_wins;
    p1_wins = other.p1_wins;
    winner = other.winner;
    deck = other.deck;
    play_log = other.play_log;

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
    p2_wins = other.p2_wins;
    p1_wins = other.p1_wins;
    winner = std::move(other.winner);
    deck = std::move(other.deck);
    play_log = std::move(other.play_log);

    rounds = other.rounds;
    draws = other.draws;
    p2_wins = other.p2_wins;
    p1_wins = other.p1_wins;
    winner = std::move(other.winner);
    deck = std::move(other.deck);
    play_log = std::move(other.play_log);


    other.rounds = 0;
    other.draws = 0;
    other.p2_wins = 0;
    other.p1_wins = 0;

    return *this;
}

