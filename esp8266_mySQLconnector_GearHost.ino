#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

char hostname[] = "den1.mysql6.gear.host";
char user[] = "yourdbnameongearhost"; // MySQL user login username
char password[] = "password"; // MySQL user login password

// WiFi card example
char ssid[] = "phloenlom_2.4GHz"; // your SSID
char pass[] = "248248248"; // your SSID Password

// Sample query
char INSERT_SQL[] = "INSERT INTO `mysmazcontrol`.`test` (`id`, `name`, `price`) VALUES ('2', 'two', '1000');";

IPAddress server_ip;
WiFiClient client;
MySQL_Connection conn((Client *)&client);

void setup() {
Serial.begin(115200);
// Begin WiFi section
WiFi.begin(ssid, pass);
// Wait for connection
while ( WiFi.status() != WL_CONNECTED ) {
  delay ( 500 );
  Serial.print ( "." );
}
Serial.println ( "" );
Serial.print ( "Connected to " );
Serial.println ( ssid );
Serial.print ( "IP address: " );
Serial.println ( WiFi.localIP() );
// End WiFi section
WiFi.hostByName(hostname,server_ip);
Serial.print( "SQL host IP: ");
Serial.println(server_ip);
// End DNS lookup
Serial.println("DB - Connecting...");
// 3306
while (conn.connect(server_ip, 3306, user, password) != true) {
  delay(500);
  Serial.print ( "." );
}
// Initiate the query class instance
MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
// Execute the query
cur_mem->execute(INSERT_SQL);
// Note: since there are no results, we do not need to read any data
// Deleting the cursor also frees up memory used
delete cur_mem;
Serial.println("Added");
}

void loop() {
}
