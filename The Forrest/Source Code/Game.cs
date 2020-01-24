using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Game : MonoBehaviour
{
    public Text playerDisplay;
    public Text scoreDisplay;

    public void Awake()
    {
        if (DBcontroller.LoggedIn == false)
        {
            playerDisplay.text = "Player: Offline";
            scoreDisplay.text = "Score: 0";
        }

        else
        {
            playerDisplay.text = "Player: " + DBcontroller.userName;
            scoreDisplay.text = "Score: " + DBcontroller.score;
        }
    }

    public void CallSaveData()
    {
        if (DBcontroller.LoggedIn == false)
        {
            UnityEngine.SceneManagement.SceneManager.LoadScene(0);
        }

        else
        {
            StartCoroutine(SavePlayerData());
        }
    }

    IEnumerator SavePlayerData()
    {
        WWWForm form = new WWWForm();
        form.AddField("name", DBcontroller.userName);
        form.AddField("score", DBcontroller.score);

        WWW www = new WWW("http://localhost/horrorunity/savedata.php", form);
        yield return www;

        if (www.text == "0")
        {
            Debug.Log("Game Saved");
        }
        else
        {
            Debug.Log("Save Failed. Error #" + www.text);
        }

        DBcontroller.LogOut();
        UnityEngine.SceneManagement.SceneManager.LoadScene(0);
    }

    public void IncreaseScore()
    {
        DBcontroller.score += 100;
        scoreDisplay.text = "Score: " + DBcontroller.score;
    }

    void Update()
    {
        if (Input.GetKeyDown("escape"))
        {
            CallSaveData();
        }
    }
}
