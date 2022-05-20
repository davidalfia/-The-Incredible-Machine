#include "Connections.h"



Connections::Connections()
{
}

Connections::~Connections()
{
}

bool Connections::tryConnecting (const std::shared_ptr<GameObj> obj)
{
    if (Connectable* toAdd = canConnect(obj.get()))
    {
        if (m_first == nullptr)
            m_first = toAdd;

        else 
            m_second = toAdd;
        
        return true;
    }
    m_first = nullptr;
    m_second = nullptr;

    return false;

}

Connectable* Connections::isConnectedAndConnectable(GameObj* obj) const
{
    if (Connectable* connectable = dynamic_cast<Connectable*>(obj))
        if(connectable->isConected())
            return connectable;

    return nullptr;
}

Connectable* Connections::canConnect(GameObj* obj) const
{
    if(obj != m_first)//set connected as soon as is m_first
        if (Connectable* connectable = dynamic_cast<Connectable*>(obj))
            if(!connectable->isConected())
                return connectable;

    return nullptr;
}

bool Connections::doneConnecting()
{
    if (m_first != nullptr && m_second)
    {
        m_connections.push_back(std::make_pair(m_first, m_second));

        setConnectedStatus(m_first, true);
        setConnectedStatus(m_second, true);

        m_first = m_second = nullptr;
        return true;
    }
    return false;
}

void Connections::checkConnections()
{
    for(auto &each : m_connections)
    {
        if(isOn(each.first))
            turnOn(each.second);
        else if (isOn(each.second))
            turnOn(each.first);
    }
}

bool Connections::isOn(const Connectable* connectable) const
{
    return connectable->isOn();
}

void Connections::turnOn(Connectable* connectable)
{
    connectable->setStatus(ON);
}

void Connections::setConnectedStatus(Connectable* connectable, const bool status)
{
    connectable->setConected(status);
}

void Connections::draw(sf::RenderWindow& window) const
{
    for (auto &each: m_connections)
        drawBelt(each, window);

    if (m_first)
        drawMovingBelt(window);
}

sf::Vector2f Connections::calculateNormal(const sf::Vertex& pointA, const sf::Vertex& pointB)const
{
    sf::Vector2f vertex;
    float x;
    float y;
    x = pointB.position.x - pointA.position.x;
    y = pointB.position.y - pointA.position.y;
    std::swap(x, y);
    x = x * (-1);
    float normal = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    vertex.x = x / normal;
    vertex.y = y / normal;

    return vertex;
}

void Connections::drawBelt(const std::pair<const Connectable*, const Connectable*> each, sf::RenderWindow& window) const
{
    sf::Vector2f centerA;
    sf::Vector2f centerB;
    sf::Vector2f normal;
    sf::Vertex line1[2];
    sf::Vertex line2[2];
    float radius = ResourceManager::instance().getTexture(connectButton)->getSize().x/2;

    line1[0].color = sf::Color::Black;
    line1[1].color = sf::Color::Black;
    line2[0].color = sf::Color::Black;
    line2[1].color = sf::Color::Black;
  
    centerA = each.first->getConnectionButtonPos();
    centerB = each.second->getConnectionButtonPos();
    normal = calculateNormal(centerA, centerB);
    normal.x *= radius;
    normal.y *= radius;

    line1[0].position.x = (centerA.x + normal.x);
    line1[0].position.y = (centerA.y + normal.y);
    line1[1].position.x = (centerB.x + normal.x);
    line1[1].position.y = (centerB.y + normal.y);
    line2[0].position.x = (centerA.x - normal.x);
    line2[0].position.y = (centerA.y - normal.y);
    line2[1].position.x = (centerB.x - normal.x);
    line2[1].position.y = (centerB.y - normal.y);

    window.draw(line1, 2, sf::Lines);
    window.draw(line2, 2, sf::Lines);
}

void Connections::unplug(Connectable* toUnplug)
{
    Connectable* other  = nullptr;
    auto i = 0;
    for (; i < m_connections.size() ; i++)
    {
        if (m_connections[i].first == toUnplug)
        {
            other = m_connections[i].second;
            break;
        }
        else if (m_connections[i].second == toUnplug)
        {
            other = m_connections[i].first;
            break;
        }
    }
    setConnectedStatus(toUnplug, false);
    setConnectedStatus(other, false);
    m_connections.erase(m_connections.begin() + i);
    m_first = other;
}

void Connections::reset()
{
    m_first = nullptr;
    m_second = nullptr; //not really necessary
}

void Connections::setMousePos(const sf::Vector2f mouseLoc)
{
    m_mousePos = mouseLoc;
}

void Connections::drawMovingBelt(sf::RenderWindow &window) const
{
    sf::Vertex line[2];
    line[0].position = m_first->getConnectionButtonPos();
    line[0].color  = sf::Color::Black;
    line[1].position = m_mousePos;
    line[1].color = sf::Color::Black;

    window.draw(line, 2, sf::Lines);
}

void Connections::deleteConnection(Connectable* obj)
{
    Connectable* other;
    auto i = 0;
    for (; i < m_connections.size() ; i++)
    {
        if (m_connections[i].first == obj)
        {
            other = m_connections[i].second;
            break;
        }
        else if (m_connections[i].second == obj)
        {
            other = m_connections[i].first;
            break;
        }
    }
    setConnectedStatus(obj, false);
    setConnectedStatus(other, false);
    m_connections.erase(m_connections.begin() + i);
}