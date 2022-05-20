#pragma once

#include "GameObj.h"

class Connectable : public GameObj
{
public:
    Connectable(const ObjInfo&, const bool, b2World &);
    ~Connectable();

    
    bool isConected() const                  { return m_conected; }
    void setConected(const bool conected)    { m_conected = conected; }

    void draw(sf::RenderWindow& window) override;
    void backToStartingPlace() override;
    Type_t handleClick(const sf::Vector2f) override;
    void setPosition(const sf::Vector2f) override;

    sf::Vector2f getConnectionButtonPos() const { return m_connection.getLocation(); }

private:

    static bool m_registerit;

    bool m_conected = false; 
    Button m_connection;
    sf::Vector2f m_buttonDelta;

    void animate();
};

