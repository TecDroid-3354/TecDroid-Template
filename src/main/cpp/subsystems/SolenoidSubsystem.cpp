#include "subsystems/SolenoidSubsystem.h"

SolenoidSubsystem::SolenoidSubsystem()
{
	SetName("SolenoidSubsystem");
}

SolenoidSubsystem::SolenoidSubsystem(unsigned int rightA, unsigned int rightB)
{

	ConfigureSolenoid(rightA, rightB);

	m_isDoubleSolenoid = false;

	SetName("SingleSolenoidSubsystem");
}

SolenoidSubsystem::SolenoidSubsystem(unsigned int rightA, unsigned int rightB, unsigned int leftA, unsigned int leftB)
{

	ConfigureSolenoids(rightA, rightB, leftA, leftB);

	m_isDoubleSolenoid = true;

	SetName("DoubleSolenoidSubsystem");
}

void SolenoidSubsystem::Periodic()
{
}

void SolenoidSubsystem::ConfigureSolenoids(unsigned int rightA, unsigned int rightB, unsigned int leftA, unsigned int leftB)
{
	m_rightSolenoid = new DoubleSolenoid(PneumaticsModuleType::REVPH, rightA, rightB);
	m_leftSolenoid = new DoubleSolenoid{PneumaticsModuleType::REVPH, leftA, leftB};
}

void SolenoidSubsystem::ConfigureSolenoid(unsigned int rightA, unsigned int rightB)
{
	m_rightSolenoid = new DoubleSolenoid(PneumaticsModuleType::REVPH, rightA, rightB);
}

void SolenoidSubsystem::OpenSolenoids()
{
	if (m_solenoidsInverted)
	{
		m_rightSolenoid->Set(DoubleSolenoid::Value::kForward);
		if (m_isDoubleSolenoid)
			m_leftSolenoid->Set(DoubleSolenoid::Value::kForward);
	}
	else
	{
		m_rightSolenoid->Set(DoubleSolenoid::Value::kReverse);
		if (m_isDoubleSolenoid)
			m_leftSolenoid->Set(DoubleSolenoid::Value::kReverse);
	}
}

void SolenoidSubsystem::CloseSolenoids()
{
	if (!m_solenoidsInverted)
	{
		m_rightSolenoid->Set(DoubleSolenoid::Value::kForward);
		if (m_isDoubleSolenoid)
			m_leftSolenoid->Set(DoubleSolenoid::Value::kForward);
	}
	else
	{
		m_rightSolenoid->Set(DoubleSolenoid::Value::kReverse);
		if (m_isDoubleSolenoid)
			m_leftSolenoid->Set(DoubleSolenoid::Value::kReverse);
	}
}

void SolenoidSubsystem::SolenoidsOff()
{
	m_rightSolenoid->Set(DoubleSolenoid::Value::kOff);
	if (m_isDoubleSolenoid)
		m_leftSolenoid->Set(DoubleSolenoid::Value::kOff);
}

unsigned int SolenoidSubsystem::GetRightSolenoid()
{
	return m_rightSolenoid->Get();
}

unsigned int SolenoidSubsystem::GetLeftSolenoid()
{
	return m_leftSolenoid->Get();
}

unsigned int SolenoidSubsystem::GetSolenoid()
{
	return GetRightSolenoid();
}

void SolenoidSubsystem::PrintSolenoids()
{

	if (m_isDoubleSolenoid)
	{
		SmartDashboard::PutNumber(GetName() + " Right Solenoid", GetRightSolenoid());
		SmartDashboard::PutNumber(GetName() + " Left Solenoid", GetLeftSolenoid());
	}
	else
	{
		SmartDashboard::PutNumber(GetName() + " Solenoid", GetSolenoid());
	}
}

void SolenoidSubsystem::ToggleSolenoids()
{
	if (m_isOpen)
	{
		OpenSolenoids();
	}
	else
	{
		CloseSolenoids();
	}
}

void SolenoidSubsystem::InvertSolenoids(bool inverted)
{
	m_solenoidsInverted = inverted;
}