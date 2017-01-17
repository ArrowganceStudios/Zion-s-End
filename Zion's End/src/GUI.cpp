#include "GUI.h"

GUI::GUI()
{
	m_DefaultFont.loadFromFile("assets/arial.ttf");

	for (int i = 0; i < MAX_MESSAGES; ++i)
	{
		sf::Text &textRef = m_MessageBuffer.m_Messages[i].m_Text;
		textRef.setCharacterSize(MESSAGE_FONTSIZE);
		textRef.setFont(m_DefaultFont);
	}

	m_TitleText.setString("You mustn't allow an unauthorized exegesis of Zion Bible to happen!");

	m_TitleText.setCharacterSize(30);
	m_TitleText.setFont(m_DefaultFont);
	m_TitleText.setPosition({ 0, 0 });

	m_MoneyText.setCharacterSize(30);
	m_MoneyText.setFont(m_DefaultFont); 
	m_MoneyText.setPosition({ 0, 40 });

	m_HealthText.setCharacterSize(30);
	m_HealthText.setFont(m_DefaultFont);
	m_HealthText.setPosition({ 0, 80 });

	m_BufferText.setCharacterSize(30);
	m_BufferText.setFont(m_DefaultFont);
	m_BufferText.setPosition({ 0, 120 });
}

GUI::~GUI()
{
}

void GUI::Render(sf::RenderTarget & renderer) const
{
	renderer.draw(m_TitleText);
	renderer.draw(m_MoneyText);
	renderer.draw(m_HealthText);
	renderer.draw(m_BufferText);

	for (int i = 0; i < MAX_MESSAGES; ++i)
	{
		const Message &msgRef = m_MessageBuffer.m_Messages[i];
		if (msgRef.m_Alive)
			renderer.draw(msgRef.m_Text);
	}
}

void GUI::Update(sf::Time deltaTime)
{
	m_MessageBuffer.Erode(deltaTime);
	UpdateBufferValue();
}

void GUI::UpdateMoneyValue(int newValue)
{
	m_MoneyText.setString("Money: " + std::to_string(newValue));
}

void GUI::UpdateHealthValue(int newValue)
{
	m_HealthText.setString("Health: " + std::to_string(newValue));
}

void GUI::RequestMessage(sf::String message, sf::Vector2f position, GUI::MessageType type)
{
	m_MessageBuffer.Push(message, position, type);
}

void GUI::MessageBuffer::Push(sf::String message, sf::Vector2f position, GUI::MessageType type)
{
	if (m_UsedCnt >= MAX_MESSAGES) return;

	unsigned int index = (m_IdxOfFirst + m_UsedCnt) % MAX_MESSAGES;
	Message &msgRef = m_Messages[index];

	msgRef.m_Text.setString(message);
	msgRef.m_Text.setPosition(position);
	msgRef.m_Text.setOrigin( {msgRef.m_Text.getLocalBounds().width / 2, msgRef.m_Text.getLocalBounds().height / 2});
	msgRef.m_LifeTime = sf::seconds(MESSAGE_DURATION_SECONDS);
	msgRef.m_Alive = true;

	switch (type)
	{
	case GUI::MessageType::POSITIVE:
		msgRef.m_Text.setColor(sf::Color::Green);
		break;
	case GUI::MessageType::NEGATIVE:
		msgRef.m_Text.setColor(sf::Color::Red);
		break;
	case GUI::MessageType::NEUTRAL:
	default:
		msgRef.m_Text.setColor(sf::Color::White);
		break;
	}

	++m_UsedCnt;
}

void GUI::MessageBuffer::Pop()
{
	Message &msgRef = m_Messages[m_IdxOfFirst];
	msgRef.m_Alive = false;

	m_IdxOfFirst = (m_IdxOfFirst + 1) % MAX_MESSAGES;
	if(m_UsedCnt > 0)
		--m_UsedCnt;
}

void GUI::MessageBuffer::Clear()
{
	for (int i = 0; i < MAX_MESSAGES; ++i)
	{
		m_Messages[i].m_Alive = false;
		m_Messages[i].m_LifeTime = sf::seconds(0);
	}
	m_UsedCnt = 0;
	m_IdxOfFirst = 0;
}

void GUI::MessageBuffer::Erode(sf::Time timeStep)
{
	for (unsigned i = m_IdxOfFirst; i < m_IdxOfFirst + m_UsedCnt; ++i)
	{
		Message &msgRef = m_Messages[i % MAX_MESSAGES];
		msgRef.m_LifeTime -= timeStep;
		msgRef.m_Text.move({sinf(10 * msgRef.m_LifeTime.asSeconds()), -timeStep.asSeconds() * 40 });
	}

	if (m_Messages[m_IdxOfFirst].m_LifeTime < sf::seconds(0)) Pop();
}

GUI::MessageBuffer::MessageBuffer()
{
	Clear();
}
