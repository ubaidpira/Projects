#include "Player.hpp"
Player * Player_factory(const std::string &name, const std::string &strategy) {
  assert(false);
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  assert(false);
}

class SimplePlayer : public Player {
public:

SimplePlayer(const std::string &name);
const std::string &get_name() const override;
void add_card(const Card &c) override;
bool make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const override;
void add_and_discard(const Card &upcard) override;
Card lead_card(Suit trump) override;
Card play_card(const Card &led_card, Suit trump) override;
private:
    std::string player_name;
    std::vector<Card> hand;
};
SimplePlayer::SimplePlayer(const std::string &name) : player_name(name) {}


const std::string &SimplePlayer::get_name() const {
    return player_name;
}

void SimplePlayer::add_card(const Card &c) {
    if (hand.size() < MAX_HAND_SIZE) {
        hand.push_back(c);
    }
}

bool SimplePlayer::make_trump(const Card &upcard, bool is_dealer, int round, Suit &order_up_suit) const {
    if (round == 1 && is_dealer) {
        order_up_suit = upcard.get_suit();
        return true;
    }
    return false;
}

void SimplePlayer::add_and_discard(const Card &upcard) {
    if (!hand.empty()) {
        Card lowest_card = hand[0];
        for (const Card &card : hand) {
            if (card < lowest_card) {
                lowest_card = card;
            }
        }
        hand.erase(std::remove(hand.begin(), hand.end(), lowest_card), hand.end());
        hand.push_back(upcard);
    }
}

Card SimplePlayer::lead_card(Suit trump) {
    if (!hand.empty()) {
        Card highest_card = hand[0];
        for (const Card &card : hand) {
            if (card > highest_card) {
                highest_card = card;
            }
        }
        hand.erase(std::remove(hand.begin(), hand.end(), highest_card), hand.end());
        return highest_card;
    }
    return Card();
}

Card SimplePlayer::play_card(const Card &led_card, Suit trump) {
    if (!hand.empty()) {
        Suit led_suit = led_card.get_suit();
        Card lowest_suit_card = hand[0];

        for (const Card &card : hand) {
            if (card.get_suit() == led_suit && card < lowest_suit_card) {
                lowest_suit_card = card;
            }
        }

        if (lowest_suit_card.get_suit() == led_suit) {
            hand.erase(std::remove(hand.begin(), hand.end(), lowest_suit_card), hand.end());
            return lowest_suit_card;
        }
        Card lowest_card = hand[0];
        for (const Card &card : hand) {
            if (card < lowest_card) {
                lowest_card = card;
            }
        }
        hand.erase(std::remove(hand.begin(), hand.end(), lowest_card), hand.end());
        return lowest_card;
}
return Card();

/*Player * Player_factory(const std::string &name, const std::string &strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    }
std::ostream & operator<<(std::ostream &os, const Player &p) {
    os << p.get_name();
    return os;
}
}
*/

