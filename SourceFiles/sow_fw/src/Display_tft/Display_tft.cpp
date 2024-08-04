#include "main.h"
#include "Display_tft.h"

//Callback function for three buttons
void btnCallback(DFRobot_UI::sButton_t &btn,DFRobot_UI::sTextBox_t &obj)
{
  String text((char *)btn.text);
  if(text == "ON")
  {
    obj.setText("you have touched button on");
  }
  else if(text == "OFF")
  {
    obj.setText("you have touched button off");
  }
  else if(text == "clr")
  {
    obj.deleteChar();
  }
    
}

void display_tft_init(void)
{
  DEBUG_NL("\n\n\n[display_tft_init]\n\n");
  //UI initialization
  ui.begin();
  //Set the UI theme, there are two themes to choose from: CLASSIC and MODERN.
  ui.setTheme(DFRobot_UI::MODERN); 
  //Create a text box control
  DFRobot_UI::sTextBox_t & tb = ui.creatText();
  tb.bgColor = 0xe6B6;
  ui.draw(&tb);
  //Create a button control on the screen
  DFRobot_UI::sButton_t & btn1 = ui.creatButton();
  //Set the name of the button
  btn1.setText("ON");
  btn1.bgColor = COLOR_RGB565_RED;
  btn1.setCallback(btnCallback);
  //Each button has a text box, its parameter needs to be set by yourself.
  btn1.setOutput(&tb);
  ui.draw(&btn1,/**x=*/screen.width()/10,/**y=*/screen.height()/2,/*width*/screen.width()/10*2,/*height*/screen.width()/10*2);
  
  DFRobot_UI::sButton_t & btn2 = ui.creatButton();
  btn2.setText("OFF");
  btn2.bgColor = COLOR_RGB565_GREEN;
  btn2.setCallback(btnCallback);
  //Each button has a text box, its parameter needs to be set by yourself.
  btn2.setOutput(&tb);
  ui.draw(&btn2,/**x=*/(screen.width()/10)*4,/**y=*/screen.height()/2,/*width*/screen.width()/10*2,/*height*/screen.width()/10*2);
 
  DFRobot_UI::sButton_t & btn3 = ui.creatButton();
  btn3.bgColor = COLOR_RGB565_BLUE;
  btn3.setText("clr");

  //Set the callback function of the button
  btn3.setCallback(btnCallback);
  //Each button has a text box, its parameter needs to be set by yourself.
  
  btn3.setOutput(&tb);
  ui.draw(&btn3,/**x=*/(screen.width()/10)*7,/**y=*/screen.height()/2,/*width*/screen.width()/10*2,/*height*/screen.width()/10*2);
}

void display_tft_loop(void)
{
  ui.refresh();
}
