/**
* @mainpage ZumoBot Project
* @brief    You can make your own ZumoBot with various sensors.
* @details  <br><br>
    <p>
    <B>General</B><br>
    You will use Pololu Zumo Shields for your robot project with CY8CKIT-059(PSoC 5LP) from Cypress semiconductor.This 
    library has basic methods of various sensors and communications so that you can make what you want with them. <br> 
    <br><br>
    </p>
    
    <p>
    <B>Sensors</B><br>
    &nbsp;Included: <br>
        &nbsp;&nbsp;&nbsp;&nbsp;LSM303D: Accelerometer & Magnetometer<br>
        &nbsp;&nbsp;&nbsp;&nbsp;L3GD20H: Gyroscope<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Reflectance sensor<br>
        &nbsp;&nbsp;&nbsp;&nbsp;Motors
    &nbsp;Wii nunchuck<br>
    &nbsp;TSOP-2236: IR Receiver<br>
    &nbsp;HC-SR04: Ultrasonic sensor<br>
    &nbsp;APDS-9301: Ambient light sensor<br>
    &nbsp;IR LED <br><br><br>
    </p>
    
    <p>
    <B>Communication</B><br>
    I2C, UART, Serial<br>
    </p>
*/

#include <project.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "Motor.h"
#include "Ultra.h"
#include "Nunchuk.h"
#include "Reflectance.h"
#include "Gyro.h"
#include "Accel_magnet.h"
#include "LSM303D.h"
#include "IR.h"
#include "Beep.h"
#include "mqtt_sender.h"
#include <time.h>
#include <sys/time.h>
#include "serial1.h"
#include <unistd.h>
/**
 * @file    main.c
 * @brief   
 * @details  ** Enable global interrupt since Zumo library uses interrupts. **<br>&nbsp;&nbsp;&nbsp;CyGlobalIntEnable;<br>
*/
// MOTOR TURNS LEFT (LEFT WHEEL GOING BACKWARDS)
void motor_turn_left(uint8 l_speed, uint8 r_speed, uint32 delay)
{
    MotorDirLeft_Write(1);
    MotorDirRight_Write(0);
    PWM_WriteCompare1(l_speed); 
    PWM_WriteCompare2(r_speed); 
    vTaskDelay(delay);
}
// MOTOR TURNS RIGHT (RIGHT WHEEL GOING BACKWARDS)
void motor_turn_right(uint8 l_speed, uint8 r_speed, uint32 delay)
{
    MotorDirLeft_Write(0);
    MotorDirRight_Write(1);
    PWM_WriteCompare1(l_speed); 
    PWM_WriteCompare2(r_speed); 
    vTaskDelay(delay);
}
#if 0
// Hello World!
void zmain(void)
{
    printf("\nHello, World!\n");

    while(true)
    {
        vTaskDelay(100); // sleep (in an infinite loop)
    }
 }   
#endif

#if 0
 // Assigment 2
    
// Name and age
void zmain(void)
{
    //char name[32];
    int age=0, start_time=0, end_time=0;
    int time;
    
    
    printf("\n\n");
    
    //printf("Enter your name: ");
    //fflush(stdout);
    //scanf("%s", name);
    start_time= xTaskGetTickCount();
    printf("Enter your age: ");
    //fflush(stdout);
    scanf("%d", &age);
    //printf("age = %d",age);
    end_time = xTaskGetTickCount();
    time = end_time - start_time;
     if(age <= 21){
        if(time < 3000){
            printf("Super fast dude!");
        }else if(time>=3000 && time<5000){
             printf("So mediocre.");
        }else if (time> 5000){
            printf("My granny is faster than you!");
        }
        else {
            printf("Time error");
        }
    } else if (age >= 22 && age <=50){
        if(time < 3000){
            printf("Be quick or be dead");
        }else if(time>=3000 && time<5000){
             printf("Youre so average.");
        }else if (time> 5000){
            printf("Have you been smoking something illegal?");
        }
        else {
            printf("Time error");
        }
    } else if(age>50){
        
        if(time < 3000){
            printf("Still going strong");
        }else if(time >= 3000 && time<5000){
             printf("You are doing ok for your age.");
        }else if (time> 5000){
            printf("Do they still allow youto drive?");
        }
        else {
            printf("Time error");
        }
    }else {
        printf("Problem with age");
    }
    
    
    //printf("You are [%s], age = %d\n", name, age);
    
    // bugg nothing after the bug will be printed. 
    printf("\n");
    
    
    while(true)
    {
        BatteryLed_Write(!SW1_Read());
        vTaskDelay(100);
    }
    
 }   
#endif

//Assigment 3
#if 0
//battery level//
void zmain(void)
{
    ADC_Battery_Start();        

    int16 adcresult =0;
    float volts = 0.0;

    printf("\nBoot\n");

    BatteryLed_Write(1); // Switch led on 
    //BatteryLed_Write(0); // Switch led off 
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed

    for(;;)
    {
        //char msg[80];
        float total_values;
        bool led = false;
        BatteryLed_Write(led);
        ADC_Battery_StartConvert(); // start sampling
        if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for ADC converted value
            adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
            // convert value to Volts
            total_values = 4095/(5*(3.0/2.0));
            volts = adcresult/total_values;
            // you need to implement the conversion
            
            if(volts < 4){
                do{
                    BatteryLed_Write(led);
                    vTaskDelay(500);
                    BatteryLed_Write(!led);
                    vTaskDelay(500);
                    printf("adc= %d volts= %f\r\n",adcresult, volts);
                }while(SW1_Read());
                
            }
            // Print both ADC results and converted value
            printf("adc= %d volts= %f\r\n",adcresult, volts);
        }
        vTaskDelay(500);
    }
 }   
#endif


#if 0
// button
void zmain(void)
{
    while(1) {
        printf("Press button within 5 seconds!\n");
        int i = 50;
        while(i > 0) {
            if(SW1_Read() == 0) {
                break;
            }
            vTaskDelay(100);
            --i;
        }
        if(i > 0) {
            printf("Good work\n");
            while(SW1_Read() == 0) vTaskDelay(10); // wait until button is released
        }
        else {
            printf("You didn't press the button\n");
        }
    }
}
#endif
// Assigment 1
#if 0
// button
void zmain(void)
{
    printf("\nBoot\n");

   //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 
    
    //uint8 button;
    //button = SW1_Read(); // read SW1 on pSoC board
    // SW1_Read() returns zero when button is pressed
    // SW1_Read() returns one when button is not pressed
    
    bool led = false;
    
    for(;;)
    {
        // toggle led state when button is pressed
        if(SW1_Read() == 0) {
            led = !led;
            BatteryLed_Write(led);
            if(led){ 
                printf("Led is ON\n");
                 BatteryLed_Write(led);
                vTaskDelay(500);
                BatteryLed_Write(!led);
                vTaskDelay(500);
                BatteryLed_Write(led);
                vTaskDelay(500);
                BatteryLed_Write(!led);
                vTaskDelay(500);
                BatteryLed_Write(led);
                vTaskDelay(500);
                BatteryLed_Write(!led);
                vTaskDelay(500);
                // Long blinks 1,5s
                BatteryLed_Write(led);
                vTaskDelay(1500);
                BatteryLed_Write(!led);
                vTaskDelay(500);
                BatteryLed_Write(led);
                vTaskDelay(1500);
                BatteryLed_Write(!led);
                vTaskDelay(500);
                BatteryLed_Write(led);
                vTaskDelay(1500);
                BatteryLed_Write(!led);
                vTaskDelay(500);
                // Short blink 0,5s
                BatteryLed_Write(led);
                vTaskDelay(500);
                BatteryLed_Write(!led);
                vTaskDelay(500);
                BatteryLed_Write(led);
                vTaskDelay(500);
                BatteryLed_Write(!led);
                vTaskDelay(500);
                BatteryLed_Write(led);
                vTaskDelay(500);
                BatteryLed_Write(!led);
                vTaskDelay(500);
                led=!led;
                continue; 
                
            }
            else{
                printf("Led is OFF\n");
           // Beep(1000, 150);
               
                
                }
            while(SW1_Read() == 0) vTaskDelay(10); // wait while button is being pressed
        }        
    }
 }   


#endif

// Assigment 2 week 3 
#if 0
//ultrasonic sensor//
void zmain(void)
{
    Ultra_Start();                          // Ultra Sonic Start function
    motor_start();
     
   
    while(1) {
        motor_forward(100,100);
        int d = Ultra_GetDistance();
        if(d < 10){
            Beep(100,100);
            motor_backward(0,0);
            motor_turn(100,50,2000);
            motor_forward(0,0);
            continue;
        }
        
        // Print the detected distance (centimeters)
        printf("distance = %d\r\n", d);
        vTaskDelay(200);
        
    }
}   
#endif

#if 0
//IR receiverm - how to wait for IR remote commands
void zmain(void)
{
    IR_Start();
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    bool led = false;
    // Toggle led when IR signal is received
    for(;;)
    {
        IR_wait();  // wait for IR command
        led = !led;
        BatteryLed_Write(led);
        if(led) printf("Led is ON\n");
        else printf("Led is OFF\n");
    }    
 }   
#endif



#if 0
//IR receiver - read raw data
void zmain(void)
{
    IR_Start();
    
    uint32_t IR_val; 
    
    printf("\n\nIR test\n");
    
    IR_flush(); // clear IR receive buffer
    printf("Buffer cleared\n");
    
    // print received IR pulses and their lengths
    for(;;)
    {
        if(IR_get(&IR_val, portMAX_DELAY)) {
            int l = IR_val & IR_SIGNAL_MASK; // get pulse length
            int b = 0;
            if((IR_val & IR_SIGNAL_HIGH) != 0) b = 1; // get pulse state (0/1)
            printf("%d %d\r\n",b, l);
        }
    }    
 }   
#endif


#if 1
//reflectance
void zmain(void)
{ 
    float mustan_lasku = 0;
    enum state{START, STOP};
    enum state robot_state = STOP;
    bool increment_mustan_lasku = true;
    struct sensors_ ref;
    struct sensors_ dig;
    // Eka tehtävä pysähdys_kohta = 4  toka = 2
    int pysahdys_kohta = 5;
   
    reflectance_start();
    reflectance_set_threshold(9000, 9000, 11000, 11000, 9000, 9000); // set center sensor threshold to 11000 and others to 9000
    
    for(;;)
    {
        // read raw sensor values
        reflectance_read(&ref);
        // print out each period of reflectance sensors
        //printf("%5d %5d %5d %5d %5d %5d\r\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
        
        // read digital values that are based on threshold. 0 = white, 1 = black
        // when blackness value is over threshold the sensors reads 1, otherwise 0
        reflectance_digital(&dig); 
        //print out 0 or 1 according to results of reflectance period
        printf("%5d %5d %5d %5d %5d %5d \r\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);        
        //motor_forward(100,50);

        //MOOTORI KÄYNTIIN JA PÄÄLLE NAPIN PAINETTUA
        if (SW1_Read() == 0){
            printf("\r\nstate before: %d\r\n", robot_state);
            if(robot_state == STOP){
                motor_start();
                robot_state = START;
            }
            else if(robot_state == START){
                motor_stop();
                robot_state = STOP;
            }
            printf("\r\nstate after: %d\r\n", robot_state);
        }
        
       
        // KAIKKI VALKOISET
        if(dig.l3 == 0 && dig.l2 == 0 && dig.l1 == 0 && dig.r1 == 0 && dig.r2 == 0 && dig.r3 == 0){
            motor_forward(30,1);
        }
        
        // JOS OLLAAN PÄÄSTY VALKOISELLE ALUEELLA VOIDAAN LISÄTÄ MUSTAAN LASKURIIN
        if(dig.l3 == 0 && dig.r3 == 0){
            motor_forward(30,3);   
            increment_mustan_lasku = true;
        }
        // VÄRILLISET VAIHTOEHDOT (eka musta)
        if(dig.l3 == 1 && dig.l2 == 1 && dig.l1 == 1 && dig.r1 == 1 && dig.r2 == 1 && dig.r3 == 1 ) {
            if(increment_mustan_lasku){
                mustan_lasku = (int)mustan_lasku + 1;   
                increment_mustan_lasku = false;
            }
            // pysähtyy ekassa koko mustassa
            if(mustan_lasku == 1){
                printf("Got here");
                motor_forward(0,0);
                mustan_lasku++;
                robot_state = STOP;
                    
            } //TEHTÄVÄ 1 ja 3,Tarkistaa jos musta laskuri on yli tai ali halutun pysähdys kohdan
            /*else if (robot_state == START && mustan_lasku <= pysahdys_kohta) {
               motor_forward(30,1);
            } else if (mustan_lasku > pysahdys_kohta) {
            motor_forward(0,0);
            mustan_lasku = 0;
            robot_state = STOP;
            } */
            // Tehtävä 2
            else if (robot_state == START && mustan_lasku == 2) {
             motor_forward(60,1);
            }else if (robot_state == START && mustan_lasku == 3) {
               printf("first turn");
               
               motor_turn_left(60,100,300);
            } else if (robot_state == START && mustan_lasku <= 5) {
               printf("secound");
                
               motor_turn_right(100,60,300);
            } 
            else if (mustan_lasku > pysahdys_kohta) {
            motor_forward(0,0);
            mustan_lasku = 0;
            robot_state = STOP;
            }
            
        } else if(dig.l2 == 0 && dig.l1 == 1 && dig.r1 == 1 && dig.r2 == 0){
            //Seuraa keskimmäistä viivaa
            motor_forward(60,1);
        } else if (dig.l2 == 0 && dig.l1 == 0 && dig.r1 == 1 && dig.r2 == 1) {
            //Anturit r1 ja r2 mustat
            motor_turn_right(60,60,1);
        } else if(dig.l2 == 1 && dig.l1 == 1 && dig.r1 == 0 && dig.r2 == 0){
            //l2 ja l1 ovat mustat
            motor_turn_left(60,60,1);
        } else if (dig.l2 == 0 && dig.l1 == 0 && dig.r1 == 0 && dig.r3 == 1){
            //r2 ja r3 ovat mustat
             motor_turn_right(60,60,1);
        } else if ( dig.l3 == 1  && dig.l1 == 0 && dig.r1 == 0 && dig.r2 == 0){
            // l3 ja l2 mustat
             motor_turn_left(60,60,1);
        } 
        
        printf("mustan_lasku : %f \r\n ", mustan_lasku); 
        vTaskDelay(200);
    }
    
}   

#endif

//ASSIGMENT 1 week 3 
#if 0
    
//motor
void zmain(void)
{
    
    
    motor_start();              // enable motor controller
    motor_forward(0,0);         // set speed to zero to stop motors

    vTaskDelay(2000);
    // First straight
    motor_forward(100,4000);
    motor_forward(0,500);
     motor_turn(100,0,1115); 
    // Secound curve
    motor_forward(100,3120);
    motor_forward(0,500);
    motor_turn(100,0,1550);
    //Last big straight
    motor_forward(100,3000);
    // Kurvi
    motor_turn(100,0,1500);
    motor_turn(100,35,4000);
    motor_forward(100,1400);
    //motor_turn(50,200,2000);     // turn
    //motor_backward(100,2000);    // moving backward
     
    motor_forward(0,0);         // stop motors

    motor_stop();               // disable motor controller
    
    for(;;)
    {
        
    }
}
#endif

#if 0
    //lisäsin just
    #include <stdlib.h>
/* Example of how to use te Accelerometer!!!*/
void zmain(void)
{  //just lisätty
    motor_start();
    int randomnr,random_time;
   
   
    struct accData_ data;
    
    printf("Accelerometer test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Device Ok...\n");
    }
    
    for(;;)
    {
         // sama tää
       
        if(data.accX > -500){
            random_time =  rand() % 30;
            
            if(random_time == 29){
                motor_turn(100,0,500); 
            } else if(random_time == 28) {
               motor_turn(0,100,500);
            } 
        };
         motor_forward(100,50);
        LSM303D_Read_Acc(&data);
        printf("%8d %8d %8d\n",data.accX, data.accY, data.accZ);
        
       
        if(data.accX < -1500){
            randomnr= rand() % 2;
            //Kääntö random suuntaan just lisätty
            if(randomnr == 1){
               // Beep(100,100);
                motor_backward(100,500);
                motor_turn(100,0,1500);
                
            } else {
               // Beep(100,100);
                motor_backward(100,500);
                motor_turn(0,100,1500);
                
            }
         
        }
        
    }
 }   
#endif    

#if 0
// MQTT test
void zmain(void)
{
    int ctr = 0;

    printf("\nBoot\n");
    send_mqtt("Zumo01/debug", "Boot");

    //BatteryLed_Write(1); // Switch led on 
    BatteryLed_Write(0); // Switch led off 

    for(;;)
    {
        printf("Ctr: %d, Button: %d\n", ctr, SW1_Read());
        print_mqtt("Zumo01/debug", "Ctr: %d, Button: %d", ctr, SW1_Read());

        vTaskDelay(1000);
        ctr++;
    }
 }   
#endif


#if 0
void zmain(void)
{    
    struct accData_ data;
    struct sensors_ ref;
    struct sensors_ dig;
    
    printf("MQTT and sensor test...\n");

    if(!LSM303D_Start()){
        printf("LSM303D failed to initialize!!! Program is Ending!!!\n");
        vTaskSuspend(NULL);
    }
    else {
        printf("Accelerometer Ok...\n");
    }
    
    int ctr = 0;
    reflectance_start();
    for(;;)
    {
        LSM303D_Read_Acc(&data);
        // send data when we detect a hit and at 10 second intervals
        if(data.accX > 1500 || ++ctr > 1000) {
            printf("Acc: %8d %8d %8d\n",data.accX, data.accY, data.accZ);
            print_mqtt("Zumo01/acc", "%d,%d,%d", data.accX, data.accY, data.accZ);
            reflectance_read(&ref);
            printf("Ref: %8d %8d %8d %8d %8d %8d\n", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);       
            print_mqtt("Zumo01/ref", "%d,%d,%d,%d,%d,%d", ref.l3, ref.l2, ref.l1, ref.r1, ref.r2, ref.r3);
            reflectance_digital(&dig);
            printf("Dig: %8d %8d %8d %8d %8d %8d\n", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);
            print_mqtt("Zumo01/dig", "%d,%d,%d,%d,%d,%d", dig.l3, dig.l2, dig.l1, dig.r1, dig.r2, dig.r3);
            ctr = 0;
        }
        vTaskDelay(10);
    }
 }   

#endif

#if 0
void zmain(void)
{    
    RTC_Start(); // start real time clock
    
    RTC_TIME_DATE now;

    // set current time
    now.Hour = 12;
    now.Min = 34;
    now.Sec = 56;
    now.DayOfMonth = 25;
    now.Month = 9;
    now.Year = 2018;
    RTC_WriteTime(&now); // write the time to real time clock

    for(;;)
    {
        if(SW1_Read() == 0) {
            // read the current time
            RTC_DisableInt(); /* Disable Interrupt of RTC Component */
            now = *RTC_ReadTime(); /* copy the current time to a local variable */
            RTC_EnableInt(); /* Enable Interrupt of RTC Component */

            // print the current time
            printf("%2d:%02d.%02d\n", now.Hour, now.Min, now.Sec);
            
            // wait until button is released
            while(SW1_Read() == 0) vTaskDelay(50);
        }
        vTaskDelay(50);
    }
 }   
#endif

/* [] END OF FILE */
