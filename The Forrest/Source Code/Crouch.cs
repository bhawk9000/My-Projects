using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Crouch : MonoBehaviour
{
    [SerializeField]
    CapsuleCollider col;

	// Use this for initialization
	void Start ()
    {
        col = gameObject.GetComponent<CapsuleCollider>();
	}
	
	// Update is called once per frame
	void Update ()
    {
		if (Input.GetKeyDown("c"))
        {
            col.height = 0.4f;
        }

        if (Input.GetKeyUp("c"))
        {
            col.height = 0.8f;
        }
    }
}
