#pragma once
#include "Connectable.h"

class Connections
{
private:
    std::vector<std::pair<Connectable*, Connectable*>> m_connections;

    Connectable* m_first = nullptr;
    Connectable* m_second = nullptr;
    sf::Vector2f  m_mousePos;

    Connectable* canConnect(GameObj*) const;
    void setConnectedStatus(Connectable*, const bool);
    void drawBelt(const std::pair<const Connectable*, const Connectable*>, sf::RenderWindow&) const;
    void drawMovingBelt(sf::RenderWindow &) const;
    bool isOn(const Connectable*) const;
    sf::Vector2f calculateNormal(const sf::Vertex&, const sf::Vertex&)  const;

public:
    Connections();
    ~Connections();

    void turnOn(Connectable*); 

    Connectable* isConnectedAndConnectable(GameObj*) const;
    bool tryConnecting (const std::shared_ptr<GameObj>);
    bool doneConnecting();
    void checkConnections();
    void draw (sf::RenderWindow&) const;
    void unplug (Connectable*);
    void reset();
    void setMousePos(const sf::Vector2f);
    void deleteConnection(Connectable* obj);
};
