/*
 * WiFlyHQ Example udpclient.ino
 *
 * This sketch implements a simple UDP client that sends a UDP packet
 * to a UDP server every second.
 *
 * This sketch is released to the public domain.
 *
 */


#include <WiFlyHQ.h>

/* Change these to match your WiFi network */
const char mySSID[] = "genieBox";
const char myPassword[] = "iamhungry";

WiFly wifly;

int analogData;

void setup()
{
    char buf[32];

    Serial.begin(9600);
//    Serial.println("Starting");
//    Serial.print("Free memory: ");
//    Serial.println(wifly.getFreeMemory(),DEC);

    Serial1.begin(9600);

    if (!wifly.begin(&Serial1,&Serial)) {
        Serial.println("Failed to start wifly");
	//terminal();
    }
    
    if (wifly.getFlushTimeout() != 10) {
        //Serial.println("Restoring flush timeout to 10msecs");
        wifly.setFlushTimeout(10);
	wifly.save();
	wifly.reboot();
    }

    /* Join wifi network if not already associated */
    if (!wifly.isAssociated()) {
	/* Setup the WiFly to connect to a wifi network */
	Serial.println("Joining network");
	wifly.setSSID(mySSID);
	wifly.setPassphrase(myPassword);
	wifly.enableDHCP();

	if (wifly.join()) {
	    Serial.println("Joined wifi network");
	} else {
	    Serial.println("Failed to join wifi network");
	    //terminal();
	}
    } else {
        Serial.println("Already joined network");
    }
     Serial.print("MAC: ");
    Serial.println(wifly.getMAC(buf, sizeof(buf)));
    Serial.print("IP: ");
    Serial.println(wifly.getIP(buf, sizeof(buf)));
    Serial.print("Netmask: ");
    Serial.println(wifly.getNetmask(buf, sizeof(buf)));
    Serial.print("Gateway: ");
    Serial.println(wifly.getGateway(buf, sizeof(buf)));

//    wifly.setDeviceID("Wifly-WebClient");
//    Serial.print("DeviceID: ");
//    Serial.println(wifly.getDeviceID(buf, sizeof(buf)));

    /* Setup for UDP packets, sent automatically */
    wifly.setIpProtocol(WIFLY_PROTOCOL_UDP);
    wifly.setHost("192.168.1.206", 11998);	// Send UDP packet to this server and port



    wifly.setDeviceID("Wifly-UDP");

    wifly.setHost("192.168.1.206", 11998);	// Send UPD packets to this server and port

    Serial.println("WiFly ready");
}

uint32_t lastSend = 0;
uint32_t count=0;

void loop()
{
    
    analogData = analogRead(A5);
//    Serial.println(analogData);
   wifly.print(analogData);
   wifly.print("[/p]");
    delay(50);                // found i need a short delay before second TX

}

