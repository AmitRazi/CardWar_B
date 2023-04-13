#include "player.hpp"

using namespace ariel;


std::string Player::getName() {
    return name;
}

int Player::stacksize() const {
    return static_cast<int>(stack.size());
}

int Player::cardesTaken() const {
    return wonCards;
}

//This function is invoked by the game instance with an int argument to indicate the number of cards won by the player.
void Player::won(int num_of_cards) {
    wonCards += num_of_cards;
}

//This function is invoked by the game instance with a card argument to be added to the players stack.
void Player::addCard(const Card &card) {
    stack.push_back(card);
}

//This function is invoked by the game instance to remove and return the top card in the players stack.
Card Player::removeCard() {
    Card top = topCard();
    stack.pop_back();
    return top;
}

//Returns the top card in the players stack.
Card Player::topCard() const {
    return stack.back();
}


//Overloading the copy operator
Player &Player::operator=(const Player &other) {
    if (this == &other) {
        return *this;
    }

    name = other.name;
    stack = other.stack;
    wonCards = other.wonCards;

    return *this;
}

//Overloading the Move operator
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

