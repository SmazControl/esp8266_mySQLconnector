#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
//192,168,43,125
IPAddress server_addr(192,168,43,125); // IP of the MySQL server here
char user[] = "esp"; // MySQL user login username
char password[] = "palace66"; // MySQL user login password

// WiFi card example
char ssid[] = "vivo 1723"; // your SSID
char pass[] = "palace66"; // your SSID Password

// Sample query
char SQL[] = "SELECT * FROM sys.host_summary;";

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
Serial.println("DB - Connecting...");
while (conn.connect(server_addr, 3306, user, password) != true) {
delay(500);
Serial.print ( "." );
}
Serial.println("Ready");
}

void loop() {
delay(2000);

Serial.println("Read data.");

// Initiate the query class instance
MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
// Execute the query
cur_mem->execute(SQL);
// Note: since there are no results, we do not need to read any data
// Deleting the cursor also frees up memory used
// Fetch the columns and print them
  column_names *cols = cur_mem->get_columns();
  for (int f = 0; f < cols->num_fields; f++) {
    Serial.print(cols->fields[f]->name);
    if (f < cols->num_fields-1) {
      Serial.print(", ");
    }
  }
  Serial.println();
  // Read the rows and print them
  row_values *row = NULL;
  do {
    row = cur_mem->get_next_row();
    if (row != NULL) {
      for (int f = 0; f < cols->num_fields; f++) {
        Serial.print(row->values[f]);
        if (f < cols->num_fields-1) {
          Serial.print(", ");
        }
      }
      Serial.println();
    }
  } while (row != NULL);
  // Deleting the cursor also frees up memory used
delete cur_mem;
}
