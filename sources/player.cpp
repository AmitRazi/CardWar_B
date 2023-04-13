#include "player.hpp"

using namespace ariel;

Player::Player(std::string name) : name(std::move(name)), wonCards(0) {
    if(this->name.length() == 0) this->name = "No Name";
}

Player::Player(const Player &other) : Player(other.name) {
}

Player::Player(Player &&other) noexcept: name(std::move(other.name)), stack(std::move(other.stack)),
                                         wonCards(other.wonCards) {
    other.wonCards = -1;
}

Player::~Player() = default;

std::string Player::getName() {
    return name;
}

int Player::stacksize() const {
    return static_cast<int>(stack.size());
}

int Player::cardesTaken() const {
    return wonCards;
}

void Player::won(int num_of_cards) {
    wonCards += num_of_cards;
}

void Player::addCard(const Card &card) {
    stack.push_back(card);
}

Card Player::removeCard() {
    Card top = topCard();
    stack.pop_back();
    return top;
}

Card Player::topCard() const {
    return stack.back();
}

Player &Player::operator=(const Player &other) {
    if (this == &other) {
        return *this;
    }

    name = other.name;
    stack = other.stack;
    wonCards = other.wonCards;

    return *this;
}

Player &Player::operator=(Player &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    name = std::move(other.name);
    stack = std::move(other.stack);
    wonCards = other.wonCards;
    other.wonCards = -1;

    return *this;
}

