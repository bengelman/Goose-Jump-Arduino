using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using UnityEngine;
using UnityEngine.UI;
using Random = UnityEngine.Random;

public class GameManager : MonoBehaviour {
    public Text text;
    public Button left, right, select;
    public List<int> seen = new List<int>();
    public Category[] categories = {
        new Category("Waterloo Memes"),
        new Category("Pop Music"),
        new Category("Animals") ,
        new Category("Companies") ,
        new Category("Countries"),
        new Category("Impressions"),
        new Category("TV Shows"),
        new Category("Movies")
    };
    int category = 0;
    int score = 0;
    int prompt = 0;
    public enum GameState {
        CHOOSE_PROMPT, PLAY, TIMEUP
    };
    GameState state = GameState.CHOOSE_PROMPT;
    float timer = 0;

	// Use this for initialization
	void Start () {
        left.onClick.AddListener(LeftButton);
        right.onClick.AddListener(RightButton);
        select.onClick.AddListener(SelectButton);
        LoadPrompts();
    }
	
	// Update is called once per frame
	void Update () {
	    if (state == GameState.PLAY)
        {
            timer -= Time.deltaTime;
            text.text = categories[category].prompts[prompt];
            if (timer <= 0)
            {
                state = GameState.TIMEUP;
                timer = 5;
            }
        }
        else if (state == GameState.TIMEUP)
        {
            text.text = "SCORE: " + score;
        }
        else if (state == GameState.CHOOSE_PROMPT)
        {
            text.text = categories[category].name;
        }
	}
    public void LeftButton()
    {
        if (state == GameState.CHOOSE_PROMPT)
        {
            category--;
            if (category < 0)
            {
                category += categories.Length;
            }
        }
    }
    public void RightButton()
    {
        if (state == GameState.CHOOSE_PROMPT)
        {
            category++;
            category %= categories.Length;
        }
    }
    public void SelectButton()
    {
        if (state == GameState.TIMEUP)
        {
            state = GameState.CHOOSE_PROMPT;
        }
        else if (state == GameState.CHOOSE_PROMPT)
        {
            state = GameState.PLAY;
            score = 0;
            timer = 60;
            seen.Clear();
            prompt = Random.Range(0, categories[category].prompts.Count - 1);
            seen.Add(prompt);
        }
        else if (state == GameState.PLAY)
        {
            score++;
            while (seen.Contains(prompt))
                prompt = Random.Range(0, categories[category].prompts.Count - 1);
            seen.Add(prompt);
        }

    }

    void LoadPrompts()
    {
        foreach (Category s in categories)
        {
            try
            {
                string line;
                StreamReader theReader = new StreamReader("Assets/" + s.name + ".txt", Encoding.Default);
                using (theReader)
                {
                    do
                    {
                        
                        line = theReader.ReadLine();

                        if (line != null)
                        {
                            Debug.Log("Reading a line");
                            s.prompts.Add(line);
                        }
                    }
                    while (line != null);  
                    theReader.Close();
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("{0}\n", e.Message);
                
            }
        }
    }
    public class Category
    {
        public string name;
        public List<string> prompts = new List<string>();
        public Category(string name)
        {
            this.name = name;
        }
    }
}
