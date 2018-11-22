using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Goose : MonoBehaviour {
    public float highestHeight = 0;
    public Camera mainCam;
	// Use this for initialization
	void Start () {
        highestHeight = 0;
	}
	
	// Update is called once per frame
	void Update () {
        mainCam.transform.position = new Vector3(0, highestHeight - 2, mainCam.transform.position.z);
        
        if (transform.position.y > highestHeight)
        {
            highestHeight = transform.position.y;
        }
        if (transform.position.y < highestHeight - 10)
        {
            GetComponent<ArduinoConnector>().WriteToArduino("TIMEUP");
            SceneManager.LoadScene("Menu");
        }
        if (transform.position.y > 95)
        {
            GetComponent<ArduinoConnector>().WriteToArduino("WIN");
            SceneManager.LoadScene("Menu");
        }
        GetComponent<Rigidbody2D>().velocity = new Vector3(Mathf.Sin(GetComponent<ArduinoConnector>().GetProcessedRotation()) * 4, GetComponent<Rigidbody2D>().velocity.y, 0);
	}
    void OnCollisionEnter2D(Collision2D col)
    {
        if (col.gameObject.tag.Equals("platform_uw"))
        {
            if (transform.position.y > col.transform.position.y)
            {
                GetComponent<Rigidbody2D>().velocity = new Vector3(GetComponent<Rigidbody2D>().velocity.x, 10, 0);
                GetComponent<ArduinoConnector>().WriteToArduino("CLICK");
            }
        }
        else if (col.gameObject.tag.Equals("platform_eng"))
        {
            if (transform.position.y > col.transform.position.y)
            {
                GetComponent<Rigidbody2D>().velocity = new Vector3(GetComponent<Rigidbody2D>().velocity.x, 15, 0);
                GetComponent<ArduinoConnector>().WriteToArduino("BLIP");
            }
        }
        else if (col.gameObject.tag.Equals("platform_arts"))
        {
            if (transform.position.y > col.transform.position.y)
            {
                col.gameObject.transform.position = new Vector3(-100, 0, 0);
                GetComponent<Rigidbody2D>().velocity = new Vector3(GetComponent<Rigidbody2D>().velocity.x, 8, 0);
                GetComponent<ArduinoConnector>().WriteToArduino("BREAK");
            }
        }
    }
}
