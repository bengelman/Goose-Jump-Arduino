using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformScript : MonoBehaviour {
    public GameObject goose;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        if (goose.GetComponent<Goose>().highestHeight - 7.5 > transform.position.y)
            this.transform.position = new Vector3(-20, -20, 0);
	}
}
