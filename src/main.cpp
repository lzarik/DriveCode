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

// define your global instances of motors and other devices here

//Motor Setup 

vex::motor BackRight = vex::motor{vex::PORT12, true};
vex::motor BackLeft = vex::motor{vex::PORT4, false};
vex::motor FrontRight = vex::motor{vex::PORT7, true};
vex::motor FrontLeft = vex::motor{vex::PORT2, false};

vex::controller MainController;


void ArcadeDrive(int ChannelA, int ChannelB, int ChannelC)
{

    int FrontLeftPower = ChannelA + ChannelB + ChannelC;
    int FrontRightPower = ChannelA - ChannelB - ChannelC;
    int BackLeftPower = ChannelA - ChannelB + ChannelC;
    int BackRightPower = ChannelA + ChannelB - ChannelC;

    // Setting Motor Powers

    BackRight.setVelocity(BackRightPower,vex::percent);
    BackLeft.setVelocity(BackLeftPower,vex::percent);
    FrontRight.setVelocity(FrontRightPower,vex::percent);
    FrontLeft.setVelocity(FrontLeftPower,vex::percent);

    BackRight.spin(vex::forward);
    BackLeft.spin(vex::forward);
    FrontRight.spin(vex::forward);
    FrontLeft.spin(vex::forward);
}


int main() 
{
	
    Brain.Screen.printAt( 2, 30, "Hello IQ2" );
   
    while(1) {
        
        int Y = MainController.AxisA.position();
        int XStrafe = MainController.AxisB.position();
        int XDirection = MainController.AxisC.position();

        ArcadeDrive(Y, XStrafe, XDirection);
    }
}