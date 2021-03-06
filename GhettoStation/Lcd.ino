//LCD 

void init_lcdscreen() {
#ifdef DEBUG
    Serial.println("starting lcd"); 
#endif

  char extract[20];
// init LCD
	LCD.begin(20,4);
        delay(20);
        LCD.backlight(); 		
 	delay(250); 		
 	LCD.noBacklight(); 		
 	delay(250);
        LCD.backlight(); 
        delay(250);
        LCD.setCursor(0,0);
	LCD.print(string_load1.copy(extract));
        LCD.setCursor(0,1);
        LCD.print(string_load2.copy(extract));
        LCD.setCursor(0,2);
	LCD.print(string_load3.copy(extract));
        LCD.setCursor(0,3);
	LCD.print(string_load4.copy(extract));
	delay(1500); //delay to init lcd in time.
}

void store_lcdline( int i, char sbuffer[20] ) {
	
	switch (i) {
		case 1: 
				strcpy(lcd_line1,sbuffer);
				break;
		case 2: 
				strcpy(lcd_line2,sbuffer);
				break;
		case 3: 
				strcpy(lcd_line3,sbuffer);
				break;
		case 4: 
				strcpy(lcd_line4,sbuffer);
				break;
                default: 
                                break;
           
	}

}

void refresh_lcd() {
   // refreshing lcd at defined update.
    if (lcdMetro.check() == 1) {
        // update lines
        //LCD.clear();
        LCD.setCursor(0,0);
	LCD.print(lcd_line1);
        LCD.setCursor(0,1);
	LCD.print(lcd_line2);
        LCD.setCursor(0,2);
	LCD.print(lcd_line3);
        LCD.setCursor(0,3);
    	LCD.print(lcd_line4);
    }
}

// SET_HOME SCREEN
void lcddisp_sethome() {
   for ( int i = 1 ; i<5; i++ ) {
     char extract[21];
     char string_buffer[21];
     String currentline;
     switch (i) {
           case 1:
                //line1
                if (!telemetry_ok) { currentline = "L:NO"; }
                else if (telemetry_ok) { currentline = "L:" + protocol;}
                //currentline = "L:" + c;
                currentline += " SATS:";
                currentline += String(uav_satellites_visible);
                currentline += " FIX:";
                currentline += String(uav_fix_type);
                break;
            case 2:
                 //line 2
                 if (!telemetry_ok) currentline = String(string_shome1.copy(extract)); // waiting for data
                 else {
                   if (!gps_fix) currentline = String(string_shome2.copy(extract));  // waiting for gps fix
                   else {
                         currentline = String(string_shome3.copy(extract)); // fix ok save home
                         currentline += String(round((uav_alt)/10));
                         currentline += "m";      
                   }
                 }
                 break;
      
             case 3:
                    if (!gps_fix) currentline = String(string_shome4.copy(extract));
                    else {
                         char bufferl[10];
                         char bufferL[10];
                         currentline = String(dtostrf(uav_lat, 5, 5, bufferl));
                         currentline += " ";
                         currentline += String(dtostrf(uav_lon, 5, 5, bufferL));
                    }
                    break;
      
             case 4:
                   if (!gps_fix) currentline = String(string_shome5.copy(extract));
                   else currentline = String(string_shome6.copy(extract));
                   break;
              }
     
    for ( int l = currentline.length() ; l<21 ; l++ ) {
	 currentline += " ";
	 }
    currentline.toCharArray(string_buffer,21);
    store_lcdline(i,string_buffer);
   } 
}

#ifdef BEARING_METHOD_1
void lcddisp_setbearing() {
    for ( int i = 1 ; i<5; i++ ) {
       char string_buffer[21];
       char extract[21];
       String currentline="";
       switch (i) {
           case 1: 
                        if (!telemetry_ok) { currentline = "L:NO"; }
                else if (telemetry_ok) { currentline = "L:" + protocol;}
                        currentline += " SATS:";
                        currentline += String(uav_satellites_visible);
                        currentline += " FIX:";
                        currentline += String(uav_fix_type);
                        break;
           case 2:
                        currentline = String(string_load2.copy(extract));  break;
           case 3:
                        currentline = String(string_shome8.copy(extract)); break;
           case 4:      
                        currentline = String(string_shome9.copy(extract)); break;

       }
       for ( int l = currentline.length()-1 ; l<21 ; l++ ) {
	 currentline = currentline + " ";
	 }
       currentline.toCharArray(string_buffer,21);
       store_lcdline(i,string_buffer);
    }
}
#endif
#ifdef BEARING_METHOD_2
void lcddisp_setbearing() {
    for ( int i = 1 ; i<5; i++ ) {
       char string_buffer[21];
       char extract[21];
       String currentline="";
       switch (i) {
           case 1: 
                        if (!telemetry_ok) { currentline = "L:NO"; }
                else if (telemetry_ok) { currentline = "L:" + protocol;}
                        currentline += " SATS:";
                        currentline += String(uav_satellites_visible);
                        currentline += " FIX:";
                        currentline += String(uav_fix_type);
                        break;
           case 2:
                        currentline = String(string_shome7.copy(extract));  break;
           case 3:
                        currentline = String(home_bearing); break;
           case 4:      
                        currentline = String(string_load2.copy(extract)); break;

       }
       for ( int l = currentline.length()-1 ; l<21 ; l++ ) {
	 currentline = currentline + " ";
	 }
       currentline.toCharArray(string_buffer,21);
       store_lcdline(i,string_buffer);
       
       //checking long press left right
       if (right_button.holdTime() >= 1000 && right_button.isPressed() ) {
        home_bearing+=25;
        delay(100);
        }
        else if ( left_button.holdTime() >= 1000 && left_button.isPressed() ) {
        home_bearing-=25;
        delay(100);
        }
        if (home_bearing>359) home_bearing = 0;
        else if (home_bearing<0) home_bearing = 359;
 }
}
#endif

#ifdef BEARING_METHOD_4
void lcddisp_setbearing() {
    retrieve_mag();
    for ( int i = 1 ; i<5; i++ ) {
       char string_buffer[21];
       char extract[21];
       String currentline="";
       switch (i) {
           case 1: 
                        if (!telemetry_ok) { currentline = "L:NO"; }
                else if (telemetry_ok) { currentline = "L:" + protocol;}
                        currentline += " SATS:";
                        currentline += String(uav_satellites_visible);
                        currentline += " FIX:";
                        currentline += String(uav_fix_type);
                        break;
           case 2:
                        currentline = String(string_shome7.copy(extract));  break;
           case 3:
                        currentline = String(home_bearing); break;
           case 4:      
                        currentline = String(string_load2.copy(extract)); break;

       }
       for ( int l = currentline.length()-1 ; l<21 ; l++ ) {
	 currentline = currentline + " ";
	 }
       currentline.toCharArray(string_buffer,21);
       store_lcdline(i,string_buffer);
       
       //checking long press left right
       if (right_button.holdTime() >= 1000 && right_button.isPressed() ) {
        home_bearing++;
        if (home_bearing>360) home_bearing = 360;
        else if (home_bearing<0) home_bearing = 0;
        delay(100);
        }
        else if ( left_button.holdTime() >= 1000 && left_button.isPressed() ) {
        home_bearing--;
        delay(100);
        }
 }
}
#endif

void lcddisp_homeok() {
    for ( int i = 1 ; i<5; i++ ) {
       char string_buffer[21];
       char extract[21];
       String currentline="";
       switch (i) {
           case 1: 
                        if (!telemetry_ok) { currentline = "L:NO"; }
                        else if (telemetry_ok) { currentline = "L:" + protocol;}
                        currentline += "SATS:";
                        currentline += String(uav_satellites_visible);
                        currentline += " FIX:";
                        currentline += String(uav_fix_type);
                        break;
           case 2:
                        currentline = String(string_shome10.copy(extract)); break;
           case 3:
                        currentline = String(string_shome11.copy(extract)); break;

           case 4:      currentline = String(string_shome12.copy(extract)); break;
       
           }
       for ( int l = currentline.length()-1 ; l<21 ; l++ ) {
         currentline = currentline + " ";
         }
       currentline.toCharArray(string_buffer,21);
       store_lcdline(i,string_buffer);
       }
}

void lcddisp_tracking(){
    for ( int i = 1 ; i<5; i++ ) {
       char string_buffer[21];
       String currentline="";
       switch (i) {
           case 1: 
                        if (!telemetry_ok) { currentline = "L:NO"; }
                        else if (telemetry_ok) { currentline = "L:" + protocol;}
                        currentline += " SATS:";
                        currentline += String(uav_satellites_visible);
                        currentline += " FIX:";
                        currentline += String(uav_fix_type);
                        break;
           case 2:
                        currentline = "Alt:"; 
                        int calt;
                        calt = round((uav_alt - home_alt)/10);
                        currentline += String(calt);
                        currentline += "m Spd:";
                        currentline += String((int) uav_groundspeed);
                        currentline += "kmh";
                        break;
           case 3:
                        char buffer[7];
                        currentline = "Dist:";
                        currentline += String(home_dist);
                        currentline += "m";
                        break;
           case 4:      
                        char bufferl[10];
                        char bufferL[10];
                        currentline = String(dtostrf(uav_lat, 5, 6, bufferl));
                        currentline += " ";
                        currentline += String(dtostrf(uav_lon, 5, 6, bufferL));
                        break;

       }
       for ( int l = currentline.length()-1 ; l<21 ; l++ ) {
	 currentline = currentline + " ";
	 }
       currentline.toCharArray(string_buffer,21);
       store_lcdline(i,string_buffer);
    }
}

void lcddisp_telemetry() {
    for ( int i = 1 ; i<5; i++ ) {
       char string_buffer[21];
       char extract[21];
       String currentline="";
       switch (i) {
           case 1: 
                     currentline = String(string_telemetry1.copy(extract));  break;
           case 2:
                     currentline = String(string_load2.copy(extract)); break;
           case 3:
                     switch (configuration.telemetry) {
                       
                        case 0:
                                 // currentline = "UAVTalk"; break;
                                currentline = String(string_telemetry2.copy(extract)); break;
                        case 1:
                                 //currentline = "MSP"; break;
                                currentline = String(string_telemetry3.copy(extract)); break;
                        case 2:
                                //currentline = "AudioModem"; break;
                                currentline = String(string_telemetry4.copy(extract)); break;
                        case 3:
                                //currentline = "MavLink"; break;
                                currentline = String(string_telemetry5.copy(extract)); break;   
                     }
                     break;
       
           case 4:      
                     currentline = String(string_shome5.copy(extract)); break;

       }
       for ( int l = currentline.length()-1 ; l<21 ; l++ ) {
	 currentline = currentline + " ";
       }
       currentline.toCharArray(string_buffer,21);
       store_lcdline(i,string_buffer);
    }
  
}
void lcddisp_baudrate() {
    for ( int i = 1 ; i<5; i++ ) {
       char string_buffer[21];
       char extract[21];
       String currentline="";
       switch (i) {
           case 1: 
                     currentline = String(string_baudrate.copy(extract));  break;
           case 2:
                     currentline = String(string_load2.copy(extract)); break;
           case 3:
                     switch (configuration.baudrate) {
                       
                        case 0:
                                 // 1200
                                currentline = String(string_baudrate0.copy(extract));  break;
                        case 1:
                                 //2400
                                currentline = String(string_baudrate1.copy(extract));  break;
                        case 2:
                                 //4800
                                currentline = String(string_baudrate2.copy(extract)); break;
                        case 3:
                                 //9600
                                currentline = String(string_baudrate3.copy(extract));  break;
                        case 4:
                                 //19200
                                currentline = String(string_baudrate4.copy(extract));  break;
                        case 5:
                                 //38400
                                currentline = String(string_baudrate5.copy(extract));  break;
                        case 6:
                                 //57600
                                currentline = String(string_baudrate6.copy(extract));  break;
                        case 7:
                                 //115200
                                currentline = String(string_baudrate7.copy(extract));  break;                            
                                              
                     }
                     break;
       
           case 4:      
                     currentline = String(string_shome5.copy(extract)); break;
           }
       for ( int l = currentline.length()-1 ; l<21 ; l++ ) {
	 currentline = currentline + " ";
	 }
       currentline.toCharArray(string_buffer,21);
       store_lcdline(i,string_buffer);
    }
}
