#include "main.h"
#include "Display_tft.h"

//Callback function for three buttons
// void btnCallback(DFRobot_UI::sButton_t &btn,DFRobot_UI::sTextBox_t &obj)
// {
//   String text((char *)btn.text);
//   if(text == "ON")
//   {
//     obj.setText("you have touched button on");
//   }
//   else if(text == "OFF")
//   {
//     obj.setText("you have touched button off");
//   }
//   else if(text == "clr")
//   {
//     obj.deleteChar();
//   }
    
// }

void tbCallback(void * highLightPage)
{
  uint8_t * hl = (uint8_t *)highLightPage;
  switch (*hl) {
     case 1:{
    //Display a string on the screen
       ui.drawString(10, 200, "this is tab1", COLOR_RGB565_YELLOW, ui.bgColor, 3, 0);break;
       }
    case 2: {
       ui.drawString(10, 200, "this is tab2", COLOR_RGB565_YELLOW, ui.bgColor, 3, 0);break;
       }
    case 3:  {
       ui.drawString(10, 200, "this is tab3", COLOR_RGB565_YELLOW, ui.bgColor, 3, 0);break;
      }
    case 4:  {
       ui.drawString(10, 200, "this is tab4", COLOR_RGB565_YELLOW, ui.bgColor, 3, 0);break;
  }
  }
}

void display_tft_init(void)
{
  //UI initialization
  // ui.begin();
  // //Set the UI theme, there are two themes to choose from: CLASSIC and MODERN.
  // ui.setTheme(DFRobot_UI::MODERN); 
  // touch.setRotation(1);
  // screen.setRotation(1);
  //Create a text box control
  // DFRobot_UI::sTextBox_t & tb = ui.creatText();  // tb.bgColor = 0xe6B6;
  // ui.draw(&tb);
  // //Create a button control on the screen
  // DFRobot_UI::sButton_t & btn1 = ui.creatButton();
  // //Set the name of the button
  // btn1.setText("ON");
  // btn1.bgColor = COLOR_RGB565_RED;
  // btn1.setCallback(btnCallback);
  // //Each button has a text box, its parameter needs to be set by yourself.
  // btn1.setOutput(&tb);
  // ui.draw(&btn1,/**x=*/screen.width()/10,/**y=*/screen.height()/2,/*width*/screen.width()/10*2,/*height*/screen.width()/10*2);
  
  // DFRobot_UI::sButton_t & btn2 = ui.creatButton();
  // btn2.setText("OFF");
  // btn2.bgColor = COLOR_RGB565_GREEN;
  // btn2.setCallback(btnCallback);
  // //Each button has a text box, its parameter needs to be set by yourself.
  // btn2.setOutput(&tb);
  // ui.draw(&btn2,/**x=*/(screen.width()/10)*4,/**y=*/screen.height()/2,/*width*/screen.width()/10*2,/*height*/screen.width()/10*2);
 
  // DFRobot_UI::sButton_t & btn3 = ui.creatButton();
  // btn3.bgColor = COLOR_RGB565_BLUE;
  // btn3.setText("clr");

  // //Set the callback function of the button
  // btn3.setCallback(btnCallback);
  // //Each button has a text box, its parameter needs to be set by yourself.
  
  // btn3.setOutput(&tb);
  // ui.draw(&btn3,/**x=*/(screen.width()/10)*7,/**y=*/screen.height()/2,/*width*/screen.width()/10*2,/*height*/screen.width()/10*2);

  // screen.fillScreen(COLOR_RGB565_BLACK);
  
  // // Set text color and size
  // screen.setTextColor(COLOR_RGB565_WHITE);
  // screen.setTextSize(2);
  
  // // Draw labels
  // screen.setCursor(10, 10);
  // screen.print("Temp:");
  // screen.setCursor(10, 40);
  // screen.print("Humi:");
  // screen.setCursor(10, 70);
  // screen.print("Volt:");
  // screen.setCursor(10, 100);
  // screen.print("Curr:");
  // screen.setCursor(10, 130);
  // screen.print("Power:");

  ui.begin();
  ui.setTheme(DFRobot_UI::MODERN);
  touch.setRotation(1);
  screen.setRotation(1);


 //Create a tableview control
 DFRobot_UI::sTableview_t &tb = ui.creatTableview();
  //Set the number and name of tableview, at most 4 pages.
 tb.setName(/*page=*/4,/*page1 name=*/"tab1",/*page2 name=*/"tab2",/*page3 name=*/"tab3",/*page4 name=*/"tab4");
  //Set callback function
 tb.setCallback(tbCallback);
 ui.draw(&tb);
}

void display_tft_loop(void)
{
  ui.refresh();
}

void display_Value(int x, int y, float value)
{
  // Clear the previous value
  screen.fillRect(x, y, 60, 20, COLOR_RGB565_BLACK);
  
  // Set cursor and print new value
  screen.setCursor(x, y);
  screen.print(value, 1); // Print value with one decimal place
}
