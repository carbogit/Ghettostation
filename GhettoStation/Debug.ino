#if defined(DEBUG)
void debug() {
    if (debugMetro.check() == 1)  {
       Serial.print("lat=");
       Serial.println(uav_lat,7);
       Serial.print("lon=");
       Serial.println(uav_lon,7);
       Serial.print("alt=");
       Serial.print(uav_alt);
       Serial.println("");
       Serial.print("dst=");
       Serial.println(home_dist);
       Serial.print("El:");
       Serial.println(Elevation);
       Serial.print("Be:");
       Serial.println(Bearing);
       Serial.print("Be:");
       Serial.println(home_bearing);
    }
  
}
#endif
