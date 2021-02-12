/******************************************************************************
                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.
*******************************************************************************/

#include <stdio.h>
#include <string.h>

#define Maske_Q1  1 // Motorbits von Achse 0

#define Maske_Q2  2

#define Maske_Q3  4 // Motorbits von Achse 1

#define Maske_Q4  8

#define Maske_Q5 16 // Motorbits von Achse 2

#define Maske_Q6 32

#define Maske_Q7 64 // Motorbits von Achse 3

#define Maske_Q8 128 


//Defining all the general states
const int STATE_TURN_OFF_MOTORS = 1;
const int EXIT = 2;
const int STATE_GO_TO_0_POS = 3;
const int STATE_TEACHING_NEW_POSITIONS = 4;
const int STATE_GO_TO_WISH_POS = 5;
const int STATE_PREPARE_TO_WISH_POS = 6;

//defining the states when checking if we are at the desired position or not
const int CURRENT_LESS_DESIRED_POSITION = 7;
const int CURRENT_MORE_DESIRED_POSITION = 8;
const int CURRENT_EQUAL_DESIRED_POSITION = 9;

//Defining the size of our 2D-Array
const int MAX_ROWS = 5;
const int MAX_COLUMNS = 4;


//Defining The states of the Ritzel in order to detect a change
//const int STATE_RITZEL_NOT_CHANGE = 1;
//const int STATE_RITZEL_CHANGE = 2;
//const int STATE_INCREASE_COUNTER = 3;
//const int EXIT_INCREASE = 4;


void Turn_off(int Axe)
{

    switch(Axe)
    {
        case 0:
        printf("\nAxe 0 is off");
        // Q1_bis_Q8 = Q1_bis_Q8 & ~(Maske_Q1 | Maske_Q2);
        //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
        break;
        
        case 1:
        printf("\nAxe 1 is off");
        //Q1_bis_Q8 = Q1_bis_Q8 & ~(Maske_Q3 | Maske_Q4);
        //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
        break;
        
        case 2:
        printf("\nAxe 2 is off");
        //Q1_bis_Q8 = Q1_bis_Q8 & ~(Maske_Q5 | Maske_Q6);
        //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
        break;
        
        case 3:
        printf("\nAxe 3 is off");
        //Q1_bis_Q8 = Q1_bis_Q8 & ~(Maske_Q7 | Maske_Q8);
        //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
        break;
        default:
        break;
    }
}


void Move_Back(int Axe, int is_knickarm)
{
    switch(Axe)
    {
         case 0:
        printf("\nThe axis(0) was moved In the clock direction");
        //Q1_bis_Q8 = (Q1_bis_Q8 | 0xFF) & Maske_Q2;
        //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
        break;
        
        case 1:
        printf("\nThe axis(1) was moved Backwards");
        //Q1_bis_Q8 = (Q1_bis_Q8 | 0xFF) & Maske_Q4;
        //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
        break;
        
        case 2:
        printf("\nThe axis(2) was moved Up");
        //Q1_bis_Q8 = (Q1_bis_Q8 | 0xFF) & Maske_Q6;
        //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
        break;
        
        case 3:
        if(is_knickarm==1)
        {
            printf("\nAxe 3 is closing"); 
            //Q1_bis_Q8 = (Q1_bis_Q8 | 0xFF) & Maske_Q8;
            //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
            break;
        }
        else
        {
            printf("\nAxe 3 is oppening");
            //Q1_bis_Q8 = (Q1_bis_Q8 | 0xFF) & Maske_Q8;
            //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
            break;
        }
        
        default:
        break;
    }
}

void Move_Forward(int Axe, int is_knickarm)
{
    switch(Axe)
    {
         case 0:
        printf("\nThe axis(0) was moved Against the clock direction");
        //Q1_bis_Q8 = (Q1_bis_Q8 | 0xFF) & Maske_Q1;
        //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
        break;
        
        case 1:
        printf("\nThe axis(1) was moved Forward");
        //Q1_bis_Q8 = (Q1_bis_Q8 | 0xFF) & Maske_Q3;
        //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
        break;
        
        case 2:
        printf("\nThe axis(2) was moved Down");
        //Q1_bis_Q8 = (Q1_bis_Q8 | 0xFF) & Maske_Q5;
        //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
        break;
        
        case 3:
        if(is_knickarm==1)
        {
            printf("\nThe axis(3) was moved to open"); //Öffnen
            //Q1_bis_Q8 = (Q1_bis_Q8 | 0xFF) & Maske_Q7;
            //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
            break;
        }
        else
        {
            printf("\nThe axis(3) was moved to close"); 
            //Q1_bis_Q8 = (Q1_bis_Q8 | 0xFF) & Maske_Q7;
            //iic_sende_pcf8574 (adrsende, Q1_bis_Q8);
            break;
        }
        
        default:
        break;
    }
}


void Setting_Max_Min_Counter(int *counter_axis, int Axis, int maximum, int minimum, int Is_Increament)
{
    
    if(Is_Increament==1)
    {
        if (counter_axis[Axis]> maximum-1)
        {
            counter_axis[Axis] = maximum; 
        }
        else
        {
            counter_axis[Axis] += 1; //Just used for simulation, in the real programm is not being used (just comment this line)
        }
    }
    else
    {
        if(counter_axis[Axis]< minimum +1)
        {
            counter_axis[Axis] = minimum;
        }
        else
        {
            counter_axis[Axis] -= 1; //Just used for simulation, in the real programm is not being used (just comment this line)
        }
    }
    
}

void Init_Zeros(int rows, int columns, int TwoDimArray[MAX_ROWS][MAX_COLUMNS])
{
    for(int outside=0; outside<rows; outside++)
    {
        for(int inner=0; inner<columns; inner++)
        {
            TwoDimArray[outside][inner] = 0;
        }
    }
}

void Print_Array(int rows, int columns, int TwoDimArray[MAX_ROWS][MAX_COLUMNS])
{
    for(int outside=0; outside<rows; outside++)
    {
        printf("[");
        for(int inner=0; inner<columns; inner++)
        {
            printf("%i", TwoDimArray[outside][inner]);
        }
        printf("]\n");
    }
}

void Allocate_New_Position(int columns, int TwoDimArray[MAX_ROWS][MAX_COLUMNS], int Counter_Used_Positions, int Teaching_Array[MAX_COLUMNS])
{
    for(int inner=0; inner<columns; inner++)
    {
        TwoDimArray[Counter_Used_Positions][inner] = Teaching_Array[inner];
    }
}

int check_existance_positions(int rows, int columns, int TwoDimArray[MAX_ROWS][MAX_COLUMNS], int Teaching_Array[MAX_COLUMNS])
{
    int compare[]={0,0,0,0};
    int result = 1;
    
    for(int outside=0; outside<rows; outside++)
    {
        for(int inner=0; inner<columns; inner++)
        {
           compare[inner] = TwoDimArray[outside][inner] - Teaching_Array[inner];
        }
        if (compare[0]==0 && compare[1]==0 && compare[2]==0 && compare[3]==0 )
        {
            return result;
        }
    }
    result = 0;
    return result;
}



int main()
{
    
    int Axis[] = {0,1,2,3}; //All 4 axis saved in a field
    
    int Num_axes= 4; //total number of axis
    
    int Current_State = STATE_TURN_OFF_MOTORS;
    int Last_State;
    //int CURRENT_RITZEL_STATE = STATE_RITZEL_NOT_CHANGE;
    
    int counter = 0;
    int counter_axis[] = {2,3,4,5}; //these are our Ritzel counter for each axis
    int Counter_Used_Positions = 0; //We use this to check how many positions we have left when we save the values after teaching
    int Current_Row_Counter = 0;    //We use this value to check how many times we need to read the "teaching" values so we can repeat it
    
    int is_knickarm = 1; //if is_knickarm = 1 then we are using knickarm, otherwise we are using saulen
    int Is_Increament = 1; // if Is_Increament = 1 we are going to Increase the Ritzel Counter, otherwhise we are decreasing it
    int Flag_last_saved = 1; //we use this variable to check if a specific coordinate was already "teach"
    
    int maximum[] = {6,6,6,6}; //maximums counters for every axis
    int minimum[] = {0,0,0,0}; //minimums "" "" "" ""
    
    int teaching_counter_axis[]={0,0,0,0}; //we use these 4 elements as buffer when we save our coordinates after teaching
    int multiple_positions[MAX_ROWS][MAX_COLUMNS]; //Here we declare a 2D-Array where we are going to save all the coordinates from teaching
    
    Init_Zeros(MAX_ROWS, MAX_COLUMNS, multiple_positions); //Here we initialize all of our 2D-Array coordinates to 0 
    
    
    char ch; //We use this value when simulating our Input Data
    
    
    //uint8 Ritzel_Achse[] = {1,2,4,8};  //Here we define the Ritzel_Achse for each axis, also axis_0 = 1, and so on....
    //uint8 Nullanschlag_Achse[] = {16,32,64,128}; //here we define the Nullanschlag for each axis, also axis_0 = 16 and so on...
    
    //uint8 I1_bis_I8;
    
                
    while (1)
    {
        switch(Current_State)
        {
            case 1://STATE_TURN_OFF_MOTORS
                for(int axis=0;axis<Num_axes; axis++)
                    {
                        Turn_off(axis);
                    }
                Last_State = Current_State;
                Current_State = STATE_GO_TO_0_POS;
                break;
            
            case 3://STATE_GO_TO_0_POS
                
                if(Last_State == CURRENT_EQUAL_DESIRED_POSITION)
                {
                    Num_axes=3;
                }
                else
                {
                    Num_axes=4;    
                }
                
                for(int axis=0; axis<Num_axes; axis++)
                {
                    counter = counter_axis[axis];
                    //I1_bis_I8   = iic_lese_pcf8574 (adrlese);
                    //I1_bis_I8   = ~I1_bis_I8;
                    
                    while(1)
                    {
                        if (counter==0) //((I1_bis_I8 & Nullanschlag_Achse[axis])==0)
                        {
                            counter_axis[axis] = counter;
                            printf("\nThe Axis: %i is at the 0 Position", axis);
                            Turn_off(axis);
                            //Serial.println("datata von Adresse:");
                            //Serial.println(adrlese, DEC);
                            //Serial.println(datat, BIN);
                            //Serial.println(" ");
                            break;
                        }
                        else
                        {
                            Move_Back(axis,is_knickarm);
                            counter -= 1; //Here we decreament for simulation purpose but in the real program there is no need to decrease
                        }
                    }
                }
                
                if(Last_State == CURRENT_EQUAL_DESIRED_POSITION)
                {
                    Turn_off(Axis[3]);
                    Current_State = STATE_GO_TO_WISH_POS;
                    break;
                }
                else
                {
                    Current_State = STATE_TEACHING_NEW_POSITIONS;
                    break;
                }
                
            case 4: //STATE_TEACHING_NEW_POSITIONS
            
            printf("\nDo you want to (Enter first letter):\n");
            printf("Go (F)orward, (B)ackwards, (D)own, (U)p, (I)n Clock, (A)gainst Clock, (C)lose, (O)pen, (E)xit, (P)rint, (R)eset, (S)ave, (W)ieder?\n");
            
            while(1)
            {
                //do 
                //{
                printf("Your choice: ");
                ch=getchar();
                while(ch=='\n')
                {
                    ch=getchar();
                }
                //} while(ch!='F' && ch!='B' && ch!='D' && ch!='U' && ch!='I' && ch!='A' && ch!='C' && ch!='O' && ch!='E' && ch!='S' && ch!='P' && ch!='R' && ch!='W');

                
                switch(ch) 
                {
                case 'F': //Forwards
                    goto Increment_counter_Axis_1;
                    Increment_Forward_Counter_Teaching:
                    printf(" (counter axis(1) =%i)\n", counter_axis[1]);
                    break;
                  
                  
                case 'B'://Backwards
                    goto Decrement_counter_Axis_1;
                    Decrement_Backwards_Counter_Teaching:
                    printf(" (counter axis(1) =%i)\n", counter_axis[1]);
                    break;
                  
                  
                case 'D'://Down
                    goto Increment_counter_Axis_2;     
                    Increment_Down_Counter_Teaching:
                    printf(" (counter axis(2) =%i)\n", counter_axis[2]);
                    break;
                  
                  
                case 'U'://Up
                    goto Decrement_counter_Axis_2;
                    Decrement_Up_Counter_Teaching:
                    printf(" (counter axis(2) =%i)\n", counter_axis[2]);
                    break;
                  
                  
                case 'I'://In Clock Direction
                    goto Decrement_counter_Axis_0; 
                    Decrement_InClock_Counter_Teaching:
                    printf(" (counter axis(0) =%i)\n", counter_axis[0]);
                    break;
                  
                  
                case 'A'://Against Clock Direction
                    goto Increment_counter_Axis_0;
                    Increment_Against_Counter_Teaching:
                    printf(" (counter axis(0) =%i)\n", counter_axis[0]);
                    break;
                  
                  
                case 'C'://Close
                    goto Decrement_counter_Axis_3;
                    Decrement_Close_Counter_Teaching:
                    printf(" (counter axis(3) =%i)\n", counter_axis[3]);
                    break;
                  
                  
                case 'O'://Open
                    goto Increment_counter_Axis_3;
                    Increment_Open_Counter_Teaching:
                    printf(" (counter axis(3) =%i)\n", counter_axis[3]);
                    break;
                  
                  
                case 'S'://Save
                Flag_last_saved = check_existance_positions(MAX_ROWS, MAX_COLUMNS, multiple_positions, counter_axis); //Returns a 1 if the position already exists
                if (Flag_last_saved == 0 && Counter_Used_Positions <MAX_ROWS)
                {
                    printf("The new saved positions are: [");
                    for (int axis=0; axis< Num_axes; axis++)
                    {
                        teaching_counter_axis[axis] = counter_axis[axis];
                        printf("%i", teaching_counter_axis[axis]);
                    }
                    printf("]\n");
                    printf("Press 'E' to Exit, 'P' to print all the saved positions so far, otherwise keep creating new positions.\n");
                    printf("Setting the axes to the initial position 0\n");
                    
                    Allocate_New_Position(MAX_COLUMNS, multiple_positions, Counter_Used_Positions, teaching_counter_axis);
                    Counter_Used_Positions += 1;
                }
                else{
                    printf("This position was already created or the memory is already full, please try again.\n");
                    printf("Setting the axes to the initial position 0\n");
                }
                
                Current_State = STATE_GO_TO_0_POS;
                break;
                
                case 'P'://Print
                Print_Array(MAX_ROWS, MAX_COLUMNS, multiple_positions);
                break;
                
                case 'R'://Reset
                //We need to set everything back to 0;
                Init_Zeros(MAX_ROWS, MAX_COLUMNS, multiple_positions);
                Counter_Used_Positions=0;
                printf("All the field elements were set to 0.\n");
                break;
                
                
                case 'E'://Exit from the teaching mode
                Current_State = STATE_GO_TO_WISH_POS;
                printf("Exit succesfull\n");
                break;
                
                case 'W'://Wiederholen (Repeat again without saving the coordinates)
                Current_State = STATE_GO_TO_0_POS;
                break;
                  
                 
                default:  printf("Invalid Input\n");
                  break;
              }
              
              if(ch=='E' || ch=='S' || ch=='W') //We want to break the while loop everytime we Exit,Save or Wiederholen, so we can place the axis at 0 position 
              {
                  break;
              }
                
                
            }
            
            Last_State = Current_State;
            break;
            
            case 2: //EXIT
            break;
            
            
            case 5: //STATE_GO_TO_WISH_POS
            
            if (Current_Row_Counter<Counter_Used_Positions) //We want to repeat as many times as the number of saved positions 
            {
                Num_axes = 4;
                for(int axis=0;axis<Num_axes; axis++)
                        {
                            while(1)
                            {
                                    if(counter_axis[axis] < multiple_positions[Current_Row_Counter][axis]) //position < desired pos
                                    {
                                        Current_State = CURRENT_LESS_DESIRED_POSITION;
                                    }
                                    else if(counter_axis[axis] > multiple_positions[Current_Row_Counter][axis]) //position > desired pos
                                    {
                                        Current_State = CURRENT_MORE_DESIRED_POSITION;
                                    }
                                    else //position = desired pos
                                    {
                                       Current_State = CURRENT_EQUAL_DESIRED_POSITION; 
                                       break;
                                    }
                                    
                                    switch(Current_State)
                                    {
                                    case 7://CURRENT_LESS_DESIRED_POSITION
                                        switch(axis)
                                        {
                                            case 0:
                                            goto Increment_counter_Axis_0;
                                            Check_Desired_Position_Axis_0:
                                            break;
                                            
                                            case 1:
                                            goto Increment_counter_Axis_1;
                                            Check_Desired_Position_Axis_1:
                                            break;
                                            
                                            case 2:
                                            goto Increment_counter_Axis_2;
                                            Check_Desired_Position_Axis_2:
                                            break;
                                            
                                            case 3:
                                            goto Increment_counter_Axis_3;
                                            Check_Desired_Position_Axis_3:
                                            break;
                                        }
                                        
                                    break;
                                    
                                    case 8://CURRENT_MORE_DESIRED_POSITION
                                        switch(axis)
                                        {
                                            case 0:
                                            goto Decrement_counter_Axis_0;
                                            Check_Desired_Decrement_Position_Axis_0:
                                            break;
                                            
                                            case 1:
                                            goto Decrement_counter_Axis_1;
                                            Check_Desired_Decrement_Position_Axis_1:
                                            break;
                                            
                                            case 2:
                                            goto Decrement_counter_Axis_2;
                                            Check_Desired_Decrement_Position_Axis_2:
                                            break;
                                            
                                            case 3:
                                            goto Decrement_counter_Axis_3;
                                            Check_Desired_Decrement_Position_Axis_3:
                                            break;
                                        }
                                    break;
                                    
                                }
                                
                            }
                        }
                    
                Current_Row_Counter += 1;    //Once we are done with the 4 axis we need to increment so we can go through the next 4 axis
                Last_State = Current_State;
                Current_State = STATE_GO_TO_0_POS;
                break;
            }   
            else
            {
                Current_State = EXIT;
                break;
            }
//------------------------------------------------------------------------------------------------------------------------ 
//GOTO LABELS START HERE:

            Increment_counter_Axis_0:
//                    while(1)
//                    {
//                        switch(CURRENT_RITZEL_STATE)
//                        {
//                            case 1://STATE_RITZEL_NOT_CHANGE
                                Move_Forward(Axis[0], is_knickarm);
//                                
//                                I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                                I1_bis_I8   = ~I1_bis_I8;
//                                if ((I1_bis_I8 & Ritzel_Achse[0])==Ritzel_Achse[0])
//                                {
//                                    CURRENT_RITZEL_STATE=STATE_RITZEL_CHANGE;
//                                }
//                                else{}
//                            break;
//                            
//                            case 2://STATE_RITZEL_CHANGE
//                            I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                            I1_bis_I8   = ~I1_bis_I8;
//                            if ((I1_bis_I8 & Ritzel_Achse[0])==0)
//                            {
//                                CURRENT_RITZEL_STATE=STATE_INCREASE_COUNTER;
//                            }
//                            else{}
//                            break;
//                            
//                            case 3://STATE_INCREASE_COUNTER
//                            Turn_off(Axis[0]);
//                            counter_axis[Axis[0]] += 1;
//                            CURRENT_RITZEL_STATE = EXIT_INCREASE;
//                            break;
//                            
//                            case 4://EXIT_INCREASE
//                            break;
//                        }
//                        if (CURRENT_RITZEL_STATE == EXIT_INCREASE)
//                          {
//                            CURRENT_RITZEL_STATE=STATE_RITZEL_NOT_CHANGE;
//                            break;
//                          }
//                    }
                
                Is_Increament = 1; //Here we specify if we just increment or decreament
                Setting_Max_Min_Counter(counter_axis, Axis[0], maximum[0], minimum[0], Is_Increament); //Here we define the max and min possible values for the counter
                if (Current_State == STATE_TEACHING_NEW_POSITIONS)
                {
                    goto Increment_Against_Counter_Teaching;
                }
                else
                {
                    goto Check_Desired_Position_Axis_0;
                }
                
            Increment_counter_Axis_1:
//                    while(1)
//                    {
//                        switch(CURRENT_RITZEL_STATE)
//                        {
//                            case 1://STATE_RITZEL_NOT_CHANGE
                                Move_Forward(Axis[1], is_knickarm);
//                                
//                                I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                                I1_bis_I8   = ~I1_bis_I8;
//                                if ((I1_bis_I8 & Ritzel_Achse[1])==Ritzel_Achse[1])
//                                {
//                                    CURRENT_RITZEL_STATE=STATE_RITZEL_CHANGE;
//                                }
//                                else{}
//                            break;
//                            
//                            case 2://STATE_RITZEL_CHANGE
//                            I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                            I1_bis_I8   = ~I1_bis_I8;
//                            if ((I1_bis_I8 & Ritzel_Achse[1])==0)
//                            {
//                                CURRENT_RITZEL_STATE=STATE_INCREASE_COUNTER;
//                            }
//                            else{}
//                            break;
//                            
//                            case 3://STATE_INCREASE_COUNTER
//                            Turn_off(Axis[1]);
//                            counter_axis[Axis[1]] += 1;
//                            CURRENT_RITZEL_STATE = EXIT_INCREASE;
//                            break;
//                            
//                            case 4://EXIT_INCREASE
//                            break;
//                        }
//                        if (CURRENT_RITZEL_STATE == EXIT_INCREASE)
//                          {
//                            CURRENT_RITZEL_STATE=STATE_RITZEL_NOT_CHANGE;
//                            break;
//                          }
//                    }
                Is_Increament = 1; //Here we specify if we just increment or decreament
                Setting_Max_Min_Counter(counter_axis, Axis[1], maximum[1], minimum[1], Is_Increament); //Here we define the max and min possible values for the counter
                if (Current_State == STATE_TEACHING_NEW_POSITIONS)
                {
                    goto Increment_Forward_Counter_Teaching;
                }
                else
                {
                    goto Check_Desired_Position_Axis_1;
                }
                
            Increment_counter_Axis_2:  
//                    while(1)
//                    {
//                        switch(CURRENT_RITZEL_STATE)
//                        {
//                            case 1://STATE_RITZEL_NOT_CHANGE
                                Move_Forward(Axis[2], is_knickarm);
//                                
//                                I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                                I1_bis_I8   = ~I1_bis_I8;
//                                if ((I1_bis_I8 & Ritzel_Achse[2])==Ritzel_Achse[2])
//                                {
//                                    CURRENT_RITZEL_STATE=STATE_RITZEL_CHANGE;
//                                }
//                                else{}
//                            break;
//                            
//                            case 2://STATE_RITZEL_CHANGE
//                            I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                            I1_bis_I8   = ~I1_bis_I8;
//                            if ((I1_bis_I8 & Ritzel_Achse[2])==0)
//                            {
//                                CURRENT_RITZEL_STATE=STATE_INCREASE_COUNTER;
//                            }
//                            else{}
//                            break;
//                            
//                            case 3://STATE_INCREASE_COUNTER
//                            Turn_off(Axis[2]);
//                            counter_axis[Axis[2]] += 1;
//                            CURRENT_RITZEL_STATE = EXIT_INCREASE;
//                            break;
//                            
//                            case 4://EXIT_INCREASE
//                            break;
//                        }
//                        if (CURRENT_RITZEL_STATE == EXIT_INCREASE)
//                          {
//                            CURRENT_RITZEL_STATE=STATE_RITZEL_NOT_CHANGE;
//                            break;
//                          }
//                    }
                Is_Increament = 1;
                Setting_Max_Min_Counter(counter_axis, Axis[2], maximum[2], minimum[2], Is_Increament);
                 if (Current_State == STATE_TEACHING_NEW_POSITIONS)
                {
                    goto Increment_Down_Counter_Teaching;
                }
                else
                {
                    goto Check_Desired_Position_Axis_2;
                }   
                
            Increment_counter_Axis_3:
//                    while(1)
//                    {
//                        switch(CURRENT_RITZEL_STATE)
//                        {
//                            case 1://STATE_RITZEL_NOT_CHANGE
                                Move_Forward(Axis[3], is_knickarm);
//                                
//                                I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                                I1_bis_I8   = ~I1_bis_I8;
//                                if ((I1_bis_I8 & Ritzel_Achse[3])==Ritzel_Achse[3])
//                                {
//                                    CURRENT_RITZEL_STATE=STATE_RITZEL_CHANGE;
//                                }
//                                else{}
//                            break;
//                            
//                            case 2://STATE_RITZEL_CHANGE
//                            I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                            I1_bis_I8   = ~I1_bis_I8;
//                            if ((I1_bis_I8 & Ritzel_Achse[3])==0)
//                            {
//                                CURRENT_RITZEL_STATE=STATE_INCREASE_COUNTER;
//                            }
//                            else{}
//                            break;
//                            
//                            case 3://STATE_INCREASE_COUNTER
//                            Turn_off(Axis[3]);
//                            counter_axis[Axis[3]] += 1;
//                            CURRENT_RITZEL_STATE = EXIT_INCREASE;
//                            break;
//                            
//                            case 4://EXIT_INCREASE
//                            break;
//                        }
//                        if (CURRENT_RITZEL_STATE == EXIT_INCREASE)
//                          {
//                            CURRENT_RITZEL_STATE=STATE_RITZEL_NOT_CHANGE;
//                            break;
//                          }
//                    }
                Is_Increament = 1;
                Setting_Max_Min_Counter(counter_axis, Axis[3], maximum[3], minimum[3], Is_Increament);
                 if (Current_State == STATE_TEACHING_NEW_POSITIONS)
                {
                    goto Increment_Open_Counter_Teaching;
                }
                else
                {
                    goto Check_Desired_Position_Axis_3;
                }
//------------------------------------------------------------------------------------------------------------------------
            Decrement_counter_Axis_0:
//                    while(1)
//                    {
//                        switch(CURRENT_RITZEL_STATE)
//                        {
//                            case 1://STATE_RITZEL_NOT_CHANGE
                                Move_Back(Axis[0], is_knickarm);
//                                
//                                I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                                I1_bis_I8   = ~I1_bis_I8;
//                                if ((I1_bis_I8 & Ritzel_Achse[0])==Ritzel_Achse[0])
//                                {
//                                    CURRENT_RITZEL_STATE=STATE_RITZEL_CHANGE;
//                                }
//                                else{}
//                            break;
//                            
//                            case 2://STATE_RITZEL_CHANGE
//                            I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                            I1_bis_I8   = ~I1_bis_I8;
//                            if ((I1_bis_I8 & Ritzel_Achse[0])==0)
//                            {
//                                CURRENT_RITZEL_STATE=STATE_INCREASE_COUNTER;
//                            }
//                            else{}
//                            break;
//                            
//                            case 3://STATE_INCREASE_COUNTER
//                            Turn_off(Axis[0]);
//                            counter_axis[Axis[0]] -= 1;
//                            CURRENT_RITZEL_STATE = EXIT_INCREASE;
//                            break;
//                            
//                            case 4://EXIT_INCREASE
//                            break;
//                        }
//                        if (CURRENT_RITZEL_STATE == EXIT_INCREASE)
//                          {
//                            CURRENT_RITZEL_STATE=STATE_RITZEL_NOT_CHANGE;
//                            break;
//                          }
//                    }
                Is_Increament = 0;
                Setting_Max_Min_Counter(counter_axis, Axis[0], maximum[0], minimum[0], Is_Increament);
                if (Current_State == STATE_TEACHING_NEW_POSITIONS)
                {
                    goto Decrement_InClock_Counter_Teaching;
                }
                else
                {
                    goto Check_Desired_Decrement_Position_Axis_0;
                }
            
            Decrement_counter_Axis_1:
//                    while(1)
//                    {
//                        switch(CURRENT_RITZEL_STATE)
//                        {
//                            case 1://STATE_RITZEL_NOT_CHANGE
                                Move_Back(Axis[1], is_knickarm);
//                                
//                                I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                                I1_bis_I8   = ~I1_bis_I8;
//                                if ((I1_bis_I8 & Ritzel_Achse[1])==Ritzel_Achse[1])
//                                {
//                                    CURRENT_RITZEL_STATE=STATE_RITZEL_CHANGE;
//                                }
//                                else{}
//                            break;
//                            
//                            case 2://STATE_RITZEL_CHANGE
//                            I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                            I1_bis_I8   = ~I1_bis_I8;
//                            if ((I1_bis_I8 & Ritzel_Achse[1])==0)
//                            {
//                                CURRENT_RITZEL_STATE=STATE_INCREASE_COUNTER;
//                            }
//                            else{}
//                            break;
//                            
//                            case 3://STATE_INCREASE_COUNTER
//                            Turn_off(Axis[1]);
//                            counter_axis[Axis[1]] -= 1;
//                            CURRENT_RITZEL_STATE = EXIT_INCREASE;
//                            break;
//                            
//                            case 4://EXIT_INCREASE
//                            break;
//                        }
//                        if (CURRENT_RITZEL_STATE == EXIT_INCREASE)
//                          {
//                            CURRENT_RITZEL_STATE=STATE_RITZEL_NOT_CHANGE;
//                            break;
//                          }
//                    }
                Is_Increament = 0;
                Setting_Max_Min_Counter(counter_axis, Axis[1], maximum[1], minimum[1], Is_Increament);
                if (Current_State == STATE_TEACHING_NEW_POSITIONS)
                {
                    goto Decrement_Backwards_Counter_Teaching;
                }
                else
                {
                    goto Check_Desired_Decrement_Position_Axis_1;
                }
            
            Decrement_counter_Axis_2:
//                    while(1)
//                    {
//                        switch(CURRENT_RITZEL_STATE)
//                        {
//                            case 1://STATE_RITZEL_NOT_CHANGE
                                Move_Back(Axis[2], is_knickarm);
//                                
//                                I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                                I1_bis_I8   = ~I1_bis_I8;
//                                if ((I1_bis_I8 & Ritzel_Achse[2])==Ritzel_Achse[2])
//                                {
//                                    CURRENT_RITZEL_STATE=STATE_RITZEL_CHANGE;
//                                }
//                                else{}
//                            break;
//                            
//                            case 2://STATE_RITZEL_CHANGE
//                            I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                            I1_bis_I8   = ~I1_bis_I8;
//                            if ((I1_bis_I8 & Ritzel_Achse[2])==0)
//                            {
//                                CURRENT_RITZEL_STATE=STATE_INCREASE_COUNTER;
//                            }
//                            else{}
//                            break;
//                            
//                            case 3://STATE_INCREASE_COUNTER
//                            Turn_off(Axis[2]);
//                            counter_axis[Axis[2]] -= 1;
//                            CURRENT_RITZEL_STATE = EXIT_INCREASE;
//                            break;
//                            
//                            case 4://EXIT_INCREASE
//                            break;
//                        }
//                        if (CURRENT_RITZEL_STATE == EXIT_INCREASE)
//                          {
//                            CURRENT_RITZEL_STATE=STATE_RITZEL_NOT_CHANGE;
//                            break;
//                          }
//                    }
                Is_Increament = 0;
                Setting_Max_Min_Counter(counter_axis, Axis[2], maximum[2], minimum[2], Is_Increament);
                if (Current_State == STATE_TEACHING_NEW_POSITIONS)
                {
                    goto Decrement_Up_Counter_Teaching;
                }
                else
                {
                    goto Check_Desired_Decrement_Position_Axis_2;
                }
                
            Decrement_counter_Axis_3:
//                    while(1)
//                    {
//                        switch(CURRENT_RITZEL_STATE)
//                        {
//                            case 1://STATE_RITZEL_NOT_CHANGE
                                Move_Back(Axis[3], is_knickarm);
//                                
//                                I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                                I1_bis_I8   = ~I1_bis_I8;
//                                if ((I1_bis_I8 & Ritzel_Achse[3])==Ritzel_Achse[3])
//                                {
//                                    CURRENT_RITZEL_STATE=STATE_RITZEL_CHANGE;
//                                }
//                                else{}
//                            break;
//                            
//                            case 2://STATE_RITZEL_CHANGE
//                            I1_bis_I8   = iic_lese_pcf8574 (adrlese);
//                            I1_bis_I8   = ~I1_bis_I8;
//                            if ((I1_bis_I8 & Ritzel_Achse[3])==0)
//                            {
//                                CURRENT_RITZEL_STATE=STATE_INCREASE_COUNTER;
//                            }
//                            else{}
//                            break;
//                            
//                            case 3://STATE_INCREASE_COUNTER
//                            Turn_off(Axis[3]);
//                            counter_axis[Axis[3]] -= 1;
//                            CURRENT_RITZEL_STATE = EXIT_INCREASE;
//                            break;
//                            
//                            case 4://EXIT_INCREASE
//                            break;
//                        }
//                        if (CURRENT_RITZEL_STATE == EXIT_INCREASE)
//                          {
//                            CURRENT_RITZEL_STATE=STATE_RITZEL_NOT_CHANGE;
//                            break;
//                          }
//                    }
                Is_Increament = 0;
                Setting_Max_Min_Counter(counter_axis, Axis[3], maximum[3], minimum[3], Is_Increament);
                if (Current_State == STATE_TEACHING_NEW_POSITIONS)
                {
                    goto Decrement_Close_Counter_Teaching;
                }
                else
                {
                    goto Check_Desired_Decrement_Position_Axis_3;
                }
            
        }
        if (Current_State==EXIT)
        {
        break;
        }
    }
 return 0;   
}
