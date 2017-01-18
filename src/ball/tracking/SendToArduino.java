package ball.tracking;

import java.io.*;
import java.util.*;
import gnu.io.*;

public class SendToArduino {
static Enumeration portList;
static CommPortIdentifier portId;
static String messageString = "-10";
static SerialPort serialPort;
static OutputStream outputStream;

public static void setServo(String message) {
	portList = CommPortIdentifier.getPortIdentifiers();
	
    while (portList.hasMoreElements()) {

        portId = (CommPortIdentifier) portList.nextElement();
        if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {

             if (portId.getName().equals("COM3")) {

                try {
                    serialPort = (SerialPort)portId.open("SimpleWriteApp", 2000);
                } catch (PortInUseException e) {System.out.println("err");}
                try {
                    outputStream = serialPort.getOutputStream();
                } catch (IOException e) {System.out.println("err1");}
                try {
                    serialPort.setSerialPortParams(9600,
                        SerialPort.DATABITS_8,
                        SerialPort.STOPBITS_1,
                        SerialPort.PARITY_NONE);
                } catch (UnsupportedCommOperationException e) {System.out.println("err2");}
                try {
                	System.out.println(message);
                	outputStream.write(message.getBytes());
					
					outputStream.close();
					serialPort.close();

                } catch (IOException e) {System.out.println("err3");}
            }
        }
    }
}
}