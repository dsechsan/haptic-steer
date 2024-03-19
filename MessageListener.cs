using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class Messagelistener : MonoBehaviour
{
    private Rigidbody ballcomponent;
    public SerialController serialController;
    private float PI = 3.1415F;
    public float speed = 5f;
    public float rotationSpeed = 180f;
    private string[] values;
    void Start()
    {
        // ballModifier = GameObject.Find("Ball");
        serialController = GameObject.Find("Ball").GetComponent<SerialController>();
        ballcomponent = GameObject.Find("Ball").GetComponent<Rigidbody>();
    }

    void Update()
    {
        // // serialController.SendSerialMessage(stringMsg);
        // string message = serialController.ReadSerialMessage();
        // float angle_in, angle_out;
        // if(message != null){
        // values  = message.Split(',');}
        // for (int i = 0; i < values.Length; i++)
        // {
        // // Debug.Log("Value " + i + ": " + values[i]);
        // if(float.TryParse(values[i].Trim(),out angle_in)){
        //     Debug.Log(angle_in);
        // }
        // else{

        // }
        // }
        string message = serialController.ReadSerialMessage();
        float angle_in, angle_out;

        if(message != null){
            Debug.Log(message);
            values  = message.Split(',');
            if (float.TryParse(values[0].Trim(), out angle_in) && float.TryParse(values[1].Trim(), out angle_out))
        {
            // Now you have float1 and float2 as the parsed float values
            Debug.Log("Float 1: " + angle_in);
            Debug.Log("Float 2: " + angle_out);
            ballcomponent.AddForce(Vector3.forward * (angle_out/5));
            ballcomponent.AddForce(Vector3.left * (angle_in/5));

        //     float horizontalInput = Input.GetAxis("Horizontal");
        
        // // Input for forward/back direction
        // float verticalInput = Input.GetAxis("Vertical");

        // Create directional vectors based on input
        // Vector3 horizontalVector = transform.right * angle_in;
        // Vector3 verticalVector = transform.forward * angle_out;

        // // Combine directional vectors to get the total movement vector
        // Vector3 movementVector = horizontalVector + verticalVector;

        // // Normalize the total movement vector to ensure consistent movement speed
        // movementVector.Normalize();

        // // Move the object based on the total movement vector
        // speed = 5* angle_out*10;
        // transform.Translate(movementVector * speed * Time.deltaTime, Space.World);

        // // Rotate the object based on the horizontal input for left/right rotation
        // transform.Rotate(Vector3.up, horizontalInput * rotationSpeed * Time.deltaTime);


            // ballcomponent.AddForce(*100f,ForceMode.Force);
            // ballcomponent.AddForce(angle_in*10f, ForceMode.Force);


        }
        else
        {
            Debug.Log("Failed to parse floats from the received string.");
        } 
        }

       

        //     if(float.TryParse(values[0].Trim(), out  angle_in))
        //     {
        //         Vector3 forceDirection = Quaternion.Euler(0,angle_in,0) * Vector3.forward;
        //         ballcomponent.AddForce(forceDirection*1000f,ForceMode.Force);
        //     }
        //     if(float.TryParse(values[1].Trim(), out  angle_out))
        //     {
        //         Vector3 forceDirection = Quaternion.Euler(0,0,angle_out) * Vector3.forward;
        //         ballcomponent.AddForce(forceDirection*1000f,ForceMode.Force);
        //     }
        // }

        }
        // Debug.Log(values[0] + values[1]);
        // 
        //  if (values.Length >= 2 && float.TryParse(values[0].Trim(), out angle_in) && float.TryParse(values[1].Trim(), out angle_out))
        // {
        //     // Now you have float1 and float2 as the parsed float values
        //     Debug.Log("Float 1: " + angle_in);
        //     Debug.Log("Float 2: " + angle_out);
        // }
        // else
        // {
        //     Debug.LogError("Failed to parse floats from the received string.");
        // }
    
    // void OnMessageArrived(string msg)
    // {
    // //    Debug.Log("msg");
    // }
// Invoked when a connect/disconnect event occurs. The parameter 'success'
// will be 'true' upon connection, and 'false' upon disconnection or
// failure to connect.
    void OnConnectionEvent(bool success)
    {
        Debug.Log(success ? "Device connected" : "Device disconnected");
    }
}
// void OnMessageArrived(string msg)
//     {
//         Debug.Log(msg);
//         // float speed = float.Parse(msg)*100 ;
//         // float new_speed = 0.3F;
//         // ballModifier.transform.Translate(Vector3.forward * new_speed);
//     }
    
// void OnConnectionEvent(bool success)
//     {
//         Debug.Log("Connected");
//     }

    

// void OnApplicationQuit()
    // {
    //     if (serialPort.IsOpen)
    //         serialPort.Close();
    // }
//void Update()
  //  {
        // try
        // {
        //     string message = serialPort.ReadLine();
        //     messageBuffer.Enqueue(message);
        //     ProcessMessageBuffer();
        // }
        // catch (System.Exception ex)
        // {
        //     Debug.LogError("Error reading from serial port: " + ex.Message);
        // }
 //   }
 // void ProcessMessageBuffer()
    // {
    //     while (messageBuffer.Count > 0)
    //     {
    //         string message = messageBuffer.Dequeue();
    //         OnMessageArrived(message);
    //     }
    // }
// void Start()
   // try
        // {
        //     serialPort.Open();
        //     serialPort.ReadTimeout = 1000; // Set a timeout for reading from the serial port
        // }
        // catch (System.Exception e)
        // {
        //     Debug.LogError("Error opening serial port: " + e.Message);

// SerialPort serialPort = new SerialPort("/dev/cu.usbserial-A10JXKN8", 9600);
    // private Queue<string> messageBuffer = new Queue<string>();