using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

[RequireComponent(typeof(PlayerMotor))]
public class PlayerController : MonoBehaviour
{
    [SerializeField]
    private float speed = 2f;
    [SerializeField]
    private float lookSensitivity = 3f;

    private PlayerMotor motor;

	// Use this for initialization
	void Start ()
    {
        motor = GetComponent<PlayerMotor>();
	}
	
	// Update is called once per frame
	void FixedUpdate ()
    {
        float xMove = Input.GetAxisRaw("Horizontal");
        float zMove = Input.GetAxisRaw("Vertical");

        Vector3 moveHorizontal = transform.right * xMove;
        Vector3 moveVertical = transform.forward * zMove;

        if (Input.GetButton("Fire3"))
        {
            Vector3 velocity = (moveHorizontal + moveVertical).normalized * speed;
            motor.Move(velocity);
        }

        else
        {
            Vector3 velocity = (moveHorizontal + moveVertical).normalized;
            motor.Move(velocity);
        }

        float yRot = Input.GetAxisRaw("Mouse X");
        Vector3 rotation = new Vector3(0f, yRot, 0f) * lookSensitivity;

        motor.Rotate(rotation);

        float xRot = Input.GetAxisRaw("Mouse Y");
        Vector3 camRotation = new Vector3(xRot, 0f, 0f) * lookSensitivity;

        motor.camRotat(camRotation);
    }
}
