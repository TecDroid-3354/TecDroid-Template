/*------------------------------------------------------------
						&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& /&&&&,
					.&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& /&&&&&&&&%
				.&&&&/ &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& /&&&&&&&&&&&*
			.%&&&(      &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&% %&&&&&&&&&&&&&
		%&&&#     %#&&#           (&&&&&&&&&&&              %&&&&&&&&&&&&&
	*&&&#                          (&&&&&&&&&&&    /           %&&&&&&&&&&&
*&%  ,                           (&&&&&&&&&&&(&&&&(           &&&&&&&&&&&
& (,..                          (&&&&&&&&&&&&&&&&            %&&&&&&&&&&
	&*                             (&&&&&&&&&&&&&&&&            &&&&&&&&&&&
	&/                             (&&&&&&&&&&&&&&&&%          &&&&&&&&&&&(
	#&&    .&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&#**(&&&&&&&&&&&&&#
	&#  (&                        ......... &&&&&&&&&&&&&&&&&&&&&&&&&&
	/&   &                                   .&&&&&&&&&&&&&&&&&&&&&&
		%&&* &*                                   ,%&&&&&&&&&&&&&%*

	Author: Esteban Padilla Cerdio
	Email: esteban37padilla@gmail.com
	URL: github.com/esteb37
		 github.com/tecdroid-3354
	Date: 12/04/2022
	Language: cpp
	Copyright (c) TecDroid 3354 and Esteban Padilla Cerdio
	Open Source Software; you can modify and/or share it under the terms of
*/

#pragma once

#include "subsystems/MotorSubsystem.h"
#include <frc/Encoder.h>
#include <frc/controller/PIDController.h>
#include <frc/smartdashboard/SmartDashboard.h>

namespace TecDroid
{
	enum class EncoderConfig
	{
		kFrc,
		kRev
	};

	class EncoderSubsystem : virtual public MotorSubsystem
	{
	public:
		/**
		 * @brief Construct a new EncoderSubsystem object without encoder and a single motor
		 * @param motorConfig The motor configuration
		 * @param motorPort The CAN ID of the motor
		 */
		EncoderSubsystem(MotorConfig, unsigned int);

		/**
		 * @brief Construct a new EncoderSubsystem object without encoder and various motors
		 * @param motorConfig The motor configuration
		 * @param motorPorts The CAN IDs of the motors
		 */
		EncoderSubsystem(MotorConfig, vector<unsigned int>);

		/**
		 * @brief Construct a new EncoderSubsystem object with a single NEO motor
		 * @param motorConfig The motor configuration
		 * @param encoderConfig The encoder configuration
		 * @param motorPort The CAN ID of the motor
		 */
		EncoderSubsystem(MotorConfig, EncoderConfig, unsigned int);

		/**
		 * @brief Construct a new EncoderSubsystem object with various NEO motors
		 * @param motorConfig The motor configuration
		 * @param encoderConfig The encoder configuration
		 * @param motorPorts The CAN IDs of the motors
		 */
		EncoderSubsystem(MotorConfig, EncoderConfig, vector<unsigned int>);

		/**
		 * @brief Construct a new EncoderSubsystem object with an FRC encoder and a single motor
		 * @param motorConfig The motor configuration
		 * @param encoderConfig The encoder configuration
		 * @param motorPort The CAN ID of the motor
		 * @param encoderA The A port of the encoder
		 * @param encoderB The B port of the encoder
		 */
		EncoderSubsystem(MotorConfig, EncoderConfig, unsigned int, unsigned int, unsigned int);

		/**
		 * @brief Construct a new EncoderSubsystem object with an FRC encoder and various motors
		 * @param motorConfig The motor configuration
		 * @param encoderConfig The encoder configuration
		 * @param motorPorts The CAN IDs of the motors
		 * @param encoderA The A port of the encoder
		 * @param encoderB The B port of the encoder
		 */
		EncoderSubsystem(MotorConfig, EncoderConfig, vector<unsigned int>, unsigned int, unsigned int);

		void Periodic() override;

		/**
		 * @brief Reset encoder and PIDs
		 */
		void Reset();

		// ---------- Motors -----------

		/**
		 * @brief Set the motor speed with safety considered
		 * @param speed The speed to set the motor to
		 */
		void SetMotor(double);

		/**
		 * @brief Set speeds of each motor with safety considered
		 * @param speeds The speeds to set the motors to
		 */
		void SetMotors(vector<double>);

		// ---------- Encoder ----------

		/**
		 * @brief Sets the encoder's value to 0
		 */
		void ResetEncoder();

		/**
		 * @brief Inverts the encoder's direction
		 * @param invert True to invert, false to not
		 */
		void InvertEncoder(bool);

		/**
		 * @brief Set the Encoders ports
		 * @param encoderA The A port of the encoder
		 * @param encoderB The B port of the encoder
		 * @warning This will create a new encoder object, be sure to reconfigure after
		 */
		void SetEncoderPorts(unsigned int, unsigned int);

		// ---------- Position PID -----------

		/**
		 * @brief Set the subsystem to a specified position
		 * @param position The position to set the subsystem to
		 * @param speed The speed at which the position will be set
		 * @return True if the subsystem is at the position, false otherwise
		 */
		bool SetPosition(double, double);

		/**
		 * @brief Get the encoder's position
		 * @return The encoder's position
		 */
		double GetPosition();

		/**
		 * @brief Configures the position's PID values, tolerance and direction
		 * @param p The proportional value
		 * @param i The integral value
		 * @param d The derivative value
		 * @param tolerance The tolerance of the position
		 * @param inverted Invert PID calculation
		 */
		void ConfigurePositionPID(double, double, double, double, bool = false);

		/**
		 * @brief Set the encoder's Position Conversion Factor
		 * @param conversionFactor The conversion factor
		 */
		void SetPositionConversionFactor(double);

		/**
		 * @brief Resets the position PID
		 */
		void ResetPositionPID();

		/**
		 * @brief Prints encoder's position
		 */
		void PrintPosition();

		/**
		 * @brief Prints position PID error
		 */
		void PrintPositionError();

		/**
		 * @brief Enables safety based on encoder position
		 *
		 */
		void SetPositionSafety(bool);

		/**
		 * @brief Sets the minimum and maximum position for safety
		 */
		void SetMinMaxPosition(double, double);

		// ---------- Speed PID -----------

		/**
		 * @brief Set the subsystem to a specified speed
		 * @param speed The speed to set the subsystem to
		 * @param acceleration The acceleration at which the speed will be set
		 * @return True if the subsystem is at the speed, false otherwise
		 */
		bool SetSpeed(double, double);

		/**
		 * @brief Get the encoder's rate
		 * @return The encoder's rate
		 */
		double GetSpeed();

		/**
		 * @brief Configures the speed's PID values, tolerance and direction
		 * @param p The proportional value
		 * @param i The integral value
		 * @param d The derivative value
		 * @param tolerance The tolerance of the speed
		 * @param inverted Invert PID calculation
		 */
		void ConfigureSpeedPID(double, double, double, double, bool = false);

		/**
		 * @brief Set the encoder's Speed Conversion Factor
		 * @param conversionFactor The conversion factor
		 */
		void SetSpeedConversionFactor(double);

		/**
		 * @brief Resets the speed PID
		 */
		void ResetSpeedPID();

		/**
		 * @brief Prints encoder's speed
		 */
		void PrintSpeed();

		/**
		 * @brief Prints speed PID error
		 */
		void PrintSpeedError();

		// ---------- Elements ----------

		SparkMaxRelativeEncoder *m_encoderSpark;

		Encoder *m_encoder;

		EncoderConfig m_encoderConfig;

		PIDController m_positionPID;

		PIDController m_speedPID;

	protected:
		int m_encoderDirection = 1;

		int m_positionPIDDirection = 1;

		int m_speedPIDDirection = 1;

		double m_speedConversionFactor = 1;

		double m_maxPosition = 100;

		double m_minPosition = 0;

		double m_maxRPM = 100;

		double m_speedCF;

		bool m_keepingStill = false;

		bool m_speedSafetyActive = false;

		bool m_positionSafetyActive = false;
	};
}
