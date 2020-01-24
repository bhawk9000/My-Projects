using UnityEngine;
using System.Collections.Generic;
using System.Collections;

public class Wave3 : MonoBehaviour
{
    // look up collision contact function plug in those points for x0 and z0 in the y = line

    private Vector3[] vert;
    private Mesh mesh;
    public float amplitude;
    public float velocity;
    public float wavelength;
    public float decay;
    private float pi = Mathf.PI * 2;
    private float ex;
    private bool hit;
    public static float t;
    public static float time;
    public float num;

   // public static ContactPoint contact;
   // public static Vector3 pos;

    // Use this for initialization
    void Start ()
    {
        mesh = GetComponent<MeshFilter>().mesh;
        vert = mesh.vertices;
        hit = false;
        t = 0;
        //playersc = GameObject.Find("unitychan").GetComponent<Player>();
    }

    // Update is called once per frame
    void Update()
    {
        time = Time.time - t;

        if (Input.GetKey(KeyCode.LeftShift) && Input.GetKey(KeyCode.A))
        {
            amplitude -= (Time.deltaTime * 2);
        }

        if (Input.GetKey(KeyCode.A))
        {
            amplitude += (Time.deltaTime * 2);
        }

        if (Input.GetKey(KeyCode.LeftShift) && Input.GetKey(KeyCode.L))
        {
            wavelength -= (Time.deltaTime * 2);
        }

        if (Input.GetKey(KeyCode.L))
        {
            wavelength += (Time.deltaTime * 2);
        }

        if (Input.GetKey(KeyCode.LeftShift) && Input.GetKey(KeyCode.V))
        {
            velocity -= (Time.deltaTime * 2);
        }

        if (Input.GetKey(KeyCode.V))
        {
            velocity += (Time.deltaTime * 2);
        }

        if (hit == true)
        {
            for (int i = 0; i < vert.Length; i++)
            {
               ex = Mathf.Exp(-(Mathf.Sqrt(vert[i].x * vert[i].x + vert[i].z * vert[i].z)) - decay * time);
               vert[i].y = amplitude * ex * Mathf.Cos(pi * (num * Mathf.Sqrt(vert[i].x * vert[i].x + vert[i].z * vert[i].z) - velocity * time) / wavelength);
            }

            mesh.vertices = vert;
            mesh.RecalculateBounds();
            mesh.RecalculateNormals();
        }
    }

    void OnCollisionEnter(Collision col)
    {
        if (col.collider.name == "unitychan")
        {
            t = Time.time;
            hit = true;
        }
    }
}
