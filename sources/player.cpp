#include "player.hpp"

using namespace ariel;

Player::Player() : Player("No Name") {}

Player::Player(std::string name) : name(std::move(name)), won_cards(0) {}

Player::Player(const Player &other) : Player(other.name) {
}

Player::Player(Player &&other) noexcept: name(std::move(other.name)), stack(std::move(other.stack)),
                                         won_cards(other.won_cards) {
    other.won_cards = -1;
}

Player::~Player() = default;

std::string Player::get_name() {
    return name;
}

int Player::stacksize() const {
    return static_cast<int>(stack.size());
}

int Player::cardesTaken() const {
    return won_cards;
}

void Player::won(int num_of_cards) {
    won_cards += num_of_cards;
}

void Player::add_card(const Card &card) {
    stack.push_back(card);
}

Card Player::remove_card() {
    Card top = top_card();
    stack.pop_back();
    return top;
}

Card Player::top_card() const {
    return stack.back();
}

Player &Player::operator=(const Player &other) {
    if (this == &other) {
        return *this;
    }

    name = other.name;
    stack = other.stack;
    won_cards = other.won_cards;

    return *this;
}

Player &Player::operator=(Player &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    name = std::move(other.name);
    stack = std::move(other.stack);
    won_cards = other.won_cards;
    other.won_cards = -1;

    return *this;
}

