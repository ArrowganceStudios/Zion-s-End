#pragma once
#include <SFML/Graphics.hpp>

//	TODO:
//	Pass somehow the window size for proper alignments
//	More generic code for static texts
//	Improve encapsulation (?)
//	Add functionality to handle eye-candy animated sprites (?)

constexpr unsigned int	MAX_MESSAGES = 32;
constexpr unsigned int	MESSAGE_FONTSIZE = 15;
constexpr float			MESSAGE_DURATION_SECONDS = 1.5f;

class GUI
{
public:
	enum MessageType
	{
		POSITIVE,
		NEGATIVE,
		NEUTRAL
	};
	
	GUI();
	~GUI();

	void SetWindowSize(sf::Vector2u size) { m_WindowSize = size; }

	void Render(sf::RenderTarget& renderer) const;
	void Update(sf::Time deltaTime);

	void UpdateTitle(sf::String message);
	void UpdateMoneyValue(int newValue);
	void UpdateHealthValue(int newValue);
	void UpdateBufferValue() {
		sf::String str("");
		for (int i = 0; i < MAX_MESSAGES; ++i)
		{
			if (m_MessageBuffer.m_Messages[i].m_Alive)
				str += '!';
			else
				str += '.';
		}
		m_BufferText.setString(str); };
	void RequestMessage(sf::String message, sf::Vector2f position, GUI::MessageType type);

private:
	sf::Font m_DefaultFont;
	sf::Text m_TitleText;
	sf::Text m_MoneyText;
	sf::Text m_HealthText;
	sf::Text m_BufferText;

	sf::Vector2u m_WindowSize;

	struct Message
	{
		sf::Text m_Text;
		sf::Time m_LifeTime;
		bool m_Alive;
	};

	struct MessageBuffer
	{
		Message m_Messages[MAX_MESSAGES];
		unsigned int m_UsedCnt;
		unsigned int m_IdxOfFirst;
		void Push(sf::String message, sf::Vector2f position, GUI::MessageType type);
		void Pop();
		void Clear();
		void Erode(sf::Time timeStep);

		MessageBuffer();
	} m_MessageBuffer;
	
	//	potential sprites and so on
};