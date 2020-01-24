using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class PlayerMotor : MonoBehaviour
{
    [SerializeField]
    private Camera cam;

    private Vector3 velo = Vector3.zero;
    private Vector3 rotation = Vector3.zero;
    private Vector3 camRotate = Vector3.zero;

    private Rigidbody rb;

	// Use this for initialization
	void Start ()
    {
        rb = GetComponent<Rigidbody>();
	}

    public void Move(Vector3 velocity)
    {
        velo = velocity;
    }

    public void Rotate(Vector3 rota)
    {
        rotation = rota;
    }

    public void camRotat(Vector3 tat)
    {
        camRotate = tat;
    }

    void FixedUpdate()
    {
        PerformMovement();
        PerformRotation();
    }

    void PerformMovement()
    {
        if (velo != Vector3.zero)
        {
            rb.MovePosition(rb.position + velo * Time.fixedDeltaTime);
        }
    }

    void PerformRotation()
    {
        rb.MoveRotation(rb.rotation * Quaternion.Euler(rotation));

        if (cam != null)
        {
            cam.transform.Rotate(-camRotate);
        }
    }
}
