using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AccelerationCalculator : MonoBehaviour
{
    // Start is called before the first frame update
    public Rigidbody ballComponent;
    private Vector3 previousVelocity;
    private Vector3 filteredAcceleration;
    public float smoothingFactor = 0.5f;
    private int counter = 0;
    void Start()
    {
        ballComponent= GameObject.Find("Ball").GetComponent<Rigidbody>();
        previousVelocity = ballComponent.velocity;
        filteredAcceleration = Vector3.zero;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        counter++;
        Vector3 rawAcceleration = (ballComponent.velocity - previousVelocity)/Time.deltaTime;
        filteredAcceleration = Vector3.Lerp(filteredAcceleration, rawAcceleration, smoothingFactor);
        previousVelocity = ballComponent.velocity;
        Debug.Log("Acceleration:" + filteredAcceleration);
        // Debug.Log("Velocity: " + ballComponent.velocity);
    //     if(counter%10 ==0){
    //     // Debug.Log("Smoothed Acceleration: " + filteredAcceleration.magnitude);}
    //     // LinearAcceleration(out filteredAcceleration,ballComponent.position,3);
    //     // Debug.Log("Acceleration: " + filteredAcceleration);
    // }

    }
}


