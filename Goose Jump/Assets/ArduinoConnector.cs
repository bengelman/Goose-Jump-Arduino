/* ArduinoConnector by Alan Zucconi
 * http://www.alanzucconi.com/?p=2979
 */

using UnityEngine;
using System;
using System.Collections;
using System.IO.Ports;


public class ArduinoConnector : MonoBehaviour {
    public float rotation;
    static int NOTE_B0 = 31;
static int NOTE_C1 = 33;
static int NOTE_CS1 = 35;
    static int NOTE_D1 = 37;
    static int NOTE_DS1 = 39;
    static int NOTE_E1 = 41;
    static int NOTE_F1 = 44;
    static int NOTE_FS1 = 46;
    static int NOTE_G1 = 49;
    static int NOTE_GS1 = 52;
    static int NOTE_A1 = 55;
    static int NOTE_AS1 = 58;
    static int NOTE_B1 = 62;
    static int NOTE_C2 = 65;
    static int NOTE_CS2 = 69;
    static int NOTE_D2 = 73;
    static int NOTE_DS2 = 78;
    static int NOTE_E2 = 82;
    static int NOTE_F2 = 87;
    static int NOTE_FS2 = 93;
    static int NOTE_G2 = 98;
    static int NOTE_GS2 = 104;
    static int NOTE_A2 = 110;
    static int NOTE_AS2 = 117;
    static int NOTE_B2 = 123;
    static int NOTE_C3 = 131;
    static int NOTE_CS3 = 139;
    static int NOTE_D3 = 147;
    static int NOTE_DS3 = 156;
    static int NOTE_E3 = 165;
    static int NOTE_F3 = 175;
    static int NOTE_FS3 = 185;
    static int NOTE_G3 = 196;
    static int NOTE_GS3 = 208;
    static int NOTE_A3 = 220;
    static int NOTE_AS3 = 233;
    static int NOTE_B3 = 247;
    static int NOTE_C4 = 262;
    static int NOTE_CS4 = 277;
    static int NOTE_D4 = 294;
    static int NOTE_DS4 = 311;
    static int NOTE_E4 = 330;
    static int NOTE_F4 = 349;
    static int NOTE_FS4 = 370;
    static int NOTE_G4 = 392;
    static int NOTE_GS4 = 415;
    static int NOTE_A4 = 440;
    static int NOTE_AS4 = 466;
    static int NOTE_B4 = 494;
    static int NOTE_C5 = 523;
    static int NOTE_CS5 = 554;
    static int NOTE_D5 = 587;
    static int NOTE_DS5 = 622;
    static int NOTE_E5 = 659;
    static int NOTE_F5 = 698;
    static int NOTE_FS5 = 740;
    static int NOTE_G5 = 784;
    static int NOTE_GS5 = 831;
    static int NOTE_A5 = 880;
    static int NOTE_AS5 = 932;
    static int NOTE_B5 = 988;
    static int NOTE_C6 = 1047;
    static int NOTE_CS6 = 1109;
    static int NOTE_D6 = 1175;
    static int NOTE_DS6 = 1245;
    static int NOTE_E6 = 1319;
    static int NOTE_F6 = 1397;
    static int NOTE_FS6 = 1480;
    static int NOTE_G6 = 1568;
    static int NOTE_GS6 = 1661;
    static int NOTE_A6 = 1760;
    static int NOTE_AS6 = 1865;
    static int NOTE_B6 = 1976;
    static int NOTE_C7 = 2093;
    static int NOTE_CS7 = 2217;
    static int NOTE_D7 = 2349;
    static int NOTE_DS7 = 2489;
    static int NOTE_E7 = 2637;
    static int NOTE_F7 = 2794;
    static int NOTE_FS7 = 2960;
    static int NOTE_G7 = 3136;
    static int NOTE_GS7 = 3322;
    static int NOTE_A7 = 3520;
    static int NOTE_AS7 = 3729;
    static int NOTE_B7 = 3951;
    static int NOTE_C8 = 4186;
    static int NOTE_CS8 = 4435;
    static int NOTE_D8 = 4699;
    static int NOTE_DS8 = 4978;
    /* The serial port where the Arduino is connected. */
    [Tooltip("The serial port where the Arduino is connected")]
    public string port = "COM8";
    /* The baudrate of the serial port. */
    [Tooltip("The baudrate of the serial port")]
    public int baudrate = 9600;

    private SerialPort stream;



    public void Start()
    {
        
        Open();
        StartCoroutine("AsynchronousReadFromArduino");
        WriteToArduino("CONNECT");
    }
    float timeSinceUpdate = 0;
    public void Open () {
        // Opens the serial port
        stream = new SerialPort(port, baudrate);
        stream.ReadTimeout = 50;
        stream.Open();
        //this.stream.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
    }
    public void PlayMusic(string name)
    {

    }
    public void WriteToArduino(string message)
    {
        // Send the request
        stream.WriteLine(message);
        stream.BaseStream.Flush();
    }

    public string ReadFromArduino(int timeout = 0)
    {
        stream.ReadTimeout = timeout;
        try
        {
            return stream.ReadLine();
        }
        catch (TimeoutException)
        {
            return null;
        }
    }
    

    public IEnumerator AsynchronousReadFromArduino()
    {
        DateTime initialTime = DateTime.Now;
        DateTime nowTime;
        TimeSpan diff = default(TimeSpan);

        string dataString = null;

        do
        {
            // A single read attempt
            try
            {
                dataString = stream.ReadLine();
            }
            catch (TimeoutException)
            {
                dataString = null;
            }

            if (dataString != null)
            {
                rotation = float.Parse(dataString);
                yield return new WaitForSeconds(0.05f);
            } else
                yield return new WaitForSeconds(0.05f);

            nowTime = DateTime.Now;
            diff = nowTime - initialTime;

        } while (true);
        
        yield return null;
    }

    public void Close()
    {
        stream.Close();
    }
    public float GetProcessedRotation()
    {
        return Mathf.Deg2Rad * rotation;
        //return 0.0f;
    }
}