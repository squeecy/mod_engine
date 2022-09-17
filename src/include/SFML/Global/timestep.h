#pragma once
struct 
{
	float d_t;
	float GetSeconds() const {return m_Time;}
	float GetMilliseconds() const {return m_Time * 1000.0f;}

	private: 
		float m_Time;
}timeStep;



