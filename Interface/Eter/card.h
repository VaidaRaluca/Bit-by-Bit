#ifndef CARD_H
#define CARD_H

#include<cstdint>
#include<string>
#include<iostream>
#include<QDebug>

namespace eter {
class Card
{
public:
    //Rule of 5
    Card() = default;
    Card(const uint8_t& value , const std::string& color, const bool& position);
    Card(const Card& other);
    Card& operator=(const Card& other);
    Card(Card&& other) noexcept;
    Card& operator=(Card&& other) noexcept;
    ~Card() = default;

    const uint8_t& GetValue() const;
    const std::string& GetColor() const;
    const bool& GetPosition() const;

    void SetValue(const uint8_t& value);
    void SetColor(const std::string& color); //for later color could be an enum : red/blue => reduces memory overhead and increases efficiency
    void SetPosition(const bool& positon);

    bool operator==(const Card& other) const;
    void swap(Card& other) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend QDebug operator<<(QDebug debug, const Card& card);
    friend void swap(Card& first, Card& second) noexcept;

private:
    uint8_t m_value;
    std::string m_color;
    bool m_position; //true = fata in sus

};

}
#endif // CARD_H
