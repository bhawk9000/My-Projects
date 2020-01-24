using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class open : MonoBehaviour
{
    [SerializeField]
    MeshCollider col;

    public Text scoreDisplay;

    // Use this for initialization
    void Start ()
    {
        col = gameObject.GetComponent<MeshCollider>();
      
	}
	
	// Update is called once per frame
	void Update ()
    {
	}

    void OnCollisionEnter (Collision hit)
    {
        if (hit.gameObject.name == "key")
        {
            col.enabled = false;
            DBcontroller.score += 100;
            scoreDisplay.text = "Score: " + DBcontroller.score;
        }
    }
}
