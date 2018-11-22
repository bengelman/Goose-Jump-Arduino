using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class PlayButton : MonoBehaviour {
    public Button button;
    // Use this for initialization
    void Start () {
        button.onClick.AddListener(LoadScene);
	}
	
	// Update is called once per frame
	void Update () {
		
	}
    public void LoadScene()
    {
        UnityEngine.SceneManagement.SceneManager.LoadScene("Main");
    }
}
