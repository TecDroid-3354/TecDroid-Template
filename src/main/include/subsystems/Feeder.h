#pragma once

#include "Constants.h"
#include <frc/motorcontrol/VictorSP.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSParkMax.h>

using namespace frc;
using namespace frc2;
using namespace rev;

class Feeder : public SubsystemBase
{

public:
	Feeder();

	void Periodic() override;

	// ---------- Motor -----------

	/**
	 * @brief Sets the Motor speed
	 * @param speed Speed and direction to turn
	 */
	void SetMotor(double);

	/**
	 * @brief Gets the Motor speed
	 */
	double GetMotor();

	/**
	 * @brief Invert motor direction
	 * @param invert True to invert, false to not
	 */
	void InvertMotor(bool);

	/**
	 * @brief Publishes the motor speed to the dashboard
	 */
	void PrintMotor();

private:
	VictorSP motor{pFeederMotor};

	// TODO : define motor type

	// CANSparkMax m_motor{pFeederMotor, CANSparkMax::MotorType::kBrushed};

	// VictorSPX m_motor{pFeederMotor};
};
