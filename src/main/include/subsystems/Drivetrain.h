#pragma once

#include "Constants.h"
#include <frc/ADIS16448_IMU.h>
#include <frc/XboxController.h>
#include <frc/controller/PIDController.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc2/command/SubsystemBase.h>
#include <rev/CANSparkMax.h>
#include <subsystems/Limelight.h>

using namespace frc2;
using namespace frc;
using namespace rev;

class Drivetrain : public frc2::SubsystemBase
{
public:
	Drivetrain();

	~Drivetrain();

	void Periodic() override;

	// --------------------- Actions ----------------------

	void Drive(double, double);

	void Reset();

	void InvertSpeed(bool);

	void InvertRotation(bool);

	void SetSafetyEnabled(bool);

	// ---------------------- Motors ----------------------

	void ResetMotors();

	void InvertRight(bool);

	void InvertLeft(bool);

	void PrintFrontRight();

	void PrintFrontLeft();

	void PrintBackRight();

	void PrintBackLeft();

	void PrintRight();

	void PrintLeft();

	void PrintMotors();

	// --------------------- Encoders ---------------------

	double GetRightEncoders();

	double GetLeftEncoders();

	double GetEncoderAverage();

	void ResetEncoders();

	void InvertRightEncoders(bool);

	void InvertLeftEncoders(bool);

	void PrintFrontRightEncoder();

	void PrintFrontLeftEncoder();

	void PrintBackRightEncoder();

	void PrintBackLeftEncoder();

	void PrintRightEncoders();

	void PrintLeftEncoders();

	void PrintEncoders();

	// ----------------------- Gyro -----------------------

	double GetGyro();

	double GetGyroRad();

	void ResetGyro();

	void InvertGyro(bool);

	void PrintGyro();

	void PrintGyroRad();

	// ----------------------- Auto -----------------------

	/**
	 * @brief Sets the drivetrain to a given heading.
	 * @param distance The desired heading in meters.
	 * @param speed The speed at which to drive.
	 * @return Wether or not the drivetrain is at the desired heading.
	 */
	bool Move(double, double);

	/**
	 * @brief Turns the drievtrain to a given angle.
	 * @param angle The desired angle in degrees.
	 * @param speed The speed at which to turn.
	 * @return Whether or not the drivetrain has reached the desired angle
	 */
	bool Turn(double, double);

	/**
	 * @brief Moves the drivetrain to a given coordinate in meters
	 * @param x The desired x coordinate.
	 * @param y The desired y coordinate.
	 * @param speed The speed at which to drive.
	 * @param turnSpeed The speed at which to turn.
	 * @return Whether or not the drivetrain has reached the desired coordinate.
	 */
	bool MoveTo(double, double, double, double);

	/**
	 * @brief Align chasis to target
	 * @param speed The speed at which to drive.
	 * @return Whether or not the drivetrain has aligned to the target.
	 */
	bool AlignWithTarget(double);

	/**
	 * @brief Set drivetrain to a specific distance from the target
	 * @param distance The distance to the target in meters.
	 * @param speed The speed at which to drive.
	 * @return Whether or not the drivetrain has reached the desired distance
	 */
	bool SetDistanceWithTarget(double, double);

	/**
	 * @brief Set drivetrain to a specific angle from the target
	 * @param angle The angle to the target in degrees.
	 * @param speed The speed at which to drive.
	 * @return Whether or not the drivetrain has reached the desired angle
	 */
	bool SetAngleWithTarget(double, double);

	double GetAbsoluteAngle(double, double);

	void ResetMovePIDController();

	void ResetTurnPIDController();

	void ResetAlignPIDController();

	void ResetDistancePIDController();

	void ResetPIDControllers();

	void PrintMoveError();

	void PrintTurnError();

	void PrintMoveToError();

	void PrintAlignError();

	void PrintSetDistanceError();

	void PrintCurrentPosition();

private:
	// ----- Motors -----

	CANSparkMax m_frontLeft{pFrontLeft, CANSparkMaxLowLevel::MotorType::kBrushless};

	CANSparkMax m_frontRight{pFrontRight, CANSparkMaxLowLevel::MotorType::kBrushless};

	CANSparkMax m_backLeft{pBackLeft, CANSparkMaxLowLevel::MotorType::kBrushless};

	CANSparkMax m_backRight{pBackRight, CANSparkMaxLowLevel::MotorType::kBrushless};

	// ----- Motor controller groups-----

	MotorControllerGroup m_right{m_frontRight, m_backRight};

	MotorControllerGroup m_left{m_frontLeft, m_backLeft};

	// ----- Chasis drive object -----

	DifferentialDrive m_drive{m_left, m_right};

	// ----- Sensors -----

	SparkMaxRelativeEncoder m_frontRightEncoder{m_frontRight.GetEncoder()};

	SparkMaxRelativeEncoder m_frontLeftEncoder{m_frontLeft.GetEncoder()};

	SparkMaxRelativeEncoder m_backRightEncoder{m_backRight.GetEncoder()};

	SparkMaxRelativeEncoder m_backLeftEncoder{m_backLeft.GetEncoder()};

	ADIS16448_IMU m_gyro;

	Limelight m_limelight;

	// ----- Auto -----

	PIDController m_movePIDController{k_moveP, k_moveI, k_moveD};

	PIDController m_turnPIDController{k_turnP, k_turnI, k_turnD};

	PIDController m_alignPIDController{k_alignP, k_alignI, k_alignD};

	PIDController m_distancePIDController{k_distanceP, k_distanceI, k_distanceD};

	// ----- Attributes -----

	int m_gyroDirection = 1;

	int m_speedDirection = 1;

	int m_rotationDirection = 1;

	double m_currentX = 0;

	double m_currentY = 0;
};
