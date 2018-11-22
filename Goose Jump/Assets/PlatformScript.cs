using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformScript : MonoBehaviour {
    public GameObject goose;
	// Use this for initialization
	void Start () {
        timeElapsed = Random.value * 2;
	}

    // Update is called once per frame
    float timeElapsed = 0;
    bool toggle = false;
	void Update () {
        if (tag.Equals("platform_sci"))
        {
            timeElapsed += Time.deltaTime;
            if (timeElapsed > 2.0f)
            {
                toggle = !toggle;
                timeElapsed = 0;
            }
            if (toggle)
            {
                transform.position = new Vector3(transform.position.x + Time.deltaTime * 1.5f, transform.position.y, 0);
            }
            else
            {
                transform.position = new Vector3(transform.position.x - Time.deltaTime * 1.5f, transform.position.y, 0);
            }
        }
        if (goose.GetComponent<Goose>().highestHeight - 7.5 > transform.position.y)
            this.transform.position = new Vector3(-20, -20, 0);
	}
}
