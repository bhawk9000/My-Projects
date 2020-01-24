using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    public static GameManager instance;

    public MatchSettings matchSettings;

    private void Awake ()
    {
        if (instance != null)
        {
            Debug.LogError("More than one GameManager in scene.");
        }

        else
        {
            instance = this;
        }
    }

    #region Player-Tracking

    private const string PLAYER_ID_PREFIX = "Player ";

    private static Dictionary<string, PlayerManager> players = new Dictionary<string, PlayerManager>();

    public static void RegisterPlayer (string NetID, PlayerManager player)
    {
        string playerID = PLAYER_ID_PREFIX + NetID;
        players.Add(playerID, player);
        player.transform.name = playerID;
    }

    public static void UnRegisterPlayer (string playerID)
    {
        players.Remove(playerID);
    }

    public static PlayerManager GetPlayer (string playerID)
    {
        return players[playerID];
    }

    private void OnGUI()
    {
        GUILayout.BeginArea(new Rect(200, 200, 200, 500));
        GUILayout.BeginVertical();

        foreach (string playerID in players.Keys)
        {
            GUILayout.Label(playerID + " - " + players[playerID].transform.name);
        }

        GUILayout.EndVertical();
        GUILayout.EndArea();
    }

    // Use this for initialization
    void Start ()
    {
		
	}
	
	// Update is called once per frame
	void Update ()
    {
		
	}

    #endregion
}
