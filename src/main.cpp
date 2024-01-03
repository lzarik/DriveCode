/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       liz                                                       */
/*    Created:      10/25/2023, 9:00:27 AM                                    */
/*    Description:  IQ2 project                                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

// using namespace vex;

// A global instance of vex::brain used for printing to the IQ2 brain screen
vex::brain       Brain;

// Motor Setup 

vex::motor BackRight = vex::motor{vex::PORT12, true};
vex::motor BackLeft = vex::motor{vex::PORT4, false};
vex::motor FrontRight = vex::motor{vex::PORT7, true};
vex::motor FrontLeft = vex::motor{vex::PORT2, false};

vex::motor PTOMotorRight = vex::motor(vex::PORT8, true);
vex::motor PTOMotorLeft = vex::motor(vex::PORT1, false);

vex::pneumatic RightPiston = vex::pneumatic(vex::PORT4)

// Controller Setup
vex::controller MainController;

// Function that moves X Drive Chassis

void ArcadeDrive(int ChannelA, int ChannelB, int ChannelC)
{
    // X Drive Movement

    int FrontLeftPower = ChannelA + ChannelB + ChannelC;
    int FrontRightPower = ChannelA - ChannelB - ChannelC;
    int BackLeftPower = ChannelA - ChannelB + ChannelC;
    int BackRightPower = ChannelA + ChannelB - ChannelC;

    // Setting Motor Powers

    BackRight.setVelocity(BackRightPower,vex::percent);
    BackLeft.setVelocity(BackLeftPower,vex::percent);
    FrontRight.setVelocity(FrontRightPower,vex::percent);
    FrontLeft.setVelocity(FrontLeftPower,vex::percent);

    // Moving Motors

    BackRight.spin(vex::forward);
    BackLeft.spin(vex::forward);
    FrontRight.spin(vex::forward);
    FrontLeft.spin(vex::forward);
}

struct ButtonBumped
{
    private:
        int currentButtonState;
        int previousButtonState;
        vex::controller::button buttonToPress;
    public:
        void init(vex::controller::button desiredButton)
        {
            currentButtonState = false;
            previousButtonState = false;
            buttonToPress = desiredButton;
        }
        bool isBtnBumped()
        {
            previousButtonState = currentButtonState;
            currentButtonState = buttonToPress.pressing();
            
            return !currentButtonState && previousButtonState;
        }
};

enum LiftStates
{
    RestState,
    PurpleDumping,
    GreenDumping,
    ManualOverride,
};

struct Lift
{
    LiftStates state;
    int RestDegrees;
    int PurpleDumpingDegrees;
    int GreenDumpingDegrees;
};

ButtonBumped buttonLUp;
ButtonBumped buttonLDown;

void Intake()
{
    double IntakeVelocity = PTOMotorLeft.velocity(vex::percent);

    if(buttonLUp.isBtnBumped())
    {   
        if(IntakeVelocity == 0)
        {
           PTOMotorLeft.setVelocity(100, vex::percent);
           PTOMotorRight.setVelocity(100, vex::percent); 
        }
        else
        {
            PTOMotorLeft.setVelocity(0, vex::percent);
            PTOMotorRight.setVelocity(0, vex::percent);
        }
    }
    else if(buttonLDown.isBtnBumped())
    {
        if(IntakeVelocity == 0)
        {
            PTOMotorLeft.setVelocity(-100, vex::percent);
            PTOMotorRight.setVelocity(-100, vex::percent);
        }
        elsex
        {
            PTOMotorLeft.setVelocity(0, vex::percent);
            PTOMotorRight.setVelocity(0, vex::percent);
        }
    }

    PTOMotorLeft.spin(vex::forward);
    PTOMotorRight.spin(vex::forward);
}

void Setup()
{
    buttonLUp.init(MainController.ButtonLUp);
    buttonLDown.init(MainController.ButtonLDown);
}

int main() 
{  
    Setup();

    while(1) 
    {
        // Joystick Values
        int Y = MainController.AxisA.position();
        int XStrafe = MainController.AxisB.position();
        int XDirection = MainController.AxisC.position();

        // Calling X Drive Chassis Movement Function
        ArcadeDrive(Y, XStrafe, XDirection);

        Intake();
    }
}